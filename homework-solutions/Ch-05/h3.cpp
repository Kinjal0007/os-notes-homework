#include <iostream>
#include <unistd.h>
#include <sys/types.h>
#include <cstdlib>
#include <cstring>
#include <cerrno>

using namespace std;

int main(){
    int pipefd[2];

    if (pipe(pipefd) == -1){
        cerr << "Pipe creation failed: "<< strerror(errno) <<endl;
        exit(EXIT_FAILURE);
    }

    pid_t rc = fork();

    if(rc < 0 ){
        cerr << "Fork failed: " << strerror(errno) <<endl;
        exit(EXIT_FAILURE);
    }else if(rc==0){
        cout<< "hello" << endl;

        close(pipefd[0]);
        write(pipefd[1] , "1" , 1);
        close(pipefd[1]);

        exit(EXIT_SUCCESS);
    } else {
        close(pipefd[1]);

        char buffer;
        read(pipefd[0], &buffer , 1);
        close(pipefd[0]);

        cout << "goodbye" <<endl;
    }
    return 0;
}