//Manoel Silva - 121088349
#include <stdio.h> 
#include <stdlib.h>

    typedef struct aresta{
        int a, b, peso;
    }aresta;

    int find(int *conj, int x){
        if(x != conj[x]){
            conj[x] = find(conj, conj[x]);
        }
        return conj[x];
    }

    void uniao(int *conj, int *rank, int a, int b){
        a = find(conj, a);
        b = find(conj, b);
        if(a != b){
            if (rank[a] < rank[b]){
                conj[a] = b;
            }
            else{
                conj[b] = a;
                if (rank[a] == rank[b]){
                    rank[a]++;
                }
            }
        }
    }

    int main(){
        
        int n, m, a, b, peso, test1, test2;
        scanf("%d %d", &n, &m);
        int *conj = malloc(n * sizeof(int));
        int *rank = malloc(n * sizeof(int));
        aresta *arestas = malloc(m * sizeof(aresta));
        aresta *result = malloc(m * sizeof(aresta));
        int result_size = 0;
        int soma = 0;
        aresta aux;
        
        for(int i = 0; i < n; i++){
            conj[i] = i;
            rank[i] = 0;
        }

        for(int i = 0; i < m; i++){
            scanf("%d %d %d", &a, &b, &peso);
            arestas[i].a = a;
            arestas[i].b = b;
            arestas[i].peso = peso;
            //printf("\tEu li :%d %d %d\n", arestas[i].a, arestas[i].b, arestas[i].peso);
        }

        for(int i = 0; i < m; i++){
            for(int j = 0; j < m; j++){
                if(arestas[i].peso < arestas[j].peso){
                    aresta aux = arestas[i];
                    arestas[i] = arestas[j];
                    arestas[j] = aux;
                    //printf("Eu troquei :%d %d\n", i, j);
                }
            }
        }

        for(int i = 0; i < m; i++){
            test1 = find(conj, arestas[i].a);
            test2 = find(conj, arestas[i].b);
            if(test1 != test2){
                //printf("Eu adiciono :%d %d\n", arestas[i].a, arestas[i].b);
                result[result_size] = arestas[i];
                result_size++;
                uniao(conj, rank, arestas[i].a, arestas[i].b);
                soma += arestas[i].peso;
            }
        }
        printf("%d\n", soma);
    }
