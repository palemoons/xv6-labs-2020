#include <kernel/types.h>
#include <kernel/stat.h>
#include <user/user.h>

void prime(int lp[]){
    int p[2];
    int n, tmp;
    if(read(lp[0], &n, sizeof(n)) > 0){// get first number from left pipe.
        printf("prime %d\n", n);
        pipe(p);
        if(fork()==0){
            close(p[1]);
            prime(p);
            close(p[0]);
            exit(0);
        }
        else{ 
            while(read(lp[0], &tmp, sizeof(tmp)) > 0){
                if(tmp % n != 0) write(p[1], &tmp, sizeof(tmp));
            }
            close(p[0]);
            close(p[1]);
            close(lp[0]);
            wait(0);
            exit(0);
        }
    }
}
int main(int argc, char* argv[]){
    int p[2];
    pipe(p);
    for(int i=2;i<36;i++) write(p[1], &i, sizeof(i));
    close(p[1]);
    prime(p);
    close(p[0]);
    exit(0);
}

