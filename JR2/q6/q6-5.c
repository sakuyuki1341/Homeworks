#include <ctype.h>
#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#define MAXLINE 1000

struct csv { int num; char *cell[1]; };
typedef struct csv *csvp;
int week = 1;

static char *readline(FILE *f) {
  char buf[MAXLINE], *str;
  if(fgets(buf, MAXLINE, f) == NULL) { return NULL; }
  int len = strlen(buf);
  if(buf[len-1] == '\n') { buf[--len] = '\0'; }
  str = (char*)malloc(len+1); strcpy(str, buf); return str;
}

static csvp read1(FILE *f) {
  char *arr[100], *s = readline(f); if(s == NULL) { return NULL; }
  int i = 0;
  for(arr[i++] = s; *s != '\0'; ++s) {
    if(*s == ' ') { *s = '\0'; arr[i++] = s+1; }
  }
  csvp r = (csvp)malloc(sizeof(struct csv) + i*sizeof(char*));
  r->num = i;
  for(i = 0; i < r->num; ++i) { r->cell[i] = arr[i]; }
  return r;
}

int csv_read(char *fname, int limit, csvp arr[]) {
  int size = 0; csvp line;
  FILE *f = fopen(fname, "rb"); if(f == NULL) { return -1; }
  while((line = read1(f)) != NULL) {
    if(size+1 >= limit) { size = -2; break; }
    arr[size++] = line;
  }
  fclose(f); return size;
}

void csv_write(char *fname, int size, csvp arr[]) {
  FILE *f = fopen(fname, "wb"); if(f == NULL) { return; }
  for(int i = 0; i < size; ++i) {
    fprintf(f, "%s", arr[i]->cell[0]);
    for(int j = 1; j < arr[i]->num; ++j) { fprintf(f, ",%s", arr[i]->cell[j]); }
    fprintf(f, "\n");
  }
  fclose(f);
}

static int cmp1(const void *x, const void *y) {
    csvp a = *(csvp*)x, b = *(csvp*)y;
    double a_win = atof(a->cell[1]), b_win = atof(b->cell[1]);
    double a_lose = atof(a->cell[2]), b_lose = atof(b->cell[2]);
    double a_last = atof(a->cell[4]), b_last = atof(b->cell[4]);

    if(a_win/(a_win+a_lose) > b_win/(b_win+b_lose)) {
        return -1;
    } else if(a_win/(a_win+a_lose) < b_win/(b_win+b_lose)) {
        return 1;
    }
    if(a_win > b_win) {
        return -1;
    } else if(a_win < b_win) {
        return 1;
    }
    if(a_last > b_last) {
        return 1;
    } else {
        return -1;
    }
}

int main(int argc,char *argv[]){
	csvp data[1000], p;
    int size = csv_read(argv[1], 1000, data);
    if(size <= 0) {
        return 0;
    }
    qsort(data, size, sizeof(csvp), cmp1);
    for(int i = 0; i < size; ++i) {
      p = data[i];
      printf("%s ", p->cell[0]);
    }
    return 0;
}
