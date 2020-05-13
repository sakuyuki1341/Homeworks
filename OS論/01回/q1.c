 #include <stdio.h>
 #include <time.h>
 int
 main(int argc, char **argv)
 {
         long now;
         time(&now);
         printf("now = %d\n", now);
         return 0;
 }