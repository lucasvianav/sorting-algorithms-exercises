#include <stdio.h>
#include <stdlib.h>

#define max(x, y) (x > y ? x : y)
#define EMPTY -1

typedef struct street_ {
    int orig;
    int dest;
    int noFriends;
} st; // street

int friendsInStreet(st *streets, int noStreets, int origin, int destination){
    for(int i = 0; i < noStreets; i++){
        if(streets[i].orig == origin && streets[i].dest == destination){ return streets[i].noFriends; }
    }

    return 0;
}

int auxFindBestPath(st *streets, int noStreets, int origin, int destination, int nRows, int nCols, int *cache){
    if(cache[origin] == EMPTY){
        if(origin >= destination){
            cache[origin] = 0;
        }

        else{
            int isInTheRight = 0;
            for(int i = 0; i < nRows; i++){
                if(origin == nCols - 1 + i*nCols){
                    isInTheRight = 1;
                    break;
                }
            }

            int isInTheBottom = origin >= destination - nCols + 1;

            int right = !isInTheRight
                ? auxFindBestPath(streets, noStreets, origin + 1, destination, nRows, nCols, cache) + friendsInStreet(streets, noStreets, origin, origin + 1)
                : 0;

            int down = !isInTheBottom
                ? auxFindBestPath(streets, noStreets, origin + nCols, destination, nRows, nCols, cache) + friendsInStreet(streets, noStreets, origin, origin + nCols)
                : 0;

            cache[origin] = max(right, down);
        }
    }

    return cache[origin];
}

int findBestPath(st *streets, int noStreets, int nRows, int nCols){
    int *cache = (int *)malloc((noStreets + 1) * sizeof(int));
    for(int i = 0; i <= noStreets; i++){ cache[i] = EMPTY; }

    int output = auxFindBestPath(streets, noStreets, 0, nRows*nCols-1, nRows, nCols, cache);

    free(cache);
    return output;
}

int main(){
    int nRows, nCols;

    scanf("%d %d", &nRows, &nCols);

    int noStreets = (nRows - 1)*nCols + (nCols - 1)*nRows;
    st *streets = (st *)malloc(noStreets * sizeof(st));

    for(int i = 0; i < noStreets; i++){ scanf("%d %d %d", &streets[i].orig, &streets[i].dest, &streets[i].noFriends); }

    int friendsMet = findBestPath(streets, noStreets, nRows, nCols);
    printf("%d\n", friendsMet);

    free(streets);
    return 0;
}