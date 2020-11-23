#include <stdio.h>
#include <stdlib.h>
#include <dirent.h>
#include <sys/stat.h>
#include <sys/types.h>
#include <string.h>

int main(){
    DIR *current = opendir(".");
    int size = 0;
    struct dirent *item = readdir(current);
    struct stat meta;
    
    while(item){
        if (item->d_type == DT_REG)
        {
            stat(item->d_name, &meta);
            size +=  meta.st_size;
        }
        item = readdir(current);
    }
    printf("Statistics for directory: .\n");
    printf("Total Diectory Size: %d Bytes\n", size);
    rewinddir(current);
    item = readdir(current);
    printf("Directories:\n");
    while(item){
        if (item->d_type == DT_DIR){
            printf("\t%s\n", item->d_name);
        }
        item = readdir(current);
    }
    rewinddir(current);
    item = readdir(current);
    printf("Regular files:\n");
    while(item){
        if (item->d_type == DT_REG){
            stat(item->d_name, &meta);
            printf("\t%s\n", item->d_name);
        }
        item = readdir(current);
    }
    closedir(current);

}