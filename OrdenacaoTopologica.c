//Manoel Silva - 121088349
#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#define TAM 100

    typedef struct _tno {
        int vert;
        struct _tno *prox;
    }tno;

    void insere(tno **ptlista, int x){ 
        tno *novo = malloc(sizeof(tno));
        if (novo == NULL){
            printf("Erro de alocacao de memória\n");
            exit(1);
        }
        novo->vert = x;
        novo->prox = *ptlista;
        *ptlista = novo;
    }
    
    int main(){
        
        char temp;
        int vertices,arestas;
        char *entrada = malloc(sizeof(char)*TAM);
        if (entrada == NULL){
            printf("Erro de alocacao de memória\n");
            exit(1);
        }
        
        // Leitura do número de vértices e arestas
        printf("Digite o número de vértices e arestas (V A) e depois pressione enter e insira os vértices conectados aos vértices em ordem crescente\n");
        scanf("%[^\n]", entrada);
        sscanf(entrada, "%d %d", &vertices, &arestas);
        scanf("%c", &temp);

        tno **adj = malloc(sizeof(tno*)*(vertices+1));
        if (adj == NULL){
            printf("Erro de alocacao de memória\n");
            exit(1);
        }
        for (int i = 0; i <= vertices; i++){
            adj[i] = NULL;
        }
        
        //Leitura da lista de adjacências 
        char *linha = NULL;
        size_t tamLinha = 0;
        for(int i = 1; i <= vertices; i++){
            getline(&linha,&tamLinha,stdin);
            int pos = 0;
            int numLido = 0;
            int numChars;
      
            while (sscanf(&linha[pos], " %d %n", &numLido, &numChars) > 0) {
                pos += numChars;
                if(strlen(linha) != 0){
                    //printf(" insere em adj [ %d ] o vertice %d\n",i, numLido);  
                    insere(&adj[i], numLido);
                }
            }
        }
        //Inicializando os vetores de grau e ordem
        tno *pt;
        int *gent = malloc(sizeof(int)*(vertices+1));
        if (gent == NULL){
            printf("Erro de alocacao de memória\n");
            exit(1);
        }
        int *ordem = malloc(sizeof(int)*(vertices));
        if (ordem == NULL){
            printf("Erro de alocacao de memória\n");
            exit(1);
        }
        
        // Algoritmo de ordenação topológica
        for (int i = 1; i <= vertices; i++){
            gent[i] = 0;
        }

        int fim = 0, inicio = 0;

        for(int i = 1; i <= vertices; i++){
            pt = adj[i];
            while(pt != NULL){
                gent[pt->vert]++;
                //printf("\nGent[%d] = %d", pt->vert, gent[pt->vert]);
                pt = pt->prox;
            }
        }

        for (int i = 1; i <= vertices; i++){
            if (gent[i]==0){
                ordem[fim] = i;
                fim++;
            }
        }

        while(inicio != fim){
            int v = ordem[inicio];
            int w;
            inicio++;
            pt = adj[v];
            while(pt != NULL){
                w = pt->vert;
                gent[w]--;
                //printf("\n\tGent[%d] = %d", w, gent[w]);
                if (gent[w] == 0){
                    ordem[fim] = w;
                    //printf("\n\tOrdem[%d] = %d\n", fim, ordem[fim]);
                    fim++;
                }
                pt = pt->prox;
            }
        }
        printf("\nOrdenação topológica: ");
        for(int i = 0; i < vertices; i++){
            printf("%d ", ordem[i]);
        }

        free(adj);
        free(gent);
        free(pt);
        free(ordem);
        free(entrada);
        free(linha);
        return 0;
    }
