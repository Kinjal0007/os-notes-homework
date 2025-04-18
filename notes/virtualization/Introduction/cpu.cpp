#include <iostream>
#include <string>
#include <chrono>
#include <thread>

// Assuming "common.h" in C might have a similar spin function.
// We'll create a simple equivalent using C++'s <chrono> and <thread>.
void Spin(int seconds) {
    std::this_thread::sleep_for(std::chrono::seconds(seconds));
}

int main(int argc, char *argv[]) {
    if (argc != 2) {
        std::cerr << "usage: cpu <string>" << std::endl;
        return 1;
    }

    std::string str = argv[1];

    while (true) {
        Spin(1);
        std::cout << str << std::endl;
    }

    return 0; // Technically unreachable
}