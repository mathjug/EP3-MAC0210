/*
    EP3 MAC0210 - PARTE 2
    ALUNOS: Matheus Sanches Jurgensen (12542199) e André Nogueira Ribeiro (12542230)
    COMO COMPILAR: gcc -o parte2 parte2.c
    COMO EXECUTAR: ./parte2
*/

#include <stdio.h>
#include <stdlib.h> // rand() e srand()
#include <time.h> // time()

double multiMonteCarlo(int n, int m, double (*f)(double*)) {
    /*
    Implementa o Método de Monte Carlo para o caso multivariado. Nesse sentido, são 3 os seus parâmetros:

    n = quantidade de número aleatórios a serem gerados
    m = quantidade de dimensões da função cuja integral deseja-se aproximar
    f = função cuja integral deseja-se aproximar, a qual recebe um vetor de double's com seus argumentos
        e retorna um double
    
    Retorna o valor da integral aproximado pelo método.
    */
    double valor_final = 0;
    srand(time(NULL));
    for (int i = 0; i < n; i++) {
        double variaveis[m];
        for (int j = 0; j < m; j++)
            variaveis[j] = ((double)rand() / (double)RAND_MAX);
        valor_final += f(variaveis);
    }
    valor_final = (valor_final / n);
    return valor_final;
}

double auxCalcularPi(double* variaveis) {
    /*
    Método auxiliar para a aproximação do valor de pi. Recebe um vetor do tipo [x,y]e verifica se o ponto
    (x,y) está contido no círculo centrado na origem e de raio unitário.
    */
    double x = variaveis[0];
    double y = variaveis[1];
    double var = x*x + y*y;
    if (var <= 1)
        return 4; // colocando o 4 para dentro da integral
    else
        return 0;
}

int main() {
    int n;
    printf("Qual o valor de n? ");
    scanf("%d", &n);
    double pi = multiMonteCarlo(n, 2, auxCalcularPi);
    printf("O valor de pi é: %f\n", pi);
}