#include<stdio.h>
#include<stdlib.h>
#include<string.h>

#define MAX_MAZE_SIZE 1024
#define NUMBER_OF_DIRECTIONS 4 // left, right, up, down

enum { FORWARD, BACKWARD };
typedef int bool;
typedef struct { int i, j; } position;
typedef struct {
  int size_row, size_col;
  char map [ MAX_MAZE_SIZE ][ MAX_MAZE_SIZE ];
  position start, goal;
} maze;

///////////////////////////////////////////////////////////////////////////////
// Stack definition
///////////////////////////////////////////////////////////////////////////////
#define STACKSIZE MAX_MAZE_SIZE
typedef position elementtype;

typedef struct {
  int top;
  elementtype elements[STACKSIZE];
} stack;

void initstack(stack *s)
{
  s->top = -1;
}

int stackempty(stack *s)
{
  return (s->top < 0);
}

void printstack(stack *s)
{
  printf("[");
  for(int i = 0; i <= s->top; i++){
    printf("(%d,%d)", s->elements[i].i, s->elements[i].j);
    if (i < s->top) {
      printf(", ");
    }
  }
  printf("]\n");
}

void push(stack *s, elementtype x, char c)
{
  s->top += 1;
  if (s->top >= STACKSIZE) {
    printf("Stack overflow.\n"); exit(1);
  } else {
    s->elements[s->top] = x;
  }
  //printf("%c push (%d,%d): ", c, x.i, x.j);
  //printstack(s);
  return;
}

elementtype pop(stack *s, char c)
{
  elementtype x;
  if (s->top < 0){
    printf("%c Stack is empty.\n", c); exit(1);
  } else {
    x = s->elements[s->top];
    s->top -= 1;
    //printf("%c pop: (%d,%d), ", c, x.i, x.j);
    //printstack(s);
    return x;
  }
}
///////////////////////////////////////////////////////////////////////////////

position possible_moves [ 4 ] = {
  { .i =  0, .j = -1 },
  { .i =  0, .j = +1 },
  { .i = -1, .j =  0 },
  { .i = +1, .j =  0 } };
position move ( position p, position d ) { position q = { .i = p.i + d.i, .j = p.j + d.j }; return q; }
bool equal ( position p, position q ) { return ( p.i == q.i && p.j == q.j ) ? 1 : 0; }

void read_maze ( maze *m )
{
  char str [ MAX_MAZE_SIZE + 2 ]; // +2 = '\n' + '\0'
  position p = { .i = 0, .j = 0 };

  while ( fgets ( str, MAX_MAZE_SIZE + 2, stdin ) ) {
    for (p.j = 0; str [ p.j ] != '\n'; p.j++ ) {
      m->map [ p.i ][ p.j ] = str [ p.j ];
      if ( str [ p.j ] == 'S' ) {
	m->start = p;
      }
      if ( str [ p.j ] == 'G' ) {
	m->goal = p;
      }
    }
    p.i += 1;
  }
  m->size_row = p.i;
  m->size_col = p.j;
}

void print_maze ( maze m )
{
  position a;

  printf(" ");
  for ( int j = 0; j < m.size_col; j++ ) {
    printf("%d", j%10);
  }
  printf("\n");

  for ( a.i = 0; a.i < m.size_row; a.i++ ) {
    printf("%d", a.i%10);
    for ( a.j = 0; a.j < m.size_col; a.j++ ) {
      printf ( "%c", m.map [ a.i ][ a.j ] );
    }
    printf ( "\n" );
  }
}

bool is_in ( maze *m, position p ) { return ( 0 <= p.i && p.i <= m->size_row - 1 && 0 <= p.j && p.j <= m->size_col - 1 ) ? 1 : 0; }
bool is_goal ( maze *m, position p ) { return ( m->map [ p.i ][ p.j ] == 'G' ) ? 1 : 0; }
bool is_wall ( maze *m, position p ) { return ( m->map [ p.i ][ p.j ] == '#' ) ? 1 : 0; }
int next_possible_move ( maze *m, position cur, position prev, position candidate [] )
{
  int n = 0;
  for ( int i = 0; i < NUMBER_OF_DIRECTIONS; i++ ) {
    position next = move ( cur, possible_moves [ i ] );
    if ( is_in ( m, next ) && ! is_wall ( m, next ) && ! equal ( next, prev ) ) { candidate[n] = next; n += 1; }
  }
  return n;
}

void solve ( maze *m )
{
  position start = m->start;
  position goal  = m->goal;
  stack route, branch;
  position cur, next, prev;
  position candidate [ NUMBER_OF_DIRECTIONS ]; // left, right, up, down;
  bool direction = FORWARD;

  initstack ( &route );
  initstack ( &branch );
  int branch_arr[1024];
  int branch_arr_now = 0;

  prev = start;
  cur = start;
  int n = next_possible_move ( m, cur, prev, candidate ); // 次の可能な移動を検索
  push ( &route, cur, 'r' );
  cur = candidate [ 0 ];

  printf("START\n");
  while(! is_goal ( m, cur ) ) { // ゴールに到達するまで繰り返し
    printf("CUR: (%d,%d)\n", cur.i, cur.j);
    n = next_possible_move ( m, cur, prev, candidate ); // 次の可能な移動を検索
    prev = cur;
    switch ( n ) {

    case 0: // 行き止まり
      direction = BACKWARD;
      cur = pop ( &route, 'r' ); // 逆戻り
      printf("%s\n", (direction == FORWARD) ? "FORWARD" : "BACKWARD");
      break;

    case 1: // 一本道
      if ( direction == FORWARD ) {
	push ( &route, cur, 'r' );
	cur = candidate [ 0 ];
      } else {
	cur = pop ( &route, 'r' );
      }
      printf("%s\n", (direction == FORWARD) ? "FORWARD" : "BACKWARD");
      break;

    default: // 分岐
      printf("BRANCH\n");

      if( direction == FORWARD ) {
        for(int i = 0; i < n; i++) {
          push ( &branch, candidate[i], 'r');
        }
        branch_arr_now++;
        branch_arr[branch_arr_now] = n;
        push ( &route, cur, 'r');
        cur = pop ( &branch, 'r');
        branch_arr[branch_arr_now]--;
      } else {
        if(branch_arr[branch_arr_now] == 0) {
          cur = pop (&route, 'r' );
          branch_arr_now--;
          break;
        }
        push ( &route, cur, 'r');
        cur = pop ( &branch, 'r');
        branch_arr[branch_arr_now]--;
        direction = FORWARD;
      }

      printf("%s\n", (direction == FORWARD) ? "FORWARD" : "BACKWARD");
      break;
    }
  }

  // ゴールに到達した
  // 行儀悪いけど、構造体の内容を書き換えて経路を追加
  //printf("DONE\n");
  while ( 1 ) {
    cur = pop ( &route, 'r' );
    if ( equal ( cur, start ) ) { break; }
    m->map [ cur.i ][ cur.j ] = '.';
  }

}

int main(void)
{
  maze m;

  read_maze ( &m );

  solve ( &m );

  print_maze ( m );

  return 0;
}
