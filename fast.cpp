#include <iostream>
#include <fstream>
#include <vector>
#include <thread>
#include <mutex>
#include <chrono>

void processFileSegments(const std::string& filename, size_t start, size_t end, size_t blockSize, unsigned int& xorResult, std::mutex& mutex) {
    std::ifstream file(filename, std::ios::binary);
    if (!file) {
        std::cerr << "Error opening file." << std::endl;
        return;
    }

    size_t current = start;
    unsigned int localXor = 0;
    while (current < end) {
        size_t segmentSize = std::min(blockSize, end - current);
        std::vector<char> buffer(segmentSize);
        file.seekg(current);
        if (!file.read(buffer.data(), segmentSize)) {
            std::cerr << "Error reading file." << std::endl;
            break;
        }

        for (size_t i = 0; i < segmentSize / sizeof(unsigned int); ++i) {
            localXor ^= reinterpret_cast<unsigned int*>(buffer.data())[i];
        }
        current += segmentSize;
    }

    std::lock_guard<std::mutex> lock(mutex);
    xorResult ^= localXor;
}

int main(int argc, char* argv[]) {
    if (argc != 2) {
        std::cerr << "Usage: " << argv[0] << " <file_to_read> <block_size>\n";
        return 1;
    }

    std::string filename = argv[1];
    size_t blockSize = 65536;
    // size_t blockSize = std::stoull(argv[2]);
    unsigned int xorResult = 0;
    std::mutex mutex;

    std::ifstream file(filename, std::ios::binary | std::ios::ate);
    if (!file) {
        std::cerr << "Error opening file." << std::endl;
        return 1;
    }
    size_t fileSize = file.tellg();
    file.close();

    // Start timer
    auto startTime = std::chrono::high_resolution_clock::now();

    size_t numThreads = std::min(static_cast<size_t>(std::thread::hardware_concurrency()), fileSize / blockSize);
    std::vector<std::thread> threads;
    size_t segmentSize = fileSize / numThreads;
    for (size_t i = 0; i < numThreads; ++i) {
        size_t start = i * segmentSize;
        size_t end = (i == numThreads - 1) ? fileSize : start + segmentSize;
        threads.emplace_back(processFileSegments, filename, start, end, blockSize, std::ref(xorResult), std::ref(mutex));
    }

    for (auto& t : threads) {
        t.join();
    }

    // Stoping timer and calculating elapsed time
auto endTime = std::chrono::high_resolution_clock::now();
std::chrono::duration<double> elapsedSeconds = endTime - startTime;

double performanceMiBps = (fileSize / (1024.0 * 1024.0)) / elapsedSeconds.count();

std::cout << "Final XOR Result: " << std::hex << xorResult << std::endl;
std::cout << "Performance: " << performanceMiBps << " MiB/s" << std::endl;

return 0;
}
