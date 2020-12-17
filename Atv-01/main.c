/** AUTORES:
 * Felipe Moura Madureira - 10748646
 * Lucas Viana Vilela - 10748409
 * Lucas Henrique Sant'Anna - 10748521
*/

#include <stdio.h>
#include <string.h>


/* Copia oS elemntos do vetor InputVector para o outputVector */
void copyVector(int vectorSize, int inputVector[], int outputVector[]){
    for(int i = 0; i < vectorSize; i++){
        outputVector[i] = inputVector[i];
    }

    return;
}

/* Realiza a troca do número em vector[index1] com o do vector[index2] */
void swapElements(int vector[], int index1, int index2){

    /** Usar ou não usar 'if(index1 != index2){}'?
     * PRO: Utilizar tornaria essa uma versão mais otimizada; 
     * PRO: O arquivo fornecido para teste indicou que deve ser usado;
     * CON: A versão mostrada em aula não utilizava;
     * 
     * Como a saída deve corresponder com o esperado( e também como o arquivo de 
     * teste de caso fornecido), então provavelmente é melhor utilizar.
    */

   if(index1 != index2){
        int tmp; /* variável auxiliar */

        printf("T %d %d\n", index1, index2); /* T = Troca */

        tmp = vector[index1];
        vector[index1] = vector[index2];
        vector[index2] = tmp;
   }
    

    return;
}

void bubbleSort(int vectorSize, int vector[], int output[]){
    int hasSwapped; /* Ocorreu uma troca na passagem anterior? 1 = sim / 0 = não */
    int lastSwapped; /* O último elementro trocado nessa passagem' index */
    int sentinella = vectorSize; /* O índice do último elemento desordenado */

    copyVector(vectorSize, vector, output);

    do{
        hasSwapped = 0; /* Uma nova passagem se inicio quando não há trocas */

        for(int i = 1; i < sentinella; i++){ /* Loops através do vetor */
            printf("C %d %d\n", i-1, i); /* C = Comparação */

            if(output[i-1] > output[i]){ /* Se a posição subsequente tiver um elemento de menor número em comparação a atual, então os elementos trocarão de posição */
                swapElements(output,i-1,i);

                hasSwapped = 1; /* A troca aconteceu */
                lastSwapped = i;
            }
        }

        sentinella = lastSwapped; /* Sentinella é colocado no último elemento que foi trocado na passagem */
    }while(hasSwapped == 1); /* O vetor é considerado ordenado quando uma passagem apresenta nenhuma troca*/

    return;
}


void selectionSort(int vectorSize, int vector[], int output[]){
    int unsortedSubvector; /* Índice do primeiro elemento do vetor não ordenado */
    int lowestValueIndex; /* Índice do elemento de menor valor do vetor não ordenado */

    copyVector(vectorSize, vector, output);

    /* Loop por todo o vetor (cada final do loop incrementa unsortedSubvector em 1) */
    for(unsortedSubvector = 0; unsortedSubvector < vectorSize; unsortedSubvector++){
        /* No início do loop o elemento atual é usado como referência para o menor valor */
        lowestValueIndex = unsortedSubvector; 

        for(int i = unsortedSubvector+1; i < vectorSize; i++){ /* Loop pelo vetor não ordenado */
            printf("C %d %d\n", lowestValueIndex, i); /* C = Comparação */

            /* Se o elemento de referência é maior que o elemento atual, então lowestValueIndex recebe o índice do elemento de menor valor */
            if(output[i] < output[lowestValueIndex]){
                lowestValueIndex = i;
            }
        }

        swapElements(output, unsortedSubvector, lowestValueIndex);
    }
}

int main(){
    char method[7]; /* "bolha" or "selecao" */
    int vectorSize; /* Tamanho do vetor */

    scanf("%s",method); /* Lê o método de ordenação do usuário */
    scanf("%d",&vectorSize); /* Lê o número de valores a ser digitado pelo usuário */
    
    int input[vectorSize]; /* Vetor não ordenado de números */
    int output[vectorSize]; /* Vetor ordenado de números */

    /* Lê os valores do usuário */
    for(int i = 0; i < vectorSize; i++){
        scanf("%d", &input[i]);
    }

    /* Se method == "bolha", o método de ordenação utilizado é o bubbleSort */
    if(strcmp(method,"bolha") == 0){
        bubbleSort(vectorSize,input,output);
    }

    /* Se method == "selecao", o método de ordenação utilizado é o selectionSort */
    else if(strcmp(method,"selecao") == 0){
        selectionSort(vectorSize,input,output);
    }

    /* Se o usuário não digitou nenhum dos métodos acima relatados, o programa é fechado com erro */
    else{
        return 1;
    }

    /* Imprime o vetor com os valores ordenados (output) */
    for(int i = 0; i < vectorSize; i++){
        printf("%d ", output[i]);
    }
    printf("\n");

    return 0;
}
