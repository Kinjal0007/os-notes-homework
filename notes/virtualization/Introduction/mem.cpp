#include <iostream>
#include <cstdlib> // For malloc and free (though we'll use new/delete in idiomatic C++)
#include <unistd.h> // For getpid()

// Assuming "common.h" might have a Spin function, we'll define a simple one
void Spin(int seconds) {
    // In a real scenario, this might involve a more controlled delay
    // For simplicity, we'll use a busy-wait loop.
    long long count = 0;
    long long target = seconds * 1000000; // Approximate iterations for a second
    while (count < target) {
        count++;
    }
}

int main(int argc, char *argv[]) {
    int *p;

    // Allocate memory for an integer using C++'s new operator
    p = new int; // Equivalent to malloc(sizeof(int)) in C (line a1)

    if (p == nullptr) { // Check for allocation failure (like p == NULL in C)
        std::cerr << "Memory allocation failed!" << std::endl;
        return 1;
    }

    std::cout << "Address pointed to by p: " << p << std::endl; // Equivalent to printf("%p\n", p); in C (line a2)

    *p = 0; // Dereference p and set the value to 0 (line a3)

    while (true) {
        Spin(1);
        std::cout << "PID: " << getpid() << ", Value at p: " << *p << std::endl; // Equivalent to printf("PID: %d, Value at p: %d\n", getpid(), *p); in C (line a4)
        (*p)++; // Increment the value pointed to by p
    }

    // In a real application, you would eventually free the allocated memory
    // to prevent memory leaks. However, this program runs infinitely.
    // For demonstration purposes, we'll skip the 'delete p;' as it's never reached.
    // In a terminating program, you would do: delete p;

    return 0; // Technically unreachable due to the infinite loop
}