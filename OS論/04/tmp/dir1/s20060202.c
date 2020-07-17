#include <stdio.h>
#include <unistd.h>
#include <stdlib.h>
#include <dirent.h>
main(int argc, char **argv)
{
        DIR *dp;
        struct dirent *dir;
        if (argc == 1) {
                fprintf(stderr,"usage: %s directory\n",argv[0]);
                return 1;
        }
        if ((dp = opendir(argv[1])) == NULL) {
                perror(argv[1]);
                return 1;
       }
        while((dir = readdir(dp)) != NULL) {
                printf("d_fileno = %6d, ",dir->d_fileno);
                printf("d_reclen = %3d, ",dir->d_reclen);
                printf("d_name = \"%s\"\n",dir->d_name);
        }
        return 0;
}
