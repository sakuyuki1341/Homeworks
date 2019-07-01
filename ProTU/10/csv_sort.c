// csvdemo_1.c --- demonstration for csv_read w/ sorting.
#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include "csv.h"

// #define ENSHU_EX
// #define ENSHU_A
 #define ENSHU_C

static int cmp1(const void *x, const void *y) { // comp-fn.
  csvp a = *(csvp*)x, b = *(csvp*)y;
  return strcmp(a->cell[0], b->cell[0]);
}

static int cmp2(const void *x, const void *y) { // comp-fn.
  csvp a = *(csvp*)x, b = *(csvp*)y;
  if(strcmp(a->cell[0], b->cell[0]) < 0) {
      return 1;
  } else if(strcmp(a->cell[0], b->cell[0]) > 0) {
      return -1;
  } else {
      return 0;
  }
}

static int cmp4(const void *x, const void *y) {
    csvp a = *(csvp*)x, b = *(csvp*)y;
    if(atof(a->cell[1]) > atof(b->cell[1])) {
        return 1;
    } else if (atof(a->cell[1]) < atof(b->cell[1])) {
        return -1;
    } else {
        return strcmp(a->cell[0], b->cell[0]);
     }
}

#ifdef ENSHU_EX
int main(int argc, char *argv[]) {
  csvp data[1000], p;
  int size = csv_read(argv[1], 1000, data);
  if(size <= 0) { return 0; }
  qsort(data+1, size-1, sizeof(csvp), cmp1); // **
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

#ifdef ENSHU_A
int main(int argc, char *argv[]) {
  csvp data[1000], p;
  int size = csv_read(argv[1], 1000, data);
  if(size <= 0) { return 0; }
  qsort(data+1, size-1, sizeof(csvp), cmp2); // **
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

#ifdef ENSHU_C
int main(int argc, char *argv[]) {
  csvp data[1000], p;
  int size = csv_read(argv[1], 1000, data);
  if(size <= 0) { return 0; }
  qsort(data+1, size-1, sizeof(csvp), cmp4); // **
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
