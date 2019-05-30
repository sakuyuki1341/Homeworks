#include <stdio.h>
#include <string.h>

char *findfirst(char*str, char*sub) {
    char *a, *b;
    if (*sub == 0) {
        return str;
    }
    for (; *str != 0; str += 1) {
        if (*str != *sub) {
            continue;
        } else {            //ここで一文字目が判別完了
            a = str;        //内部で使用するため
            b = sub;        //内部で使用するため
            for (; *b != 0; b += 1) {
                if(*a != *b) {
                  break;          //判定に失敗時抜ける
                }
                a++;              //大本の文字列も移動させる
            }
            if(*b == 0) {
              return str;        //もともと持っていた位置を返す
            }
        }
    }
    return NULL;
}


int main(int argc, char *argv[]) {
    char *s1, *s2, *s;

    s1 = argv[1];
    s2 = argv[2];
    if((s=findfirst(s1, s2))) {
        printf("%s\n", s);
    }
    else {
        printf("\n");
    }
    return 0;
}
