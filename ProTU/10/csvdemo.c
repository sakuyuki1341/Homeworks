// csvdemo.c --- demonstration for csv_read.
#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include "csv.h"

// #define ENSHU_A
#define ENSHU_B

#ifdef ENSHU_A
int main(int argc, char *argv[]) {
  csvp data[1000], p;
  int size = csv_read(argv[1], 1000, data);
  if(size <= 0) { return 0; }
//qsort(data+1, size-1, sizeof(csvp), cmp1); // **
  p = data[0];
  printf("%11s %11s %11s\n", p->cell[0], p->cell[1], p->cell[2]);
  for(int i = 1; i < size; ++i) {
    p = data[i];
    printf("%11s %11.3f %11.3f\n",
           p->cell[0], atof(p->cell[1]), atof(p->cell[2])/12.0);
  }
  return 0;
}
#endif

#ifdef ENSHU_B
int main(int argc, char *argv[]) {
    csvp data[1000], p;
    int size = csv_read(argv[1], 1000, data);
    if(size <= 0) { return 0; }
  //qsort(data+1, size-1, sizeof(csvp), cmp1); // **
    p = data[0];
    printf("%11s %11s %11s\n", p->cell[0], p->cell[1], p->cell[2]);
    float max = atof(data[1]->cell[2]);
    int i, j = 1;
    for(i = 1; i < size; ++i) {
        p = data[i];
        if(max < atof(p->cell[2])) {
            max = atof(p->cell[2]);
            j = i;
        }
    }
    printf("%11s %11.3f %11.3f\n", data[j]->cell[0], atof(data[j]->cell[1]), atof(data[j]->cell[2]));
    return 0;
}
#endif
