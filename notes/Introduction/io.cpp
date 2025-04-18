#include <iostream>
#include <fstream>
#include <string>
#include <cassert> // For the assert macro

int main() {
    // 1. Open the file
    std::ofstream file("/tmp/file", std::ios::out | std::ios::trunc);
    //Check if the file is opened
    assert(file.is_open());

    // 2. Write to the file
    std::string data = "hello world\n";
    file.write(data.c_str(), data.size());
    assert(file.good());

    // 3. Close the file
    file.close();

    return 0;
}
