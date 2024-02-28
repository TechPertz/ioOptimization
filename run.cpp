#include <iostream>
#include <fstream>
#include <vector>
#include <random>
#include <algorithm>

unsigned int xorBuffer(const unsigned int* buffer, std::size_t size) {
    unsigned int result = 0;
    for (std::size_t i = 0; i < size; ++i) {
        result ^= buffer[i];
    }
    return result;
}

void writeFile(const std::string& filename, std::size_t fileSize, std::size_t blockSize) {
    std::ofstream file(filename, std::ios::binary | std::ios::out);
    if (!file.is_open()) {
        std::cerr << "Error opening file for writing: " << filename << std::endl;
        return;
    }

    std::vector<char> buffer(blockSize);
    std::random_device rd;
    std::mt19937 gen(rd());
    std::uniform_int_distribution<> dis(0, 255);

    for (std::size_t i = 0; i < fileSize; i += blockSize) {
        std::generate(buffer.begin(), buffer.end(), [&]() { return static_cast<char>(dis(gen)); });
        file.write(buffer.data(), buffer.size());
    }
}

void readFile(const std::string& filename, std::size_t blockSize, std::size_t blockCount) {
    std::ifstream file(filename, std::ios::binary | std::ios::in);
    if (!file.is_open()) {
        std::cerr << "Error opening file for reading: " << filename << std::endl;
        return;
    }

    std::vector<unsigned int> buffer(blockSize / sizeof(unsigned int));
    unsigned int finalXorResult = 0;
    std::streamsize bytesRead;

    for (std::size_t i = 0; i < blockCount; ++i) {
        file.read(reinterpret_cast<char*>(buffer.data()), blockSize);
        bytesRead = file.gcount();
        finalXorResult ^= xorBuffer(buffer.data(), bytesRead / sizeof(unsigned int));

        if (bytesRead < static_cast<std::streamsize>(blockSize)) {
            break; // Break the loop if the last block is partial
        }
    }

    std::cout << "Final XOR Result: " << std::hex << finalXorResult << std::endl;
}


int main(int argc, char* argv[]) {
    if (argc != 5) {
        std::cerr << "Usage: " << argv[0] << " <filename> [-r|-w] <block_size> <block_count>\n";
        return 1;
    }

    std::string filename = argv[1];
    std::string mode = argv[2];
    std::size_t blockSize = std::stoul(argv[3]);
    std::size_t blockCount = std::stoul(argv[4]);

    if (blockSize % sizeof(unsigned int) != 0) {
        std::cerr << "Block size must be a multiple of " << sizeof(unsigned int) << std::endl;
        return 1;
    }

    if (mode == "-w") {
        writeFile(filename, blockSize * blockCount, blockSize);
    } else if (mode == "-r") {
        readFile(filename, blockSize, blockCount);
    } else {
        std::cerr << "Invalid mode. Use -r for reading or -w for writing.\n";
        return 1;
    }

    return 0;
}
