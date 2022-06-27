#include <stdio.h>
#include <stdlib.h> // rand() e srand()
#include <time.h> // time()

double multiMonteCarlo(int n, int m, double (*f)(double*)) {
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