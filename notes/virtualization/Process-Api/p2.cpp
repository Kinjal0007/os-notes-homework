#include <iostream>
#include <cstdlib>
#include <unistd.h>
#include <sys/wait.h>

using namespace std;

int main(int argc, char *argv[])
{
    cout << "hello world (pid:" << getpid() << ")" << endl;
    pid_t rc = fork();

    if (rc < 0)
    {
        // Fork failed
        cerr << "fork failed" << endl;
        exit(1);
    }
    else if (rc == 0)
    {
        // Child process
        cout << "hello, I am child (pid:" << getpid() << ")" << endl;
    }
    else
    {
        // Parent process
        int wc = wait(NULL); // Wait for the child to finish
        cout << "hello, I am parent of " << rc
             << " (wc:" << wc << ")" // wc should also be the child's pid
             << " (pid:" << getpid() << ")" << endl;
    }

    return 0;
}