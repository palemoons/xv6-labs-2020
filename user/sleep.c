// do nothing for a little while
// throw error if no param provided

#include "kernel/types.h"
#include "kernel/stat.h"
#include "user/user.h"

int main(int argc, char* argv[]){
    if(argc<2){
        fprintf(2, "insufficient params\n");
        exit(0);
    }
    else{
        sleep(atoi(argv[1]));
        exit(0);
    }
}

