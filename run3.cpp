#include <iostream>
#include <fstream>
#include <chrono>
#include <vector>
#include <cstring>

unsigned int xorBuffer(const unsigned int* buffer, std::size_t size) {
    unsigned int result = 0;
    for (std::size_t i = 0; i < size; ++i) {
        result ^= buffer[i];
    }
    return result;
}

double measureReadSpeedAndXor(const std::string& filename, std::size_t blockSize, unsigned int& finalXorResult) {
    std::ifstream file(filename, std::ios::binary | std::ios::in);
    if (!file.is_open()) {
        std::cerr << "Error opening file for reading: " << filename << std::endl;
        return 0.0;
    }

    std::vector<char> buffer(blockSize, 0); 
    finalXorResult = 0;
    std::size_t totalBytesRead = 0;

    auto start = std::chrono::high_resolution_clock::now();

    while (file.read(buffer.data(), buffer.size()) || file.gcount() != 0) {
    // Getting number of bytes read
    std::size_t actualBytesRead = file.gcount();

    
    finalXorResult ^= xorBuffer(reinterpret_cast<unsigned int*>(buffer.data()), actualBytesRead / sizeof(unsigned int));
    totalBytesRead += actualBytesRead;
}


    auto end = std::chrono::high_resolution_clock::now();
    file.close();

    std::chrono::duration<double> elapsed = end - start;
    return totalBytesRead / (1024.0 * 1024.0) / elapsed.count(); // MiB/s
}

int main(int argc, char* argv[]) {
    if (argc != 3) {
        std::cerr << "Usage: " << argv[0] << " <filename> <block_size>\n";
        return 1;
    }

    std::string filename = argv[1];
    std::size_t blockSize = std::stoul(argv[2]);
    unsigned int finalXorResult = 0;

    double speed = measureReadSpeedAndXor(filename, blockSize, finalXorResult);
    std::cout << "Block size: " << blockSize << " bytes, Read speed: " << speed << " MiB/s" << std::endl;
    std::cout << "Final XOR Result: " << std::hex << finalXorResult << std::endl;

    return 0;
}
