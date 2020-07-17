#include <stdio.h>
#include <stdlib.h>
#include <unistd.h>
main()
{
        execl("./s2020063002","s2020063002",NULL);
        perror("execl");
        exit(0);
}
