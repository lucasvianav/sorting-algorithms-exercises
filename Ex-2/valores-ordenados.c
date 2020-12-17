/* Author: Lucas Viana Vilela */
/* noUSP:  10748409 */

#include <stdio.h>

int main(){
    int N, output = 7;

    scanf("%d",&N);

    if(N <= 0){
        printf("\n\n>>> ERRO - O NÚMERO INSERIDO É INVÁLIDO <<<\n\n");

        return 1;
    }

    int v[N];

    for(int i = 0; i < N; i++){
        scanf("%d",&v[i]);

        if(i == 0){
            continue;
        }
        
        if(v[i] > v[i-1] && (output == 7 || output == 1)){
            output = 1;
        }
        else if (v[i] < v[i-1] && (output == 7 || output == -1)) {
            output = -1;
        }
        else if(v[i] == v[i-1]){
            continue;
        }
        else {
            output = 0;
        }
    }

    if(output == 7){
        output = 1;
    }

    printf("%d\n",output);

    return 0;

}