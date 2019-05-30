#include<stdio.h>
#include<stdlib.h>
#include<string.h>

#define MAX_BUF_SIZE 1024

#define QUEUESIZE 128

//front == ip
//rear == op
typedef char elementtype;

typedef struct {
  int front, rear;
  elementtype elements[QUEUESIZE];
} queue;

elementtype getq(queue *q);

void initqueue(queue *q)
{
  q->front = q->rear = 0;
}

int queueempty(queue *q)
{
  if(q->front == q->rear) {
    return 1;
  } else {
    return 0;
  }
}

void printqueue(queue *q)
{
  printf("[");
  while(1) {
    printf("%c", getq(q));
    if(queueempty(q)){
      break;
    } else {
      printf(", ");
    }
  }
  printf("]\n");
}

void putq(queue *q, elementtype x)
{
  q->elements[q->front++] = x;
}

elementtype getq(queue *q)
{
  elementtype c = q->elements[q->rear++];
  return c;
}

void test(void)
{
  elementtype x;
  queue q;
  char buf[MAX_BUF_SIZE], str[MAX_BUF_SIZE];
  int n = 0;

  initqueue(&q);

  while(fgets(buf, MAX_BUF_SIZE, stdin) != NULL){
    if (strncmp(buf, "putq ", 5) == 0){
      // putq
      x = buf[5]; // 6文字目が要素
      putq(&q, x);
      continue;
    }
    if (strncmp(buf, "getq", 4) == 0){
      // getq
      x = getq(&q);
      str[n] = x;
      n++;
      continue;
    }
    printf("Unknown command.\n");
  }

  printqueue(&q);

  for(int i = 0; i < n; i++){
    printf("%c", str[i]);
  }
  printf("\n");
}

int main(void)
{
  test();

  return 0;
}
