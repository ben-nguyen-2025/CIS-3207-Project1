

#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <sys/types.h>
#include <dirent.h>

int main(int argc, char *argv[]) {
    struct dirent **namelist;
    int n;
    //from pdf of project part A
    n=scandir(".",&namelist,NULL, alphasort);
    if (n == -1) {
        perror("scandir");
        exit(EXIT_FAILURE);
    }
    while (n--)
    {
        printf("%s\n",namelist[n] -> d_name);
        free(namelist[n]);
    }

    
    

    return 0;
}