#include <ncurses.h>
#include <stdlib.h>

int main(void) {
  initscr(); noecho(); cbreak(); system("stty raw"); clear();
  move(10, 10); addstr("press any key"); refresh();
  int ch = getch(); addch('a'); addch('b'); refresh();
  ch = getch(); move(10, 15); insch('a'); insch('b'); refresh();
  ch = getch(); delch(); move(10, 20); clrtoeol(); refresh();
  ch = getch(); endwin(); return 0;
}
