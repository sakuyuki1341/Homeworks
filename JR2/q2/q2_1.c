#include <stdio.h>

  int main(int argc, char *argv[]) {
    long   x[100];
    char  *typeStr = argv[1];
    void  *ptr = (void*)strtol(argv[2], NULL, 16);
    int    num = atoi(argv[3]);
    char  *cptr= (char*)x;
    int i;
    for (i=0; i<100*sizeof(long); i++)
    cptr[i] = i + 0x10;

    if (!strcmp(typeStr, "char")) {
      char *ptrnew;
      char value;
      ptrnew = ((char*)ptr) + num;
      value  = *((char*)cptr+num);
      printf("%p 0x%x\n", ptrnew, value);
    } else if (!strcmp(typeStr, "short")) {
      short *ptrnew;
      short value;
      ptrnew = ((short*)ptr) + num;
      value  = *((short*)cptr+num);
      printf("%p 0x%x\n", ptrnew, value);
    } else if (!strcmp(typeStr, "int")) {
      int  *ptrnew;
      int  value;
      ptrnew = ((int*)ptr) + num;
      value  = *((int*)cptr+num);
      printf("%p 0x%x\n", ptrnew, value);
    } else if (!strcmp(typeStr, "long")) {
      long *ptrnew;
      long value;
      ptrnew = ((long*)ptr) + num;
      value  = *((long*)cptr+num);
      printf("%p 0x%lx\n", ptrnew, value);
    }

    return 0;
  }
