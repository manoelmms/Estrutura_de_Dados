//Manoel Silva - 121088349
#include <stdio.h>
#include <math.h>
#include <stdlib.h>
#define TAM 100

    void overflow_c(char pilha[], int *tam){
        //copia para um vetor auxiliar
        char *tmp, *v;
        tmp = (char*)malloc(2*(*tam)*sizeof(char));
        for (int i = 0; i < (*tam) - 1; i++){
            tmp[i] = pilha[i];
        }

        free(pilha);
        v = tmp;
        *tam = 2 * (*tam);
    }
    void overflow(double pilha[], int *tam){
        //copia para um vetor auxiliar
        double *tmp, *v;
        tmp = (double*)malloc(2*(*tam)*sizeof(double));
        for (int i = 0; i < (*tam) - 1; i++){
            tmp[i] = pilha[i];
        }

        free(pilha);
        v = tmp;
        *tam = 2 * (*tam);
    }

    void push_c(char pilha[],int *topo, int *tam, char x){
        //printf("pushc : %c, %d, %d\n", x, *topo, *tam);
        if ((*topo) == (*tam)){
            //pilha cheia 
            overflow_c(pilha, tam);
        }
        if((*topo) < (*tam)){
            pilha[(*topo)] = x;
            (*topo)++;
            //printf("pushc 2: %c, %d, %d\n", pilha[(*topo)-1], *topo, *tam);
        }
    }
    
    double pop(double pilha[], int *topo){
        if((*topo) != 0){
            return pilha[--(*topo)];
        } else{
            return -1;
        }
    }
    
    void push(double pilha[],int *topo, int *tam, double x){
        //printf("push : %f, %d, %d\n", x, *topo, *tam);
        if (*topo == *tam){
            //pilha cheia 
            overflow(pilha, tam);
        }
        else if(*topo < *tam){
            int top = *topo;
            pilha[top] = x;
            (*topo)++;
            //printf("push 2: %f, %d, %d\n", pilha[top], *topo, *tam);

        }
    }

    char pop_c(char pilha[], int *topo){
        if((*topo) != 0){
            return pilha[--(*topo)];
        } else{
            return '$';
        }
    }

    char checknumber(char ch) 
    {
        if ((ch >= '0' && ch <= '9') || ch == '.') return 1;
        else return 0;
    }

    int precedence(char ch)
    {
        if(ch == '+'||ch == '-'){
            return 1;
        } 
        if(ch == '*'||ch == '/') {
            return 2;
        }
        return 0;
    }

    double calculate(char moperator, double num1, double num2) 
    {
        double result;
        switch (moperator)
        {
        case '+':
            result = num1 + num2;
            break;
        case '-':
            result = num1 - num2;
            break;
        case '*':
            result = num1 * num2;
            break;
        case '/':
            result = num1 / num2;
            break;
        case '^':
            result = pow(num1, num2);
            break;
        default:
            printf("Expressão Inválida\n");
            //printf( "%f, %c, %f", num1, moperator, num2);
            exit(-1);
        }
        return result;
    }

    double evaluate(char expr[]) {
        //inicializando pilha dos números
        double *numbers;
        int *toponum, *tamnum;
        numbers = (double*)malloc(TAM*sizeof(double));
        toponum = (int*)malloc(sizeof(int));
        tamnum = (int*)malloc(sizeof(int));
        if (numbers == NULL){
            printf(("Sem memória!"));
            return 1;
        }
        *tamnum = TAM;
        *toponum = 0;

        //inicializando pilha dos operandos 
        char *operators;
        int *topoop, *tamop;
        operators = (char*)malloc(TAM*sizeof(char));
        topoop = (int*)malloc(sizeof(int));
        tamop = (int*)malloc(sizeof(int));
        if (operators == NULL){
            printf(("Sem memória!"));
            return 1;
        }
        *tamop = TAM;
        *topoop = 0;

        char ch, op; 
        int  i = 0;
        double num1, num2;
        
        while ((ch = expr[i]) != '\0') {
            if (ch == '('){
                push_c(operators, topoop, tamop, ch);
            }
            else if (checknumber(ch)) {
                    int value = 0;
                    while (checknumber(expr[i])){
                        value = value * 10 + expr[i++] - '0';
                    }
                    push(numbers, toponum, tamnum, value);
                    i--;
            } 
            else if (ch == ')'){
                while (((*topoop) != 0)  && operators[(*topoop) - 1] != '('){
                    //fazer precedencia aqui
                    num2 = pop(numbers, toponum);
                    num1 = pop(numbers, toponum);
                    op = pop_c(operators, topoop);
                    push(numbers, toponum, tamnum, calculate(op, num1, num2));
                }
                pop_c(operators, topoop);
            }                    
            else{
                if(((*topoop) != 0)  && (precedence(operators[(*topoop) -1]) > precedence(ch))){
                    num2 = pop(numbers, toponum);
                    num1 = pop(numbers, toponum);
                    op = pop_c(operators, topoop);
                    push(numbers, toponum, tamnum, calculate(op, num1, num2));
                }
                push_c(operators, topoop, tamop, ch);
            }
            i++;  
        }
        while ((*topoop) != 0) {
                num2 = pop(numbers, toponum);
                num1 = pop(numbers, toponum);
                op = pop_c(operators, topoop);
                push(numbers, toponum, tamnum, calculate(op, num1, num2));
        }
        
        double result = numbers[0];
        free(numbers);
        free(tamnum);
        free(toponum);
        free(operators);
        free(tamop);
        free(topoop);
        return result;
    }

    int main(void) {
        char *expression;
        expression = (char*)malloc(TAM*sizeof(char));
        double result;

        printf("Entre com a Expressão a ser avaliada (Indique a multiplicação antes do parêntesis e somente inteiros): "); scanf("%[^\n]", expression);
        result = evaluate(expression);
        printf("Resultado = %lf\n", result);
        free(expression);
        return 0;
    }
