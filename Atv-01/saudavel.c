#include <stdio.h>
#include <stdlib.h>
#include <string.h>

void preencheVetor(int n, int *vetor){
    int i;
    for(i=0;i<n;i++){
        scanf("%d",&vetor[i]);
    }
}

void imprimeVetor(int n, int *vetor){
    int i;
    for(i=0;i<n;i++){
        printf("%d",vetor[i]);
        if(i!=n-1){
            printf(" ");
        }
        else {printf("\n");}
    }
}

void bolha(int tamanhoVetor, int *vetor){
    int restam,i,aux;
    for(restam = tamanhoVetor-1; restam>0; restam--){
        for(i=0;i<restam;i++){
            printf("C %d %d\n",i,i+1);
            if(vetor[i]>vetor[i+1]){
                printf("T %d %d\n",i,i+1);
                aux=vetor[i];
                vetor[i]=vetor[i+1];
                vetor[i+1]=aux;
            }
        }
    }
}

void selecao(int tamanhoVetor, int *vetor){
    int i,j,candidato,posicaoCandidato,aux;
    for(i=0;i<(tamanhoVetor-1);i++){
        candidato=vetor[i];
        posicaoCandidato=i;
        for(j=i+1;j<tamanhoVetor;j++){
            printf("C %d %d\n",posicaoCandidato,j);
            if(vetor[j]<candidato){
                candidato=vetor[j];
                posicaoCandidato=j;
            }
        }
        if(posicaoCandidato==i){
            continue;
        }
        printf("T %d %d\n",i,posicaoCandidato);
        aux = vetor[i];
        vetor[i] = candidato;
        vetor[posicaoCandidato] = aux;
    }
}

int main(){
    char tipo[10], moldeBolha[10]="bolha", moldeSelecao[10]="selecao";
    int tamanhoVetor, *vetor;

    //strcpy(moldeBolha,"bolha");
    //strcpy(moldeSelecao,"selecao");
    scanf("%s",tipo);
    scanf("%d",&tamanhoVetor);
    vetor=(int*)malloc(tamanhoVetor*sizeof(int));
    preencheVetor(tamanhoVetor,vetor);
    if(strcmp(moldeBolha,tipo)==0){
        bolha(tamanhoVetor,vetor);
    }
    else if(strcmp(moldeSelecao,tipo)==0){
        selecao(tamanhoVetor,vetor);
    }
    else{
        return 0;
    }
    imprimeVetor(tamanhoVetor,vetor);
    free(vetor);
    return 0;
}
