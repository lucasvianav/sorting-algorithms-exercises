#include <stdio.h>
#include <stdlib.h>

// SHELL SORT
int shell(int v[], int n) {
    int count = 0;

    int gap = 1;
    while(gap <= n) {
        gap *= 2;
    }
    gap = gap / 2 - 1;

    while(gap > 0) {
        int j;

        for (int k = 0; k < gap; k++){
            for (int i = k + gap; i < n; i += gap){
                int x = v[i];
                count++;

                j = i - gap;
                while(j >= 0){
                    count++;
                    if(v[j] > x){
                        v[j+gap] = v[j];
                        count++;

                        j-=gap;
                    }
                    else{ break; }
                }
                v[j+gap] = x;
                    count++;
            }
        }
        gap /= 2;
    }

    return count;
}

// QUICK SORT
int quick(int *vector, int leftIndex, int rightIndex){
    int count = 0;

    if(leftIndex < rightIndex){
        int pivot = vector[(int)((rightIndex+leftIndex)/2)];
        count++;

        int left = leftIndex, right = rightIndex;

        while(1){
            // Selects elements from the left that are >= to the pivot
            count++;
            while(vector[left] < pivot){ 
                left++;
                count++;
            }

            // Selects elements from the right that are <= to the pivot
            count++;
            while(vector[right] > pivot){ 
                right--; 
                count++;
            }

            // If the swapping the above selected elements is worth it, do it
            if(left < right){ 
                // swapElements(vector, left++, right--); 
                int tmp = vector[left];
                count++;
                vector[left] = vector[right];
                count++;
                vector[right] = tmp;
                count++;
                left++; right--;
            } // And pass to the next element

            // If the swap is not worth it, the vector was successfully partitionted
            else{ break; }

        }

        // Sorts the partitions
        count += quick(vector, leftIndex, right);
        count += quick(vector, right+1, rightIndex);
    }

    return count;

}


int main(){
    int size, q, s;

    scanf("%d", &size);

    int *vector = (int *)malloc(size * sizeof(int)), *auxShell, *auxQuick;

    for(int i = 0; i < size; i++){
        scanf("%d", &vector[i]);
    }

    for(int i = 0; i < size; i++){
        auxShell = (int *)malloc((i+1) * sizeof(int));
        auxQuick = (int *)malloc((i+1) * sizeof(int));
        for(int j = 0; j < i+1; j++){
            auxShell[j] = vector[j];
            auxQuick[j] = vector[j];
        }

        s = shell(auxShell, i+1);
        q = quick(auxQuick, 0, i);

        free(auxShell);
        free(auxQuick);

        if(s > q){
            printf("Q");
            if(i < size - 1){ printf(" "); }
        }

        else if(s < q){
            printf("S");
            if(i < size - 1){ printf(" "); }
        }

        else{
            printf("-");
            if(i < size - 1){ printf(" "); }
        }
    }

    printf("\n");

    free(vector);

    return 0;

}