#include <kernel/types.h>
#include <kernel/stat.h>
#include <user/user.h>
#include <kernel/param.h>

int main(int argc, char* argv[]){
    if(argc < 2){
        fprintf(2, "usage: xargs <cmd>...\n");
        exit(1);
    }
    char* params[MAXARG];
    for(int i = 1;i < argc;i++){
        params[i - 1] = argv[i];
    }
    char ch;
    do{
        int i = argc - 1, j = 0;
        char buf[MAXARG][32];
        memset(buf, 0, MAXARG * 32);
        while(read(0, &ch, sizeof(char)) > 0){
            if(ch == ' '){
                buf[i][j] = '\0';
                params[i] = buf[i];
                i++;
                j = 0;
                continue;
            }
            if(ch == '\n'){
                buf[i][j] = '\0';
                params[i] = buf[i];
                i++;
                break;
            }
            if(i >= MAXARG){
                fprintf(2, "error: too many args\n");
                exit(1);
            }
            buf[i][j++] = ch;
        }
        params[i] = 0;
        
        if(fork() == 0){
            exec(argv[1], params);
        }
        else{
            wait(0);
        }
    } while(read(0, &ch, sizeof(char)) > 0);
    exit(0);
}
