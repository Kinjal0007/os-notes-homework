#include <iostream>
#include <cstdlib>    // For exit(), EXIT_SUCCESS, EXIT_FAILURE
#include <unistd.h>   // For fork(), execvp(), getpid(), close(), STDOUT_FILENO
#include <sys/wait.h> // For waitpid()
#include <fcntl.h>    // For open() and file control flags
#include <sys/stat.h> // For mode constants
#include <cstring>    // For strdup(), strerror()
#include <cerrno>     // For errno
#include <limits.h>   // For PATH_MAX
#include <unistd.h>   // For getcwd()

using namespace std;

/*
 * This program demonstrates I/O redirection using fork(), exec(), and file descriptors.
 * It creates a child process that runs the 'wc' (word count) command and redirects its
 * output to a file instead of the terminal.
 *
 * Key Concepts:
 * 1. Process Creation (fork)
 * 2. File Descriptors and I/O Redirection
 * 3. Program Execution (exec)
 * 4. Process Synchronization (wait)
 */
int main(int argc, char *argv[])
{
    // Get and display the current working directory for debugging
    // PATH_MAX is the maximum length for a file path on this system
    char cwd[PATH_MAX];
    if (getcwd(cwd, sizeof(cwd)) != NULL)
    {
        cout << "Current working directory: " << cwd << endl;
    }
    else
    {
        cerr << "getcwd() error: " << strerror(errno) << endl;
    }

    // Create a new process
    // fork() returns:
    // - Negative: Error occurred
    // - Zero: We're in the child process
    // - Positive: We're in the parent process (value is child's PID)
    pid_t rc = fork();

    if (rc < 0)
    {
        // Fork failed - print error and exit
        cerr << "fork failed: " << strerror(errno) << endl;
        exit(EXIT_FAILURE);
    }
    else if (rc == 0)
    {
        // ====== CHILD PROCESS ======
        // This code runs in the new child process
        cout << "Child process starting (pid:" << getpid() << ")" << endl;

        // Verify child's working directory (inherited from parent)
        if (getcwd(cwd, sizeof(cwd)) != NULL)
        {
            cout << "Child working directory: " << cwd << endl;
        }

        // Step 1: Close standard output (file descriptor 1)
        // This disconnects the process from the terminal output
        if (close(STDOUT_FILENO) == -1)
        {
            cerr << "Child failed to close stdout: " << strerror(errno) << endl;
            exit(EXIT_FAILURE);
        }

        // Step 2: Set up the output file path
        // Using absolute paths to avoid directory-related issues
        string output_path = string(cwd) + "/p4.output";
        string source_path = string(cwd) + "/p4.cpp";

        cout << "Attempting to open: " << output_path << endl;

        // Step 3: Open the output file
        // - O_CREAT: Create file if it doesn't exist
        // - O_WRONLY: Open for writing only
        // - O_TRUNC: If file exists, truncate to zero length
        // - S_IRUSR | S_IWUSR: User read/write permissions (0600)
        int output_fd = open(output_path.c_str(),
                             O_CREAT | O_WRONLY | O_TRUNC,
                             S_IRUSR | S_IWUSR);

        // Check if file opened successfully
        if (output_fd == -1)
        {
            cerr << "Child failed to open " << output_path << " for writing: " << strerror(errno) << endl;
            exit(EXIT_FAILURE);
        }

        // Verify that we got file descriptor 1 (standard output)
        // This is crucial for redirection to work properly
        if (output_fd != STDOUT_FILENO)
        {
            cerr << "Warning: Expected fd 1, got " << output_fd << endl;
        }

        // Step 4: Prepare arguments for wc command
        // execvp expects a NULL-terminated array of C-strings
        char *myargs[3];
        myargs[0] = strdup("wc");                // Program name
        myargs[1] = strdup(source_path.c_str()); // File to count
        myargs[2] = NULL;                        // Array terminator

        cout << "Executing wc on: " << source_path << endl;

        // Step 5: Replace current process with 'wc'
        // execvp searches PATH for the program and passes the arguments
        execvp(myargs[0], myargs);

        // If execvp returns, it means it failed
        // (successful execvp never returns)
        cerr << "Child execvp failed: " << strerror(errno) << endl;
        free(myargs[0]);
        free(myargs[1]);
        exit(EXIT_FAILURE);
    }
    else
    {
        // ====== PARENT PROCESS ======
        // This code runs in the original process
        cout << "Parent process waiting (pid:" << getpid() << ")" << endl;

        // Wait for child process to complete
        int wait_status;
        pid_t finished_pid = waitpid(rc, &wait_status, 0);

        // Check if wait itself failed
        if (finished_pid == -1)
        {
            cerr << "Parent waitpid failed: " << strerror(errno) << endl;
            exit(EXIT_FAILURE);
        }

        // Check how the child process terminated
        if (WIFEXITED(wait_status))
        {
            // Child terminated normally (with exit)
            cout << "Parent: Child exited with status " << WEXITSTATUS(wait_status) << endl;
        }
        else
        {
            // Child terminated abnormally (e.g., crashed)
            cout << "Parent: Child terminated abnormally" << endl;
        }
    }

    return EXIT_SUCCESS;
}