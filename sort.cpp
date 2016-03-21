#include <time.h>
#include <stdio.h>
#include <unistd.h>
#include <stdlib.h>
#include <math.h>
#include <algorithm>
#define SIZE 50000

void quickSort(int *, int, int);
void mergeSort(int *, int, int);
void bubbleSort(int *, int, int);
void calcPrint(void (*func)(int *,int, int));

int main( ){

    printf("\tQuick Sort\n");
    calcPrint(quickSort);
    printf("\tMerge Sort\n");
    calcPrint(mergeSort);
    printf("\tBubble Sort\n");
    calcPrint(bubbleSort);

    exit(0);
}

void quickSort(int *vet, int esquerda, int direita)
{
    int i, j, x, y;
    i = esquerda;
    j = direita;
    x = vet[(esquerda + direita) / 2];

    while(i <= j) {
        while(vet[i] < x && i < direita) 
            i++;
        while(vet[j] > x && j > esquerda) 
            j--;
        if(i <= j) {
            y = vet[i];
            vet[i] = vet[j];
            vet[j] = y;
            i++;
            j--;
        }
    }
    if(j > esquerda) 
        quickSort(vet, esquerda, j);
    if(i < direita) 
        quickSort(vet,  i, direita);
}

 void mergeSort(int *vet, int posicaoInicio, int posicaoFim){
    int i, j, k, metadeTamanho, *vetTemp;

    if(posicaoInicio == posicaoFim) return;

    // ordenacao recursiva das duas metades
    metadeTamanho = (posicaoInicio + posicaoFim ) / 2;
    mergeSort(vet, posicaoInicio, metadeTamanho);
    mergeSort(vet, metadeTamanho + 1, posicaoFim);

    // intercalacao no vetor temporario t
    i = posicaoInicio;
    j = metadeTamanho + 1;
    k = 0;
    vetTemp = (int *) malloc(sizeof(int) * (posicaoFim - posicaoInicio + 1));

    while(i < metadeTamanho + 1 || j  < posicaoFim + 1) {
        if (i == metadeTamanho + 1 ) { // i passou do final da primeira metade, pegar v[j]
            vetTemp[k] = vet[j];
            j++;
            k++;
        } 
        else {
            if (j == posicaoFim + 1) { // j passou do final da segunda metade, pegar v[i]
                vetTemp[k] = vet[i];
                i++;
                k++;
            } 
            else {
                if (vet[i] < vet[j]) { 
                    vetTemp[k] = vet[i];
                    i++;
                    k++;
                } 
                else { 
                    vetTemp[k] = vet[j];
                    j++;
                    k++;
                }
            }
        }

    }
    // copia vetor intercalado para o vetor original
    for(i = posicaoInicio; i <= posicaoFim; i++) {
        vet[i] = vetTemp[i - posicaoInicio];
    }
    free(vetTemp);
}

void bubbleSort(int *vet, int trash, int size){
    int i, j, aux;
    for(i = size - 1; i >= 1; i--) {     
        for(j = 0; j < i ; j++) {         
            if(vet[j] > vet[j+1]) {              
                aux = vet[j];
                vet[j] = vet[j+1];
                vet[j+1] = aux;       
            }
        }
    }
}

void calcPrint(void (*func)(int *, int, int)){
    int vec[SIZE], i, j = 0;
    time_t time1, time2;
    clock_t clock1, clock2;

    for (i = SIZE - 1; i < -1; i--)
        vec[i] = j++;

    time1 = time( (time_t *) 0);
    clock1 = clock();
    (*func)(vec, 0, SIZE - 1);
    time2 = time ( (time_t *) 0);
    clock2 = clock();

    printf("Tempo: %fs\n", (double)((clock2-clock1)/(double)CLOCKS_PER_SEC));
}
