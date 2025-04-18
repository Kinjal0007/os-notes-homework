#include <iostream>
#include <cstdlib>    // For exit()
#include <unistd.h>   // For fork(), execvp(), getpid()
#include <sys/wait.h> // For wait()
#include <cstring>    // For strdup() (POSIX function, common but technically not standard C++)
#include <vector>     // Although not used for exec args here, good C++ practice

using namespace std;

int main(int argc, char *argv[])
{
    cout << "Parent starting (pid:" << getpid() << ")" << endl;
    pid_t rc = fork();

    if (rc < 0)
    {
        // Fork failed
        cerr << "fork failed" << endl;
        exit(EXIT_FAILURE); // Use EXIT_FAILURE for errors
    }
    else if (rc == 0)
    {
        // --- Child Process ---
        cout << "Child executing (pid:" << getpid() << ")" << endl;

        // Prepare arguments for execvp.
        // execvp expects a NULL-terminated array of C-style strings (char*).
        // argv[0] is the program name, followed by arguments.
        char *myargs[3];
        // strdup allocates memory; in a real app, consider managing this
        // memory or using std::string and .c_str() carefully.
        // However, since execvp replaces the process image, memory leaks
        // here are only an issue if execvp *fails*.
        myargs[0] = strdup("wc");     // Program to run: word count
        myargs[1] = strdup("p3.cpp"); // Argument: the file to count (relative path)
        myargs[2] = NULL;             // Null terminator for the array

        // Attempt to replace this child process with "wc"
        execvp(myargs[0], myargs);

        // ---- If execvp returns, it means an error occurred ----
        perror("execvp failed"); // perror prints the system error message
        // Clean up allocated memory before exiting on error
        free(myargs[0]);
        free(myargs[1]);
        exit(EXIT_FAILURE); // Exit child with failure status
    }
    else
    {
        // --- Parent Process ---
        // Wait for the child process to complete its execution (running 'wc').
        int wait_status;
        pid_t wc_pid = waitpid(rc, &wait_status, 0); // Wait specifically for the child rc

        cout << "Parent finished waiting." << endl;

        if (wc_pid == -1)
        {
            perror("waitpid failed");
            exit(EXIT_FAILURE);
        }

        // Optional: Check how the child exited
        if (WIFEXITED(wait_status))
        {
            cout << "Parent: Child (pid:" << wc_pid << ") exited normally with status "
                 << WEXITSTATUS(wait_status) << "." << endl;
        }
        else if (WIFSIGNALED(wait_status))
        {
            cout << "Parent: Child (pid:" << wc_pid << ") killed by signal "
                 << WTERMSIG(wait_status) << "." << endl;
        }
        else
        {
            cout << "Parent: Child (pid:" << wc_pid << ") changed state unexpectedly." << endl;
        }

        cout << "Parent finishing (pid:" << getpid() << ")" << endl;
    }

    return EXIT_SUCCESS; // Use EXIT_SUCCESS for successful completion
}