# Chapter 6: Direct Execution - Measurement Homework

This directory contains the implementation of measurement tools for understanding system call and context switch costs, as described in Chapter 6 of OSTEP (Operating Systems: Three Easy Pieces).

## Problem Description

The goal is to measure two fundamental operating system operations:

1. The cost of a system call
2. The cost of a context switch

## Implementation Details

### System Call Measurement (`measure_syscall.cpp`)

- Uses a null read system call for measurement
- Uses high-precision `clock_gettime()` for timing
- Measures timer overhead for accurate results
- Performs statistical analysis (mean and standard deviation)

### Context Switch Measurement (`measure_context_switch.cpp`)

- Creates two processes that communicate via pipes
- Forces context switches through pipe I/O operations
- Uses high-precision `clock_gettime()` for timing
- Performs statistical analysis on round-trip measurements
- Notes: CPU binding is disabled on macOS but would be implemented on Linux for better accuracy

## Building and Running

```bash
# Build both programs
make

# Run system call measurements
./measure_syscall

# Run context switch measurements
./measure_context_switch

# Clean up
make clean
```

## Understanding the Results

The programs output:

- Timer overhead measurements
- Number of iterations performed
- Mean time per operation
- Standard deviation

For context switches, the reported time is divided by 2 since each round-trip involves two context switches.

## Compatibility Notes

This implementation:

- Works on both macOS and Linux systems
- Uses standard POSIX timing functions (`clock_gettime`)
- Disables CPU binding on macOS (would be used on Linux)
- Reports results in microseconds

## Requirements

- POSIX-compliant operating system (macOS, Linux, etc.)
- g++ compiler with C++11 support
