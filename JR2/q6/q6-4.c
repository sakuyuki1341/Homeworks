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
    if(atoi(a->cell[week]) > atoi(b->cell[week])) {
        return -1;
    } else if (atoi(a->cell[week]) < atoi(b->cell[week])) {
        return 1;
    } else {
        return strcmp(a->cell[0], b->cell[0]);
    }
}

static int cmp2(const void *x, const void *y) {
    csvp a = *(csvp*)x, b = *(csvp*)y;
    int sum_a = 0, sum_b = 0;
    for(int i = 1; i < 7; i++) {
        sum_a += atoi(a->cell[i]);
        sum_b += atoi(b->cell[i]);
    }
    if(sum_a > sum_b) {
        return -1;
    } else if (sum_a < sum_b) {
        return 1;
    } else {
        return strcmp(a->cell[0], b->cell[0]);
    }
}

int main(int argc,char *argv[]){
	csvp data[1000], p;
    int size = csv_read(argv[1], 1000, data);
    if(size <= 0) {
        return 0;
    }
    for(int i = 0; i < 6; i++) {
        qsort(data, size, sizeof(csvp), cmp1);
        printf("Week %d: ",week);
        for (int j = 0; j < size; j++) {
            p = data[j];
            printf("%s ", p->cell[0]);
        }
        printf("\n");
        week++;
    }
    week = 1;
    qsort(data, size, sizeof(csvp), cmp2);
    printf("Total : ");
    for(int i = 0; i < size; i++) {
        printf("%s ", data[i]->cell[0]);
    }
    printf("\n");
    return 0;
}
