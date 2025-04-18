#include <iostream> // cout,cerr,endl
#include <unistd.h> // fork,getpid
#include <sys/wait.h> //wait
#include <cstdlib> //exit

using namespace std;

int main(){
    int a=100;
    cout<< "A value in parent process: "<<a<<endl;
}

