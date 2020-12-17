#include <stdio.h>
#include <stdlib.h>
#include <string.h>

int main()
{
    int n, aux, overlap[4] = {-1, 0, 1, 0};
    char letra;
    char **reads_tmp;

    // Input din�mico dos n reads, char a char.
    scanf("%d ", &n);

    char **reads = (char **)malloc(n * sizeof(char *));
    for(int i = 0; i < n; i++){
        reads[i] = (char *)malloc(sizeof(char));
        aux = 0;

        do{
            scanf("%c", &letra);
            reads[i] = (char *)realloc(reads[i], ++aux * sizeof(char));
            reads[i][aux-1] = (letra == '\n' || letra == '\r' || letra == ' ') ? '\0' : letra;

        } while(letra != '\n' && letra != '\r' && letra != ' ');
    }

    while(n > 1){

        /*
            Hora de conferir onde est� o maior overlap, examinando arranjos das reads dispostas 2 a 2.

            Aqui aux ser� usado para guardar informa��es sobre poss�veis overlaps completos
            (1 palavra completamente inclusa na outra).

            Sobre o array overlap[4]:
                - [0] examina overlaps na compara��o atual, como uma vari�vel local faria;
                - [3] guarda valor do maior overlap encontrado at� ent�o;
                - [1] e [2] guardam �ndices das strings que t�m o maior overlap, em ordem.
        */


        for(int i = 0; i < n; i++){
            for(int j = 0; j < n; j++){
                if(j == i){ continue; }

                for(int k = 0; k < strlen(reads[i]); k++){
                    // Enquanto chars das duas strings coincidirem, ele conta como um overlap
                    if(reads[i][k] == reads[j][overlap[0]]){ overlap[0]++; }

                    // Caso um overlap seja 'cortado' antes do fim da primeira string
                    else if(overlap[0] > 0){
                        // Confere se encontrou uma string inclusa na outra
                        if(overlap[0] == strlen(reads[j])){
                            aux = -1;
                            break;
                        }

                        else{ overlap[0] = (reads[i][k] == reads[j][0]) ? 1 : 0; }
                    }
                }

                // Caso encontre um overlap, confira se � o maior overlap encontrado at� agora
                if(overlap[0] > overlap[3]){
                    overlap[3] = overlap[0];
                    overlap[1] = i;
                    overlap[2] = j;

                    // Se sim, o maior overlap � um overlap completo
                    // se não, o maior overlap N�O � um overlap completo
                    aux = (aux == -1) ? -2 : 0;
                }

                // Ao terminar de examinar o par de strings, ele pode resetar overlap[0] (que serve apenas para esse momento)
                overlap[0] = 0;
            }
        }

        /*
            Hora de, dado o que foi encontrado, unir e reorganizar strings.

            Se overlap[3] > 0:
                Sabemos que h� um (maior) overlap e que iremos
                unir suas respectivas strings.
                Se aux = -2, podemos descartar a string que estaria contida na
                outra, e o efeito � o mesmo.
                Ap�s isso, movemos a nova sequ�ncia (ap�s unir overlaps) na 1�
                posi��o na lista de reads.

            Caso contr�rio:
                N�o h� nenhum overlap entre as strings dadas.
                Podemos unir todas as strings numa s�.
        */

        reads_tmp = (char **)malloc((n-1) * sizeof(char *));

        // Copia a nova sequ�ncia (montada a partir dos overlaps) para o array auxiliar
        if(aux != -2){
            reads_tmp[0] = (char *)malloc((strlen(reads[overlap[1]]) + strlen(reads[overlap[2]]) - overlap[3] + 1) * sizeof(char));
            strcpy(reads_tmp[0], reads[overlap[1]]);
            strcpy(&reads_tmp[0][strlen(reads_tmp[0]) - overlap[3]], reads[overlap[2]]);
        }

        // Caso o overlap seja completo, podemos 'ignorar' a segunda string (englobada na primeira)
        else{
            reads_tmp[0] = (char *)malloc((strlen(reads[overlap[1]]) + 1)*sizeof(char));
            strcpy(reads_tmp[0], reads[overlap[1]]);
        }

        // Copia os demais reads (exceto os envolvidos nos overlaps) para o array auxiliar
        for(int i = 0, j = 1; i < n; i++){
            if(i != overlap[1] && i != overlap[2]){
                reads_tmp[j] = (char *)malloc((strlen(reads[i]) + 1) * sizeof(char));
                strcpy(reads_tmp[j++], reads[i]);
            }

            free(reads[i]);
        }

        free(reads);
        reads = (char **)malloc(--n * sizeof(char *));

        // Refaz a lista de reads por meio do array tempor�rio
        for(int i = 0; i < n; i++){
            reads[i] = (char *)malloc((strlen(reads_tmp[i]) + 1) * sizeof(char));
            strcpy(reads[i], reads_tmp[i]);
            free(reads_tmp[i]);
        }

        free(reads_tmp);
        overlap[3] = 0;
    }

    // Diferenciando n = 1 e n = 0 evitamos imprimir 2 vezes no caso de n�o haver nenhum overlap.
    printf("%s\n", reads[0]); 
    free(reads[0]);
    free(reads);
    
    return 0;
}
