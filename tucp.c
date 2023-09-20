#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <dirent.h>
#include <sys/stat.h>
#include <sys/types.h>
#include <unistd.h>
#include <errno.h>
#define MAXFILEREAD 10000000



char *readFile(char *path, int maxLength, FILE *fPtr);
void copyFile(char *source, char *destination, FILE *fPtr);
char *readPhoto(char *path, int maxLength, FILE *fPtr);
int isDirectory(const char *path);


int main(int argc, char *argv[]) { 
    //char *path = (char *) malloc(4096);
    FILE *fptr;
    struct stat itemStats;

    if (argc < 3) { // ./tucp apple bear --> argc = 3
        printf("%s", "error: need at least 2 file/directory arguments");
        exit(EXIT_FAILURE);
    }
    //find properties of last item in function (directory or file?)
    //deal with accordingly based on number of items
    char * destination = argv[argc - 1];
    printf("%d", isDirectory("rat.jpg"));
    /*
    if (stat(destination, &itemStats) == -1 ) { //checks if item does not exist
        fptr = fopen(destination, "w"); //if it doesn't, creates file 
        printf("file didn't exist");
    }
    */

    if (!isDirectory(destination)) { //checks if item is not a directory (is then a file)
        fptr = fopen(destination, "w"); //if it doesn't exist, creates file 
        //fprintf(fptr, "file didn't exist");
        if (argc > 3) {
            printf("%s", "error: trying to copy multiple files into destination file");
            exit(EXIT_FAILURE);
        }

        if (stat(argv[1], &itemStats) == 0) { //checks if item exists
            copyFile(argv[1], destination, fptr);
            //char *fileContents = readFile(argv[1], MAXFILEREAD, fptr);
            //printf("%s", fileContents);
            //fprintf(fptr, "%s", fileContents);
        } else {
            printf("error: copied from file argument %d doesn't exist", 1);
            exit(EXIT_FAILURE);
        }

    }
    else { //must be directory

    }
    //printf("%d", isDirectory(destination));

   
    
    
   //printf("%s", destination);

   exit(EXIT_SUCCESS);
}

int isDirectory(const char *path) { //macro to determine if something is directory or file
   struct stat statbuf; //from https://stackoverflow.com/questions/4553012/checking-if-a-file-is-a-directory-or-just-a-file
   if (stat(path, &statbuf) != 0)
       return 0;
   return S_ISDIR(statbuf.st_mode); //1 if directory, 0 if not
}

char *readFile(char *path, int maxLength, FILE *fPtr) { //assumes file exists
    fPtr = fopen(path, "r");
    char *fileContent = (char *) malloc(maxLength);
    fgets(fileContent, maxLength, fPtr);
    return fileContent;
}

void copyFile(char *source, char *destination, FILE *fPtr) {
    char *fileContents = readFile(source, MAXFILEREAD, fPtr);
    fprintf(fPtr, "%s", fileContents);
}
