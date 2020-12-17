/** AUTHOR: Lucas Viana Vilela */

#include <stdio.h>
#include <string.h>
#include <stdlib.h>

/* Copies inputVector to outputVector */
int *copyVector(int *inputVector, int vectorSize){
    int *outputVector = (int *)malloc(vectorSize * sizeof(int));

    for(int i = 0; i < vectorSize; i++){
        outputVector[i] = inputVector[i];
    }

    return outputVector;
}

/* Swaps vector[index1] with vector[index2] */
void swapElements(int *vector, int index1, int index2){

   if(index1 != index2){
        int tmp; /* Auxiliar variable */

        tmp = vector[index1];
        vector[index1] = vector[index2];
        vector[index2] = tmp;
   }
    
    return;
}

/* Receives a vector and the position of the two  sorted subvectors inside it. Merges both subvectors into a fully sorted one. */
int *interpolateSubvectors(int *vector, int firstLeftIndex, int firstRightIndex, int secondLeftIndex, int secondRightIndex){
    int vectorSize = (firstRightIndex - firstLeftIndex + 1) + (secondRightIndex - secondLeftIndex + 1);
    int *tmp = (int*)malloc(vectorSize * sizeof(int));
    int *count = (int*)malloc(2 * sizeof(int)); /* count[0] = swapCount ; count[1] = comparisonCount */
    int i, j, k = 0;

    count[0] = 0; count[1] = 0;

    for(i = firstLeftIndex, j = secondLeftIndex; k < vectorSize; k++){
        count[0]++;
        if(i <= firstRightIndex && j <= secondRightIndex){ 
            count[1]++;
            if(vector[i] < vector[j]){ tmp[k] = vector[i++]; }
            else{ tmp[k] = vector[j++]; }
        }
        else if(i <= firstRightIndex){ tmp[k] = vector[i++]; }
        else if(j <= secondRightIndex){ tmp[k] = vector[j++]; }

    }

    for(i = firstLeftIndex, j = secondLeftIndex, k = 0; k < vectorSize; k++){
        count[0]++;
        if(i <= firstRightIndex){ vector[i++] = tmp[k]; }
        else{ vector[j++] = tmp[k]; }

    }

    free(tmp); tmp = NULL;

    return count;

}


/* INSERTION SORT */
void insertionSort(int* vector, int vectorSize, int consoleLog){
    int swapCount = 0, comparisonCount = 0;

    if(consoleLog == 1){ printf("\n"); }

    for(int i = 1; i < vectorSize; i++){
        int aux = 0;

        swapCount+=2;

        for(int j = i-1; j >= 0; j--){
            comparisonCount++;

            if(vector[i-aux] < vector[j]){
                swapElements(vector, j, i-aux);
                aux++;
                swapCount++;

                if(consoleLog == 1) { 
                    for(int k = 0; k < vectorSize; k++){ 
                        if(k == i - aux){ printf(">%d ", vector[k]);  }
                        else if(k == 0) { printf(" %d ", vector[k]); }
                        else{ printf("%d ", vector[k]); }
                    }

                    printf("\n");
                }
            }
            
            else{ break; }
        }
    }

    if(consoleLog == 1){ printf("\n"); }
    printf("I %d %d %d\n", vectorSize, swapCount, comparisonCount);

    free(vector);

    return;
}


/* MERGE SORT */
int *mergeSort(int *vector, int leftIndex, int rightIndex, int consoleLog, int execution){
    int vectorSize = rightIndex - leftIndex + 1;
    int *count = (int *)malloc(2 * sizeof(int)); /* [0] = swapCount ; [1] = comparisonCount */

    count[0] = 0; count[1] = 0;

    if(consoleLog == 1){ printf("\n"); }

    if(vectorSize > 1){
        int middleIndex = (rightIndex + leftIndex)/2, *tmp = (int *)malloc(2 * sizeof(int));

        tmp = mergeSort(vector, leftIndex,middleIndex, consoleLog-1, execution+1);
        count[0] += tmp[0]; count[1] += tmp[1];
        free(tmp); tmp = NULL;

        tmp = mergeSort(vector, middleIndex+1,rightIndex, consoleLog-1, execution+1);
        count[0] += tmp[0]; count[1] += tmp[1];
        free(tmp); tmp = NULL;
        
        tmp = interpolateSubvectors(vector, leftIndex, middleIndex, middleIndex+1, rightIndex);
        count[0] += tmp[0]; count[1] += tmp[1];
        free(tmp); tmp = NULL;
        
    }

    if(consoleLog == 1){ for(int i = 0; i < vectorSize; i++){ printf("%d ", vector[i]); } }
    if(consoleLog == 1){ printf("\n\n"); }
    if(execution == 1){ 
        printf("M %d %d %d\n", vectorSize, count[0], count[1]); 
        free(count); count = NULL;
        free(vector);
    }

    return count;

}


int main(){
    int howManyVectors;

    scanf("%d", &howManyVectors);

    int *vectorsSizes = (int*)malloc(howManyVectors * sizeof(int));
    for(int i = 0; i < howManyVectors; i++){ scanf("%d", &vectorsSizes[i]); }

    int **vectors;
    vectors = (int**)malloc(howManyVectors * sizeof(int*));
    for(int i = 0; i < howManyVectors; i++){ 
        vectors[i] = (int *)malloc(vectorsSizes[i] * sizeof(int)); 

        for(int j = 0; j < vectorsSizes[i]; j++){ scanf("%d", &vectors[i][j]); }
    }

    for(int i = 0; i < howManyVectors; i++){ 
        int *copy = copyVector(vectors[i],vectorsSizes[i]);

        insertionSort(copyVector(vectors[i],vectorsSizes[i]), vectorsSizes[i], 0);
        mergeSort(copy, 0, vectorsSizes[i]-1, 0, 1);
        
        copy = NULL;
    }

    for(int i = 0; i < howManyVectors; i++){ free(vectors[i]); }
    free(vectorsSizes);
    free(vectors);

    return 0;
}