#include <iostream>
#include <fstream>
#include <chrono>
#include <vector>

unsigned int xorBuffer(const unsigned int* buffer, std::size_t size) {
    unsigned int result = 0;
    for (std::size_t i = 0; i < size; ++i) {
        result ^= buffer[i];
    }
    return result;
}

std::chrono::milliseconds measureReadTime(const std::string& filename, std::size_t blockSize, std::size_t& blockCount, unsigned int& finalXorResult) {
    std::ifstream file(filename, std::ios::binary | std::ios::in);

    if (!file.is_open()) {
        std::cerr << "Error opening file for reading: " << filename << std::endl;
        return std::chrono::milliseconds(0);
    }

    std::vector<unsigned int> buffer(blockSize / sizeof(unsigned int));
    auto start = std::chrono::high_resolution_clock::now();

    finalXorResult = 0;
    std::streamsize bytesRead;

    while (file.read(reinterpret_cast<char*>(buffer.data()), blockSize)) {
        bytesRead = file.gcount();
        finalXorResult ^= xorBuffer(buffer.data(), bytesRead / sizeof(unsigned int));
        ++blockCount;
    }

    
    if (file.gcount() > 0) {
        finalXorResult ^= xorBuffer(buffer.data(), file.gcount() / sizeof(unsigned int));
    }

    auto end = std::chrono::high_resolution_clock::now();
    file.close();

    return std::chrono::duration_cast<std::chrono::milliseconds>(end - start);
}

int main(int argc, char* argv[]) {
    if (argc != 3) {
        std::cerr << "Usage: " << argv[0] << " <filename> <block_size>" << std::endl;
        return 1;
    }

    std::string filename = argv[1];
    std::size_t blockSize = std::stoul(argv[2]);

    if (blockSize % sizeof(unsigned int) != 0) {
        std::cerr << "Block size must be a multiple of " << sizeof(unsigned int) << std::endl;
        return 1;
    }

    std::size_t blockCount = 0;
    unsigned int finalXorResult = 0;

    auto readTime = measureReadTime(filename, blockSize, blockCount, finalXorResult);
    long long fileSize = blockSize * blockCount;

    std::cout << "Time to Read: " << readTime.count() << " ms\n";
    std::cout << "Final XOR Result (All Blocks): " << std::hex << finalXorResult << std::endl;
    std::cout << "Total Blocks Read: " << std::dec<< blockCount << std::endl;
    std::cout << "File size time: " << std::dec << fileSize << " bytes" << std::endl;

    return 0;
}
