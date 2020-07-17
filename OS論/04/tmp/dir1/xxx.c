#include <stdio.h>
#include <stdlib.h>
#include <time.h>
#include <sys/types.h>
#include <sys/stat.h>
#include <pwd.h>
#include <grp.h>
main(int argc, char **argv)
{
        struct stat st;
        struct passwd *pw;
        struct group *gr;
        if (argc == 1) {
                fprintf(stderr,"usage: %s file\n",*argv);
                return 1;
        }
        if (lstat(argv[1], &st) < 0) {
                perror(argv[1]);
                return 1;
        }
        printf("st_dev = %#x\n",st.st_dev);
        printf("st_ino = %d\n",st.st_ino);
        printf("st_mode = %#o\n",st.st_mode);
        printf("st_nlink = %d\n",st.st_nlink);
        printf("st_uid = %d",st.st_uid);
        if (pw = (struct passwd *)getpwuid(st.st_uid))
                printf(" (%s)",pw->pw_name);
        printf("\n");
        printf("st_gid = %d",st.st_gid);
        if (gr = (struct group *)getgrgid(st.st_gid))
                printf(" (%s)",gr->gr_name);
        printf("\n");
        printf("st_size = %d\n",st.st_size);
        printf("st_atime = %d, %s",st.st_atime,ctime(&st.st_atime));
        printf("st_mtime = %d, %s",st.st_mtime,ctime(&st.st_mtime));
        printf("st_ctime = %d, %s",st.st_ctime,ctime(&st.st_ctime));
        printf("st_blksize = %d\n",st.st_blksize);
        printf("st_blocks = %d\n",st.st_blocks);
        return 0;
}
