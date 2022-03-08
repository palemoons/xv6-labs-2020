#include <kernel/types.h>
#include <kernel/stat.h>
#include <user/user.h>
#include <kernel/fs.h>

void find(char* path, char* file){
    struct stat st;
    struct dirent de;
    int fd;
    char* p;
    char buf[512];
    fd = open(path, 0);
    fstat(fd, &st);
    strcpy(buf, path);

    p = buf + strlen(buf);
    if(*(p - sizeof(char)) != '/')
        *p++ = '/';

    if(st.type == T_DIR){
        while(read(fd, &de, sizeof(de)) == sizeof(de)){
            if(de.inum==0 || strcmp(de.name, ".") == 0 || strcmp(de.name, "..") == 0){
                continue;
            }
            memmove(p, de.name, DIRSIZ); 
            p[DIRSIZ] = 0;
            if(strcmp(de.name, file) == 0){
                printf("%s\n", buf);
            }
            if(stat(buf, &st) < 0){
                fprintf(2, "find: cannot stat %s\n", buf);
                continue;
            }
            if(st.type == T_DIR){
                find(buf, file);
            }
        }
    }
}

int main(int argc, char* argv[]){
    struct stat st;
    int fd;
    if(argc < 3){
        fprintf(2, "insufficient params\n");
    }
    else{
        char* path=argv[1], *file=argv[2];
        if((fd = open(path, 0)) < 0){
            fprintf(2, "find: cannot open %s\n", path);
            exit(0);
        }

        if(fstat(fd, &st) < 0){
            fprintf(2, "find: cannot stat %s\n", path);
            close(fd);
            exit(0);
        }
        close(fd);

        find(path, file);
        
   }
    exit(0);
}
