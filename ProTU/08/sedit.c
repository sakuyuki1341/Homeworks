#include <stdio.h>
#include <stdbool.h>
#include <ncurses.h>
#include <stdlib.h>
#include <string.h>
#include "ebuf.h"

/*========================================================*
 * 関数readfile: ebufとファイルの名前を受け取り
 * ファイルが開けなければNULLを返し、ファイルが開ければ
 * ファイルの中身の文字列をebufのcurの上に插入する。
 *========================================================*/
bool readfile(ebufp e, char *fname) {
    char str[200];
    FILE *f = fopen(fname, "r");
    if(f == NULL) { return false; }
    while(fgets(str, 200, f) != NULL) {
        int len = strlen(str);
        if(len > 0) { str[len-1] = '\0'; }
        ebuf_insert(e, str);
    }
    fclose(f); return true;
}

/*========================================================*
 * 関数writefile: ebufとファイルの名前を受け取り
 * ファイルが開けなければNULLを返し、ファイルが開ければ
 * ファイルにebufの中身全てを追加する。
 *========================================================*/
bool writefile(ebufp e, char *fname) {
    FILE *f = fopen(fname, "w");
    if(f == NULL) { return false; }
    ebuf_top(e);
    while(!ebuf_iseof(e)) {
        fprintf(f, "%s\n", ebuf_str(e)); ebuf_forward(e);
    }
    fclose(f); return true;
}

void inschar(char *s, char ch, int p, int len) {
    int i;
    for(i = len + 1; i > p; --i) { s[i] = s[i-1]; }
    s[p] = ch;
}

void delchar(char *s, int p, int len) {
    int i;
    for(i = p; i < len; ++i) { s[i] = s[i+1]; }
}

bool handleline(int c, char *s, int *pos, int *len) {
    if(c >= ' ' && c <= '~') {
        if(*len >= MAXSTR-1) { return false; }
        insch(c); inschar(s, c, *pos, (*len)++); move(10, ++(*pos));
    } else if(c == 'B'-'@') {
        if(*pos > 0) { move(10, --(*pos)); }
    } else if(c == 'F'-'@') {
        if(*pos < *len) { move(10, ++(*pos)); }
    } else if(c == 'H'-'@') {
        if(*pos <= 0) { return false; }
        move(10, *pos - 1); delch(); delchar(s, --(*pos), (*len)--);
    } else {
        return false;
    }
    return true;
}

int main(int argc, char *argv[]) {
    ebufp e = ebuf_new();
    if(!readfile(e, argv[1])) { printf("?\n"); return 1; }
    ebuf_top(e);
    int len, pos, ch; char *str;
    bool show = true;
    initscr(); noecho(); cbreak(); system("stty raw"); clear();
    while(true) {
        if(show) {
            str = ebuf_str(e); len = strlen(str); pos = 0;
            move(10, 0); addstr(str); clrtoeol(); move(10, 0); show = false;
        }
        refresh(); ch = getch();
        if(handleline(ch, str, &pos, &len)) {
            // do nothing
        } else if(ch == 'J'-'@') {
            ebuf_forward(e); ebuf_insert(e, "");
            ebuf_backward(e); show = true;
        } else if(ch == 'N'-'@') {
            ebuf_forward(e); show = true;
        } else if(ch == 'P'-'@') {
            ebuf_backward(e); show = true;
        } else if(ch == 'Z'-'@') {
            break;
        }
    }
    endwin(); writefile(e, argv[1]); return 0;
}
