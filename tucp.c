#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <dirent.h>
#include <sys/stat.h>
#include <sys/types.h>
#include <unistd.h>
#include <errno.h>


char *readFile(char *path);
void copyFile(char *source, char *destination);
int isDirectory(const char *path);


int main(int argc, char *argv[]) { 
    //char *path = (char *) malloc(4096);
    struct stat itemStats;

    if (argc < 3) { // ./tucp apple bear --> argc = 3
        printf("%s", "error: need at least 2 file/directory arguments");
        exit(EXIT_FAILURE);
    }
    //find properties of last item in function (directory or file?)
    //deal with accordingly based on number of items
    char * destination = argv[argc - 1]; //last item in argv = file/directory to copy into

    if (!isDirectory(destination)) { //checks if item is not a directory (is therefore a file)
        if (argc > 3) {
            printf("%s", "error: trying to copy multiple files into destination file");
            exit(EXIT_FAILURE);
        }

        if (stat(argv[1], &itemStats) == 0) { //checks if item exists
            copyFile(argv[1], destination);
        } else { 
            printf("error: source file doesn't exist");
            exit(EXIT_FAILURE);
        }

    }
    else { //must be directory
        for (unsigned int i = 1; i < argc - 1; i++) {
            char *path = (char *) malloc(4096);
            strcpy(path, destination);
           // printf("%d", i);
            if (stat(argv[i], &itemStats) == 0) { //checks if item exists
                strcat(path, "/");
                strcat(path, argv[i]);
                copyFile(argv[i], path);
                
                free(path); //frees path memory, allowing for cycling through files 
            } else {
                printf("error: source file doesn't exist");
                exit(EXIT_FAILURE);
            }
            
        }
        
    }
   exit(EXIT_SUCCESS);
}

int isDirectory(const char *path) { //macro to determine if something is directory or file
   struct stat statbuf; //from https://stackoverflow.com/questions/4553012/checking-if-a-file-is-a-directory-or-just-a-file
   if (stat(path, &statbuf) != 0)
       return 0;
   return S_ISDIR(statbuf.st_mode); //1 if directory, 0 if not
}

char *readFile(char *path) { //assumes file exists
    FILE *fPtr = fopen(path, "rb");
    struct stat itemStats;
    stat(path, &itemStats);
    char *fileContent = (char *) malloc(itemStats.st_size);
    fread(fileContent, 1, itemStats.st_size, fPtr);
    fclose(fPtr);
    return fileContent;
}

void copyFile(char *source, char *destination) {
    FILE *fPtr = fopen(destination, "wb");
    struct stat itemStats;
    stat(source, &itemStats);
    char *fileContents = readFile(source);
    fwrite(fileContents, 1, itemStats.st_size, fPtr);
    fclose(fPtr);
    free(fileContents);
}


