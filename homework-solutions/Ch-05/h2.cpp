#include <iostream>
#include <unistd.h>
#include <fcntl.h>
#include <sys/types.h>
#include <cstdlib>
#include <cstring>
#include <cerrno>
#include <sys/wait.h>

using namespace std;

int main() {
    const char* filename = "my_file.txt";
    int fd;

    fd = open(filename, O_CREAT | O_WRONLY | O_TRUNC, 0666);
    if (fd == -1) {
        cerr << "Error opening file: " << strerror(errno) << endl;
        exit(EXIT_FAILURE);
    }

    pid_t rc = fork();

    if (rc < 0) {
        cerr << "fork failed: " << strerror(errno) << endl;
        close(fd);
        exit(EXIT_FAILURE);
    } else if (rc == 0) {
        const char* child_message = "Child: This is the child writing.\n";
        write(fd, child_message, strlen(child_message));
        close(fd);
        exit(EXIT_SUCCESS);
    } else {
        const char* parent_message = "Parent: This is the parent writing.\n";
        write(fd, parent_message, strlen(parent_message));
        wait(nullptr);
        close(fd);
    }

    return 0;
}
