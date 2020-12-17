/* Author: Lucas Viana Vilela */
/* noUSP: 10748409 */

/** What does this program do?
 * This program takes an input textfile containing only numbers (one in each line) in which the first line indicates 
 * the file's total number of lines. It'll read the whole file and return the index corresponding to the lowest value
 * number listed in there - considering that the 2nd line's index is 0.
*/

#include <stdio.h>
#include <stdlib.h>

#define MAX_SIZE 99999

int main() {
    int N; /* Input vector's number of elements */   
    int lowestValue = 0; /* Input's lowest value V[i] */
    int lowestValueIndex = 0; /* Output i */
    char auxStr[MAX_SIZE]; /* Auxiliar string in order to read the file */
    char filepath[999]; /* Path to the file that will be read */

    printf("\nThis program takes an input textfile containing only numbers (one in each line) ");
    printf("in which the first line indicates the file's total number of lines. It'll read the whole");
    printf(" file and return the index corresponding to the lowest value number listed in there - ");
    printf("considering that the 2nd line's index is 0.\n\n");
    printf("Enter the filepath to be read: ");
    scanf("%s",filepath);
    printf("\n");

    FILE *fPointer = fopen(filepath,"r");

    /* In case it is impossible to open or find the file */
    if(fPointer == NULL){
        printf("ERROR - Could not open file");

        return 1;
    }

    fgets(auxStr,MAX_SIZE,fPointer); /* Reads the first line (value of input size) */
    N = atoi(auxStr); /* Turn the read string into an int */

    int vector[N]; /* Input elements */
    
    for(int i = 0; fgets(auxStr,MAX_SIZE,fPointer) != NULL; i++) {
        vector[i] = atoi(auxStr); /* Turn the read string into an int */

        /* If the current value is the first or is lower than the former lowest one, set it as the lowest value */
        if(i == 0 || vector[i] < lowestValue){
            lowestValue = vector[i];
            lowestValueIndex = i;
        }
    }

    fclose(fPointer);

    /* Prints the output */
    printf(":::LOWEST VALUE IS %d.\n", lowestValue);
    printf("\n:::actual output:\n");
    printf(":::LOWEST VALUE'S INDEX IS %d.\n\n", lowestValueIndex);

    return 0;

}