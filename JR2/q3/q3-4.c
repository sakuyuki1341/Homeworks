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

void push(stack *s, elementtype x)
{
  s->top += 1;
  if (s->top >= STACKSIZE) {
    printf("Stack overflow.\n"); exit(1);
  } else {
    s->elements[s->top] = x;
  }
  return;
}

elementtype pop(stack *s)
{
  elementtype x;
  if (s->top < 0){
    printf("Stack is empty.\n"); exit(1);
  } else {
    x = s->elements[s->top];
    s->top -= 1;
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
  stack route;
  position cur, next, prev;
  position candidate [ NUMBER_OF_DIRECTIONS ]; // left, right, up, down;
  bool direction = FORWARD;

  initstack ( &route );

  prev = start;
  cur = start;
  int n = next_possible_move ( m, cur, prev, candidate ); // 次の可能な移動を検索
  push ( &route, cur );
  cur = candidate [ 0 ];

  while(! is_goal ( m, cur ) ) { // ゴールに到達するまで繰り返し
    //printf("CUR: (%d,%d)\n", cur.i, cur.j);
    n = next_possible_move ( m, cur, prev, candidate ); // 次の可能な移動を検索
    prev = cur;
    switch ( n ) {

    case 0: // 行き止まり
      direction = BACKWARD;
      cur = pop ( &route ); // 逆戻り
      printf("%s\n", (direction == FORWARD) ? "FORWARD" : "BACKWARD");
      break;

    default: // それ以外
      if ( direction == FORWARD ) {
	push ( &route, cur );
	cur = candidate [ 0 ];
      } else {
	cur = pop ( &route );
      }
      printf("%s\n", (direction == FORWARD) ? "FORWARD" : "BACKWARD");
      break;
    }
  }

  // ゴールに到達した
  // 行儀悪いけど、構造体の内容を書き換えて経路を追加
  while ( 1 ) {
    cur = pop ( &route );
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
