/*
    EP3 MAC0210 - PARTE 2 (A) - Monte Carlo Unidimensional
    ALUNOS: Matheus Sanches Jurgensen (12542199) e André Nogueira Ribeiro (12542230)
    COMO COMPILAR: gcc -o parte2A parte2A.c -lm
    COMO EXECUTAR: ./parte2A
*/

#include <stdio.h>
#include <stdlib.h> // rand() e srand()
#include <time.h> // time()
#include <math.h>

double uniMonteCarlo(int n, double (*f)(double)) {
    /*
    Implementa o Método de Monte Carlo para o caso univariado. Nesse sentido, são 2 os seus parâmetros:

    n = quantidade de número aleatórios a serem gerados
    f = função cuja integral deseja-se aproximar, a qual recebe um double como seu argumento e retorna
        outro double
    
    Retorna o valor da integral aproximado pelo método.
    */
    double valor_final = 0;
    srand(time(NULL));
    for (int i = 0; i < n; i++)
        valor_final += f((double)rand() / (double)RAND_MAX);
    valor_final /= n;
    return valor_final;
}

double seno(double x) {
    /*
    Função que, dado um x, retorna o valor de sen(x).
    */
    return sin(x);
}

double cubo(double x) {
    /*
    Função que, dado um x, retorna o valor de g(x) = 4(4x + 3)³. Essa é uma função que substitui f(x) = x³,
    visto que a integral da primeira está no intervalo [0,1], o qual é o adequado para o método de Monte
    Carlo, enquanto a da segunda está em [3,7], que é inadequado.
    */
    return 4 * pow(4*x + 3, 3);
}

double exponencial(double x) {
    /*
    Função que, dado um x, retorna o valor de e^(-x).
    */
    return exp(-x);
}

double auxExponencial(double x) {
    /*
    Função que retorna o valor de e⁻¹. Essa função é importante porque a sua integral, no intervalo [0,1],
    substitui a integral da função e^(-x) no intervalo [1,+∞[.
    */
    return 1 / exp(1);
}

double integralExponencial(int n) {
    /*
    Função que calcula e retorna a integral de e^(-x) no intervalo entre 0 e +∞, por meio do método de Monte
    Carlo, com n números aleatórios, em duas etapas:
        1) Calcula-se a integral de e^(-x) em [0,1].
        2) Calcula-se a integral de 1/e em [0,1], a qual é equivalente à integral de e^(-x) em [1,+∞[.
    */
    return uniMonteCarlo(n, exponencial) + uniMonteCarlo(n, auxExponencial);
}

int main() {
    int n;
    printf("Qual o valor de n? ");
    scanf("%d", &n);
    double exp = integralExponencial(n);
    printf("O valor da integral da exponencial é: %f\n", exp);
}