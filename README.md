Here is the revised README for the `ioOptimization` project:

# ioOptimization

## Overview
The `ioOptimization` project focuses on optimizing disk I/O operations using various C++ programs. The project is divided into multiple parts, each targeting different aspects of I/O optimization such as measurement, caching, system calls, and raw performance.

## Setup and Usage
1. Extract the `codes.zip` file and run the compilation script to compile all provided C++ files.
2. There are three script files:
   - **Compilation script**: Compiles all programs.
   - **Execution script**: Executes all compiled code.
   - **Extra credit script**: Compiles and executes additional code (e.g., dd compare code and Google benchmark).

### Scripts
- For the execution and extra credit scripts, you may need to change filenames accordingly.
- If you encounter "Permission denied" issues, run `chmod -x <scriptname>`.
- For optimal file size execution within a reasonable time, run 'run2' separately and change the filename accordingly in `executionScript.sh`.
- Default filename in `executionScript.sh` and `extracreditScript.sh` is "ubuntu-21.04-desktop-amd64.iso". You can change the filename or run the code manually.

### Compilation
- Code compilation command: `g++ -std=c++11 -O3 run.cpp -o run`

## Project Breakdown

### Part 1: Basics
Write a program that can read and write a file from disk using the C/C++ library's open, read, write, and close functions.
- Parameters:
  - File name
  - File size (for writing)
  - Block size (how much to read with a single call)
- Execute: `./run <filename> [-r|-w] <block_size> <block_count>`

### Part 2: Measurement
Write a program to find a file size that can be read in a reasonable time (between 5 and 15 seconds).
- Input: block size
- Output: file size/block count
- Execute: `./run2 <filename> <block_size>`

### Part 3: Raw Performance
Make your program output the performance achieved in MiB/s and create a graph showing performance as block size changes.

### Part 4: Caching
Experiment with clearing the caches and not. Create a graph showing performance for cached and non-cached reads for various block sizes.
- Clear cache: `sudo sh -c "/usr/bin/echo 3 > /proc/sys/vm/drop_caches"`
- Execute:
  - `./run3 <file_name> block_size`
  - `./run3 <file_name> block_size` (again for cached performance)

### Part 5: System Calls
Measure performance in MiB/s and B/s when using a block size of 1 byte.
- Execute: `./run5a <file_name> 1` and `./run5b <file_name> 1`

### Part 6: Fast Performance
Optimize your program to run as fast as possible. Report both cached and non-cached performance numbers.
- Execute: `./fast <filename>`

## Conclusion
This project provides a comprehensive framework for optimizing disk I/O operations. Each part focuses on different optimization techniques, making it a versatile tool for performance analysis and improvement.