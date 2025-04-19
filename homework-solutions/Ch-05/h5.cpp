#include <iostream>
#include <unistd.h>
#include <sys/wait.h>
#include <stdlib.h>

using namespace std;

int main(){
    pid_t rc=fork();

    if(rc<0){
        perror("fork failed");
        exit(EXIT_FAILURE);
    }else if(rc==0){
        cout<<"[Child] PID: "<<getpid() <<" | PPID: "<<getppid()<<endl;
        sleep(2);
        cout<<"[Child] Finished work.\n";

        exit(42);
    }else {
        cout<<"[Parent] Waiting for child to finish...\n";

        int status;
        pid_t wait_result=wait(&status);

        cout<<"[Parent] Child process with PID "<<wait_result<< " finished.\n";

        if (WIFEXITED(status)) {
            cout << "[Parent] Child exited with status: " << WEXITSTATUS(status) << endl;
        } else {
            cout << "[Parent] Child did not exit normally.\n";
        }
    }
    return 0;
}