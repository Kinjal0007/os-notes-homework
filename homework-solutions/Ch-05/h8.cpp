#include <iostream>
#include <unistd.h>
#include <cstdlib>
#include <sys/wait.h>

using namespace std;

int main(){
    int pipefd[2];

    if(pipe(pipefd) == -1){
        perror("pipe failed");
        exit(EXIT_FAILURE);
    }

    pid_t rc=fork();
    if(rc<0){
        perror("fork failed");
        exit(EXIT_FAILURE);
    }else if(rc==0){
        close(pipefd[0]);

        dup2(pipefd[1],STDOUT_FILENO);
        close(pipefd[1]);

        string input;
        getline(cin, input);
        cout<<"[Child 2 ] Received: "<< input <<endl;

        exit(EXIT_SUCCESS);
    }

    close(pipefd[0]);
    close(pipefd[1]);
    wait(nullptr);
    wait(nullptr);

    cout<<"[Parent] Both children have finished.\n";

    return 0;

}