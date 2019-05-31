#include <stdio.h>
#include <stdlib.h>

int* p;
int   N;
/*
int* remover(int* p, int choice) {
    int* p_ret = malloc((N+1)*sizeof(int));
    for(int i = 1; i <= N; i++) {
        p_ret[i] = p[i];
    }
    for(int i = choice; i <= N; i++) {
        p_ret[i] = p_ret[i+1];
    }
    return p_ret;
}

void perm(int n,int choice, int* p, int* store) {
    if(n == 0) {
        printf("\n");
    } else {
        //printf("%d", n);
        store[N-n] = choice;
        printf("%d", choice);
        int* p_new = remover(p, choice);
        for(int i=1; i <= n; i++) {
            //printf("%d", n);
            perm(n-1, i, p_new, store);
        }
    }
}
*/
void perm(int n, int k) {
    if(n == 1) {
        p[n] = k;
        int flag = 1;
        for(int i = 1; i <= N; i++) {
            for(int j = 1; j <= N; j++) {
                if(p[i] == p[j] && i != j) {
                    flag = 0;
                }
            }
        }
        if(flag){
            for(int i = 1; i <= N; i++) {
                printf("%d ", p[i]);
            }
            printf("\n");
        }
    } else {
        p[n] = k;
        for(int i = 1; i <= N; i++) {
            perm(n-1, i);
        }
    }
}



int main(int argc, char *argv[]){
	N = atoi(argv[1]);
	p = malloc((N+1)*sizeof(int));
    int* store = malloc((N+1)*sizeof(int));
	for(int i=1; i<=N; i++) {
		p[i] = i;
    }
    for(int i=1; i<=N; i++) {
        perm(N, i);
    }
	return 0;
}
