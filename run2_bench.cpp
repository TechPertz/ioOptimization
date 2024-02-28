#include <iostream>
#include <fstream>
#include <chrono>
#include <vector>
#include <benchmark/benchmark.h>

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

static void BM_MeasureReadTime(benchmark::State& state) {
    std::string filename = "ubuntu-21.04-desktop-amd64.iso";  // Change to a file name accordingly
    std::size_t blockSize = state.range(0);
    
    for (auto _ : state) {
        std::size_t blockCount = 0;
        unsigned int finalXorResult = 0;
        measureReadTime(filename, blockSize, blockCount, finalXorResult);
        benchmark::DoNotOptimize(finalXorResult);
    }
}

BENCHMARK(BM_MeasureReadTime)->Arg(1024)->Arg(2048)->Arg(4096)->Arg(8192)->Arg(16384)->Arg(32768)->Arg(65536);
BENCHMARK_MAIN();
