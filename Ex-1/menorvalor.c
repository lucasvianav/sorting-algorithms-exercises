/* Author: Lucas Viana Vilela */
/* noUSP: 10748409 */

#include <stdio.h>
#include <stdlib.h>

int main() {
    int N; /* Input vector's number of elements */   
    int lowestValue = 0; /* Input's lowest value V[i] */
    int lowestValueIndex = 0; /* Output i */

    scanf("%d",&N);

    int V[N]; /* Input elements */
    
    for(int i = 0; i<N; i++) {
        scanf("%d",&V[i]);

        /* If the current value is the first or is lower than the former lowest one, set it as the lowest value */
        if(i == 0 || V[i] < lowestValue){
            lowestValue = V[i];
            lowestValueIndex = i;
        }
    }

    /* Prints the output */
    printf("%d\n", lowestValueIndex);

    return 0;

}