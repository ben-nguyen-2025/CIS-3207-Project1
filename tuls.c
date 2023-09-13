#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <dirent.h>
#include <sys/types.h>
#include <sys/stat.h>
#include <unistd.h>
#include <errno.h>

void fileRecursive(char* pathName, int indentLevel);
int isDirectory(const char *path);

int main(int argc, char *argv[]) {
    
    if (argv[1] != NULL) { //specified folder name is present, i.e. starting recursive backtracking
        if (!isDirectory(argv[1])) {
            printf("%s", "tuls: cannot open directory");
            exit(1);
        }
        printf("[%s]\n", argv[1]);
        char *startPath = (char *) malloc(4096);
        strcat(startPath, "./");
        fileRecursive(strcat(startPath, argv[1]), 1); //second parameter = indentLevel (successive levels are indented based on depth)
       //fileRecursive(argv[1]);
    }
   
    struct dirent **namelist;
    int n;
    //scandir example from pdf of project part A
    n=scandir(".",&namelist,NULL, alphasort);
    if (n == -1) {
        printf("%s\n", "tuls: cannot open directory");
        exit(1);
    }
    while (n--)
    {
        char *finalWord = (char *) malloc(4096);
        char *fileName = namelist[n]->d_name;
        if (strncmp(fileName, ".", 1) != 0) {
            if (isDirectory(fileName)) { //folder denoted with braces ex.: [folder1]
                strcat(finalWord, "[");
                strcat(finalWord, fileName);
                strcat(finalWord, "]");
            }
            else { //file denoted with arrows ex.: -> tuls.c
                strcat(finalWord, "-> ");
                strcat(finalWord, fileName);
            }
            printf("%s\n", finalWord);
            
        }
        finalWord[0] = '\0';
        free(namelist[n]);
        free(finalWord);
        
    }
    
    
    
    return 0;
}

int isDirectory(const char *path) { //macro to determine if something is directory 
   struct stat statbuf; //from https://stackoverflow.com/questions/4553012/checking-if-a-file-is-a-directory-or-just-a-file
   if (stat(path, &statbuf) != 0)
       return 0;
   return S_ISDIR(statbuf.st_mode);
}

void fileRecursive(char* pathName, int indentLevel) {
    //puts("hi");
    
    struct dirent **namelist;
    int n;
    n=scandir(pathName, &namelist, NULL, alphasort);
    if (n == -1) { //recursive base case: no more files to parse through directory
        return;
    } 
    else {
        //printf("%s", pathName);

        while (n--)
        {
            char *finalWord = (char *) malloc(4096);
            char *fileName = namelist[n]->d_name;
            if (strncmp(fileName, ".", 1) != 0) { 
                char *tempPath = (char *) malloc(4096);
                strcpy(tempPath, pathName);
                strcat(tempPath, "/");
                strcat(tempPath, fileName);
                if (isDirectory(tempPath)) { //it is a folder and further recursive calls must be made
                    strcat(finalWord, "[");
                    strcat(finalWord, fileName);
                    strcat(finalWord, "]");
                    //printf("%s\n", finalWord);

                    fileRecursive(tempPath, indentLevel + 1);
                }
                else { //it is a word and can be printed
                    strcat(finalWord, "-> ");
                    strcat(finalWord, fileName);
                }
                for (int i = 0; i < indentLevel; i++) {
                    printf("%s", "    ");
                }
                printf("%s\n", finalWord);
                
            }
            finalWord[0] = '\0';
            free(namelist[n]);
            free(finalWord);
        
        }
    }
}
