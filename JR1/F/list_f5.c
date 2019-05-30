#include <stdio.h>

typedef enum Element{NORMAL, SPARE, STRIKE} Element;

int Bowling(int n, int*a);

int main(void) {
  int n, i;
  int a[21];
  scanf("%d", &n);
  for(i = 0; i < n; i++) {
    scanf("%d", a + i);
  }
  printf("%d\n", Bowling(n, a));
  return 0;
}

int Bowling(int n, int* a) {
  int bowl[10][5];
  int i;
  int score = 0;
  int num = 0;

  for(i = 0; i < 9; i++) {
    if(a[num] == 10) {
      bowl[i][0] = a[num];
      bowl[i][1] = 0;
      bowl[i][2] = 0;
      bowl[i][3] = STRIKE;
      bowl[i][4] = bowl[i][0] + bowl[i][1] + bowl[i][2];
      num++;
    } else if(a[num] + a[num + 1] == 10) {
      bowl[i][0] = a[num];
      bowl[i][1] = a[num + 1];
      bowl[i][2] = 0;
      bowl[i][3] = SPARE;
      bowl[i][4] = bowl[i][0] + bowl[i][1] + bowl[i][2];
      num += 2;
    } else {
      bowl[i][0] = a[num];
      bowl[i][1] = a[num + 1];
      bowl[i][2] = 0;
      bowl[i][3] = NORMAL;
      bowl[i][4] = bowl[i][0] + bowl[i][1] + bowl[i][2];
      num += 2;
    }
  }

  if(n - num  == 3) {
    bowl[9][0] = a[num];
    bowl[9][1] = a[num + 1];
    bowl[9][2] = a[num + 2];
    bowl[9][3] = NORMAL;
    bowl[9][4] = bowl[i][0] + bowl[i][1] + bowl[i][2];
  } else {
    bowl[9][0] = a[num];
    bowl[9][1] = a[num + 1];
    bowl[9][2] = 0;
    bowl[9][3] = NORMAL;
    bowl[9][4] = bowl[i][0] + bowl[i][1] + bowl[i][2];
  }

  for(i = 0; i < 9; i++) {
    score += bowl[i][4];
    if(bowl[i][3] == SPARE) {
      score += bowl[i + 1][0];
    } else if(bowl[i][3] == STRIKE) {
      score += bowl[i + 1][0];
      if(bowl[i + 1][3] == STRIKE) {
        score += bowl[i + 2][0];
      } else {
        score += bowl[i + 1][1];
      }
    }
  }

  score += bowl[9][4];
  return score;
}
