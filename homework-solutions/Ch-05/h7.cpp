#include <iostream>
#include <unistd.h>   // for fork(), close(), STDOUT_FILENO
#include <sys/wait.h> // for wait()
#include <cstdlib>    // for exit()

using namespace std;

int main() {
    pid_t pid = fork();

    if (pid < 0) {
        perror("fork failed");
        exit(EXIT_FAILURE);
    } else if (pid == 0) {

        cout << "[Child] Closing STDOUT_FILENO...\n";
        close(STDOUT_FILENO); 

        printf("[Child] This message will not appear.\n");
        fflush(stdout);

        exit(EXIT_SUCCESS);
    } else {

        wait(nullptr); 
        cout << "[Parent] Child has finished.\n";
    }

    return 0;
}
