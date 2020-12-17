#include <stdio.h>

#define EMPTY -1
#define DELETED -2
#define NOT_FOUND -1

int h(int x, int m, int k){
    return (x + k) % m;
}

void insert(int *table, int x, int m){
    for(int k = 0; k < m; k++){
        int i = h(x, m, k);

        if(table[i] == x){ break; }

        else if(table[i] == EMPTY || table[i] == DELETED){ 
            table[i] = x; 
            break;
        }
    }

    return;
}

void delete(int *table, int x, int m){
    for(int k = 0; k < m; k++){
        int i = h(x, m, k);
        
        if(table[i] == x){
            table[i] = DELETED;
            break;
        }

        else if(table[i] == EMPTY){ break; }
    }

    return;
}

int search(int *table, int x, int m){
    for(int k = 0; k < m; k++){
        int index = h(x, m, k);
        if(table[index] == x){ return index; }
    }

    return NOT_FOUND;
}

int main(){
    int m, n, x, d, b;

    scanf("%d", &m);
    int table[m];
    for(int i = 0; i < m; i++){ table[i] = EMPTY; }

    scanf("%d", &n);
    for(int i = 0; i < n; i++){
        scanf("%d", &x);
        insert(table, x, m);
    }

    scanf("%d", &d);
    for(int i = 0; i < d; i++){
        scanf("%d", &x);
        delete(table, x, m);
    }

    scanf("%d", &b);
    for(int i = 0; i < b; i++){
        scanf("%d", &x);
        printf("%d ", search(table, x, m));
    }
    printf("\n");

    return 0;
}