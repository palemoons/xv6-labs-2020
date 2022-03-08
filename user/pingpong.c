// ''ping-pong'' a byte between two processes over a pair of pipes, one for each direction

#include "kernel/types.h"
#include "kernel/stat.h"
#include "user/user.h"

int main(int argc, char* argv[]){
    int pp[2],cp[2];//parent&child pair
    char byte='0';
    pipe(pp);
    pipe(cp);
    if(fork()==0){//child process
        int pid=getpid();
        char str;
        read(pp[0], &str, 1);
        printf("%d: received ping\n", pid);
        write(cp[1], &byte, 1);
    } else{
        int pid=getpid();
        char str;
        write(pp[1], &byte, 1);
        read(cp[0], &str, 1);
        printf("%d: received pong\n", pid);
    }
    exit(0);
}    
