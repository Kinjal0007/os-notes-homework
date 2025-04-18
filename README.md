# Operating Systems: Learning Journey 🚀

This repository documents my learning journey through Operating Systems concepts, following the [Operating Systems: Three Easy Pieces](http://pages.cs.wisc.edu/~remzi/OSTEP/) (OSTEP) book and its [homework assignments](https://github.com/remzi-arpacidusseau/ostep-homework).

## Repository Structure 📂

- `notes/`: Chapter-wise detailed notes
  - `CH-01/`: Introduction and Dialogue
  - `CH-03/`: Virtualization Dialogue
  - `virtualization/`: CPU and Memory virtualization notes
  - `concurrency/`: Threads, locks, and synchronization notes
  - `persistence/`: Storage, I/O, and file systems notes
- `homework-solutions/`: Solutions to OSTEP homework assignments
  - `Simulation.cpp`: FCFS scheduler simulation
  - `Performance-Measurement.cpp`: System performance measurement
- `ostep-homework/`: Original homework assignments from OSTEP
- `code/`: Additional code examples and experiments

## Learning Progress 📚

### Completed Topics ✅

#### Introduction

- [x] Chapter 1: Dialogue
- [x] Chapter 2: Introduction to Operating Systems

#### Virtualization

- [x] Chapter 3: Dialogue
- [x] Chapter 4: Processes
- [x] Chapter 5: Process API
  - fork(), exec(), and wait() implementations
  - File descriptor manipulation
  - Process control and management

### Currently Learning 🎯

- Chapter 6: Direct Execution
- Chapter 7: CPU Scheduling

### Upcoming Topics 📋

#### Virtualization (Cont.)

- Memory Abstraction (Address Spaces, Memory API)
- Address Translation, Segmentation
- Free-Space Management
- Paging and Swapping

#### Concurrency

- Threads and Locks
- Condition Variables
- Semaphores
- Concurrency Bugs
- Event-based Concurrency

#### Persistence

- I/O Devices
- Hard Disk Drives
- RAID
- Files and Directories
- File System Implementation

## Homework Solutions Status ✅

### Virtualization

- [x] Process API (Chapter 5)

  - Process creation and control
  - Variable sharing between processes
  - File descriptor inheritance
  - Process ordering with wait()

- [x] CPU Scheduling
  - FCFS Scheduler Implementation
  - Performance Metrics Analysis
  - Context Switch Measurements

## Notes Organization 📝

Each chapter's notes follow this structure:

- Key Concepts and Terminology
- Code Examples and Implementation
- Common Pitfalls and Solutions
- Practice Problems and Solutions
- Additional Resources and References

## Environment Setup 🛠️

Development Environment:

- macOS Sonoma
- GCC/Clang compiler
- VS Code with C/C++ extensions
- Make build system

## Building and Running

1. Clone the repository
2. Navigate to homework-solutions
3. Run `make` to build all programs
4. Execute individual programs as needed

## Resources 📖

- [OSTEP Book](http://pages.cs.wisc.edu/~remzi/OSTEP/)
- [Official OSTEP Homework](https://github.com/remzi-arpacidusseau/ostep-homework)
- [Man7 Linux Documentation](https://man7.org/)

## Contributing 🤝

While this is a personal learning repository, if you spot errors or have suggestions:

1. Open an issue
2. Explain the problem/suggestion
3. Reference relevant book chapter/homework

## License 📄

This repository is for educational purposes. Code samples are MIT licensed unless noted otherwise.

---

_This is a living document that will evolve as I progress through my OS learning journey._
