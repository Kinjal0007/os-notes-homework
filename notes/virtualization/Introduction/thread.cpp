#include <iostream>
#include <thread>
#include <mutex>
#include <atomic> // For atomic counter

using namespace std;

// Global variables
atomic<int> counter(0); // Use atomic to make counter thread-safe
int loops;

void worker() {
    for (int i = 0; i < loops; i++) {
        counter++; // Atomically increment the counter
    }
}

int main(int argc, char* argv[]) {
    if (argc != 2) {
        cerr << "Usage: threads <value>\n";
        return 1;
    }

    loops = atoi(argv[1]); // Convert command-line argument to integer

    thread p1(worker); // Create thread p1, start running worker()
    thread p2(worker); // Create thread p2, start running worker()

    cout << "Initial value: " << counter << endl;

    p1.join(); // Wait for thread p1 to finish
    p2.join(); // Wait for thread p2 to finish

    cout << "Final value: " << counter << endl;

    return 0;
}
