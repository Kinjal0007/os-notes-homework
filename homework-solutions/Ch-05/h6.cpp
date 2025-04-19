#include <iostream>
#include <unistd.h>
#include <sys/wait.h>
#include <cstdlib>

using namespace std;

int main(){
    pid_t rc=fork();

    if(rc<0){
        perror("fork failed");
        exit(EXIT_FAILURE);
    }else if(rc==0){
        cout<<"[Child] Closing STDOUT_FILENO...\n";
        close(STDOUT_FILENO);


        cout<<"[Child] This message will not appear on the screen.\n";
        fflush(stdout);

        exit(EXIT_SUCCESS);
    }else {
        
        wait(nullptr);
        cout<<"[Parent] Child has finished.\n";
    }
    return 0;
}