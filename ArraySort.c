#include <stdio.h>
#include <stdlib.h>
#include <time.h>
#include <string.h>
#define MAX 100000

    void troca(int *a, int *b){
        int tmp = *a;
        *a = *b;
        *b = tmp;
    }

    void imprimir(int vet[], int tam){
        for(int i = 0; i < tam; i++){
            printf(" %d ", vet[i]);
        }
    }

    void bubble_sort(int vet[], int tam){
        for(int i =0; i < tam - 1; i++){
            for(int j = 0; j < tam - i - 1; j++){
                if(vet[j] > vet[j+1]){
                    troca(&vet[j],&vet[j+1]);
                }
            }
        }
    }

    void merge(int vet[], int inicio, int meio, int fim){

        //criando um vetor auxiliar e copiando o vetor original
        int *tmp;
        tmp = (int*)malloc(sizeof(int) * (fim - inicio));

        int i = inicio;
        int j = meio;
        int pos = 0;

        while(i < meio && j < fim){
            if(vet[i] <= vet[j]){
                tmp[pos++] = vet[i++];
            } else{
                tmp[pos++] = vet[j++];
            }
        }

        while(i < meio){
            tmp[pos++] = vet[i++];
        }
        
        while(j < fim){
            tmp[pos++] = vet[j++];
        }

        for(i = inicio; i < fim; i++){
            vet[i] = tmp[i - inicio];
        }
        free(tmp);
    }
    
    void merge_sort(int vet[], int inicio, int fim){
        if(inicio < (fim - 1)){
            int meio = (inicio + fim)/ 2;
            merge_sort(vet, inicio, meio);
            merge_sort(vet, meio, fim);
            merge(vet, inicio, meio, fim);
        }
    }

    int particiona(int vet[], int inicio, int fim){
        //pivot randomico
        int p = inicio + rand()%(fim - inicio + 1);
        troca(&vet[inicio], &vet[p]);
        
        int pivot = vet[inicio];
        int i = inicio;
        int j = fim ;
        
        while(i < j){
            while(i < fim && vet[i] <= pivot){
                i++;
            }
            while(j > inicio && vet[j] >= pivot){
                j--;
            }
            if(i < j){
                troca(&vet[i], &vet[j]);
            }
        }
        vet[inicio] = vet[j];
        vet[j] = pivot;
        return j; 
    }

    void quick_sort(int vet[], int inicio, int fim){
        if(inicio < fim){
            int pivot = particiona(vet, inicio, fim);
            quick_sort(vet, inicio, pivot - 1);
            quick_sort(vet, pivot + 1, fim);
        }
    }

    int main(int argc, char *argv[]){
        int *vet, num, n;
        int flag = 0;

        if(argc <= 2){
            printf("\tUse os parâmetros -n VALOR para atribuir o tamanho do vetor aleatório. Depois use -q para o Quicksort, -m para o Mergesort e nenhum desses dois para o Bubblesort!\n");
            return 1;
        }

        for(int c = 0; c < argc; c++){

            if(!strcmp(argv[c], "-n")){
                //cria um vetor de tamanho n com valores aleatorios

                n = atoi(argv[c + 1]);
                vet = (int*)malloc(sizeof(int) * n);
                srand(time(NULL));

                for (int i = 0; i < n; i++){
                    num = rand() % MAX;
                    vet[i] = num;
                }

                flag++;
                printf("\nVetor criado: ");
                imprimir(vet, n);
                printf("\n");
            } 
        }
        if(!flag){
            printf("\tNão foi informado o tamanho do vetor usando -n VALOR\n");
            return 1;
        }

        for(int c = 0; c < argc; c++){
            if(!strcmp(argv[c], "-m")){
                //algoritmo mergesort
                clock_t tempo = clock();

                merge_sort(vet, 0, n);
                
                tempo = clock() - tempo;
                double tempo_percorrido = ((double)tempo)/CLOCKS_PER_SEC;

                printf("\nVetor Ordenado: ");
                imprimir(vet, n);
                printf("\n");
                printf("\nO Mergesort foi concluido em %f segundos.", tempo_percorrido);
            }
            if(!strcmp(argv[c], "-q")){
                //algoritmo quicksort
                clock_t tempo = clock();

                quick_sort(vet, 0, n-1);
                
                tempo = clock() - tempo;
                double tempo_percorrido = ((double)tempo)/CLOCKS_PER_SEC;

                printf("\nVetor Ordenado: ");
                imprimir(vet, n);
                printf("\n");
                printf("\nO Quicksort foi concluido em %f segundos.", tempo_percorrido);
            }
        }

        if(argc == 3){
            //algoritmo bubble sort 
            clock_t tempo = clock();

            bubble_sort(vet, n);

            tempo = clock() - tempo;
            double tempo_percorrido = ((double)tempo)/CLOCKS_PER_SEC;
            
            printf("\nVetor Ordenado: ");
            imprimir(vet, n);
            printf("\n");
            printf("\nO BubbleSort foi concluido em %f segundos.", tempo_percorrido);
        }
        free(vet);
        return 0;
    }
