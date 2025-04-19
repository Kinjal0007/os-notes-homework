#define _GNU_SOURCE
#include <iostream>
#include <unistd.h>
#include <sys/wait.h>
#include <cstdlib>
#include <cstring>


using namespace std;

// Path is specified explicitly
void execl()
{
    cout << "\n[excel] Running /bin/ls with execl... \n";
    execl("/bin/ls", "ls", "-l", nullptr);
    perror("execl failed");
}

// Path allows custom env
void execle()
{
    cout << "\n[excel] Running /bin/ls with execle... \n";
    char* envp[] = {nullptr};
    execle("/bin/ls", "ls", "-l", nullptr, envp);
    perror("execle failed");
}

// Looks up "ls" using path env variables
void execlp()
{
    cout << "\n[excel] Running /bin/ls with execlp... \n";
    char* envp[] = {nullptr};
    execlp("/bin/ls", "ls", "-l", nullptr);
    perror("execlp failed");
}

// Similar to excel(args as an array)
void execv()
{
    cout << "\n[excel] Running /bin/ls with execv... \n";
    char* args[] = {(char*)"ls", (char*)"-1", nullptr};
    execv("/bin/ls", args);
    perror("execv failed");
}

// Path + an array of args
void execvp()
{
    cout << "\n[excel] Running /bin/ls with execvp... \n";
    char* args[] = {(char*)"ls", (char*)"-1", nullptr};
    execvp("ls", args);
    perror("execvp failed");
}

void fork_and_run(void (*func)()){
    pid_t rc=fork();

    if(rc<0){
        perror("fork failed");
        exit(EXIT_FAILURE);
    }else if(rc==0){
        func();
        exit(EXIT_FAILURE);
    }else{
        waitpid(rc,nullptr,0);
    }
}

int main(){
    fork_and_run(execl);
    fork_and_run(execle);
    fork_and_run(execlp);
    fork_and_run(execv);
    fork_and_run(execvp);

    cout<<"\n[Parent] All exec variants executed.\n";
}
