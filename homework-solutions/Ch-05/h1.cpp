#include <iostream> // cout,cerr,endl
#include <unistd.h> // fork,getpid
#include <sys/wait.h> //wait
#include <cstdlib> //exit

using namespace std;

int main(){
    int x=100;
    cout<< "A value in parent process: "<<x<<endl;
    cout<<"Parent PID: "<<getpid()<<endl;
    pid_t rc =fork();

    if(rc<0){
        cerr<<"Fork Failed"<<endl;
        exit(EXIT_FAILURE);

    }else if(rc==0){
        cout<<"Child PID: "<<getpid()<< " Value of x before fork = "<<x<<endl;

        x=312;
        cout<<"Child PID: "<<getpid()<<" Value of x after modification = "<<x<<endl;

    } else {
        wait(nullptr);

        cout<< "Parent PID: "<<getpid()<<" Value of x after child process = "<<x<<endl;

        x = 231;

        cout<<"Parent PID:"<<getpid()<<" Value of x after it's own modification = "<<x<<endl;
    }

    return 0;
}

