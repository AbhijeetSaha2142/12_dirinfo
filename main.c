#include <stdio.h>
#include <stdlib.h>
#include <dirent.h>
#include <sys/stat.h>
#include <sys/types.h>
#include <errno.h>
#include <string.h>

int main(int argc, char **argv){
    DIR *dir;
    if (argc != 1){ // if given command line arg for directory open that
        dir = opendir(argv[1]);
    }

    else{ // otherwise ask for directory through stdin
        char filename [256];
        printf("Choose a directory: ");
        fgets(filename, sizeof(filename), stdin);
        *strchr(filename, '\n') = 0; // replace \n char with terminating 0
        dir = opendir(filename);
    }
    if (dir == NULL){ // in case something went wrong when opening
        printf("errno: %d\terror: %s\n", errno, strerror(errno));
    }
    int size = 0;
    struct dirent *item = readdir(dir);
    struct stat meta;
    
    while(item){
        if (item->d_type == DT_REG){
            stat(item->d_name, &meta);
            size +=  meta.st_size;
        }
        item = readdir(dir);
    }
    printf("Statistics for directory: .\n");
    printf("Total Diectory Size: %d Bytes\n", size);
    rewinddir(dir);
    item = readdir(dir);
    printf("Directories:\n");
    while(item){
        if (item->d_type == DT_DIR){
            printf("\t%s\n", item->d_name);
        }
        item = readdir(dir);
    }
    rewinddir(dir);
    item = readdir(dir);
    printf("Regular files:\n");
    while(item){
        if (item->d_type == DT_REG){
            printf("\t%s\n", item->d_name);
        }
        item = readdir(dir);
    }
    closedir(dir);

}
