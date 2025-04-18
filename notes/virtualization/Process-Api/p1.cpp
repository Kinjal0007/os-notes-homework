#include <iostream>   // For std::cout, std::cerr, std::endl
#include <cstdlib>    // For exit() -> std::exit()
#include <unistd.h>   // For fork(), getpid()
#include <sys/wait.h> // For wait() (optional but good practice)
using namespace std;

int main(int argc, char *argv[])
{
    // Use std::cout for output
    cout << "hello world (pid:" << getpid() << ")" << endl;

    // Call fork()
    pid_t rc = fork(); // pid_t is the traditional type for process IDs

    if (rc < 0)
    {
        // Fork failed
        cerr << "fork failed" << endl; // Output error to standard error
        exit(1);                            // Exit with error status
    }
    else if (rc == 0)
    {
        // Child process
        cout << "hello, I am child (pid:" << getpid() << ")" << endl;
    }
    else
    {
        // Parent process
        // Optional: Wait for the child to finish to ensure cleaner output order
        // wait(NULL);
        cout << "hello, I am parent of " << rc
                  << " (pid:" << getpid() << ")" << endl;
    }

    return 0; // Exit successfully
}
