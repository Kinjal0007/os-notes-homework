# Operating Systems: Learning Journey 🚀

This repository documents my learning journey through Operating Systems concepts, following the [Operating Systems: Three Easy Pieces](http://pages.cs.wisc.edu/~remzi/OSTEP/) (OSTEP) book and its [homework assignments](https://github.com/remzi-arpacidusseau/ostep-homework).

## Repository Structure 📂

```
.
├── notes/
│   ├── virtualization/
│   │   ├── Introduction/           # Chapter 2
│   │   │   ├── cpu.cpp            # CPU virtualization example
│   │   │   ├── mem.cpp            # Memory virtualization example
│   │   │   ├── thread.cpp         # Thread operations example
│   │   │   └── io.cpp             # I/O operations example
│   │   └── Process-Api/           # Chapter 4-5
│   │       ├── p1.cpp             # Basic process creation
│   │       ├── p2.cpp             # Process control
│   │       ├── p3.cpp             # Process execution
│   │       └── p4.cpp             # Complex process interactions
│   ├── concurrency/               # Upcoming
│   └── persistence/               # Upcoming
├── homework-solutions/            # My solutions to OSTEP homework
├── ostep-homework/               # Original OSTEP homework (submodule)
└── README.md
```

## Learning Progress 📚

### Completed Topics ✅

#### Virtualization

- [x] Chapter 2: Introduction to Operating Systems
  - Basic OS concepts
  - Virtualization examples (CPU, Memory, Threads, I/O)
  - System call interface
- [x] Chapter 4: Processes
  - Process concept
  - Process creation
  - Process states
  - Process management
- [x] Chapter 5: Process API
  - fork(), exec(), and wait() implementations
  - File descriptor manipulation
  - Process control and management
  - Complex process interactions

### Currently Learning 🎯

- Chapter 6: Direct Execution
- Chapter 7: CPU Scheduling

### Upcoming Topics 📋

#### Virtualization (Cont.)

- Memory Abstraction (Address Spaces)
- Address Translation
- Segmentation
- Free-Space Management
- Paging and TLBs
- Advanced Page Tables
- Swapping Mechanisms

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

## Code Examples 💻

### Virtualization Examples

- **CPU Virtualization** (`virtualization/Introduction/cpu.cpp`): Demonstrates basic CPU scheduling
- **Memory Virtualization** (`virtualization/Introduction/mem.cpp`): Shows memory management
- **Thread Operations** (`virtualization/Introduction/thread.cpp`): Basic thread handling
- **I/O Operations** (`virtualization/Introduction/io.cpp`): Input/Output handling

### Process API Examples

- **Basic Process Creation** (`virtualization/Process-Api/p1.cpp`): Simple fork() example
- **Process Control** (`virtualization/Process-Api/p2.cpp`): Process management
- **Process Execution** (`virtualization/Process-Api/p3.cpp`): exec() family usage
- **Complex Interactions** (`virtualization/Process-Api/p4.cpp`): Advanced process control

## Building and Running 🛠️

Each code example can be compiled and run independently:

```bash
# For Introduction examples
gcc -o cpu virtualization/Introduction/cpu.cpp
gcc -o mem virtualization/Introduction/mem.cpp
gcc -o thread virtualization/Introduction/thread.cpp
gcc -o io virtualization/Introduction/io.cpp

# For Process API examples
gcc -o p1 virtualization/Process-Api/p1.cpp
gcc -o p2 virtualization/Process-Api/p2.cpp
gcc -o p3 virtualization/Process-Api/p3.cpp
gcc -o p4 virtualization/Process-Api/p4.cpp
```

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
