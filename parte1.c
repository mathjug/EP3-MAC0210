/*
    EP3 MAC0210 - PARTE 1
    ALUNOS: Matheus Sanches Jurgensen (12542199) e André Nogueira Ribeiro (12542230)
    COMO COMPILAR: gcc -o parte1 parte1.c
    COMO EXECUTAR: ./parte1
*/

#include <stdio.h>
#include <math.h>
#include <stdlib.h>

double lagrange(double dados[], int n_pontos, double x) {
    /*
    Método que, recebendo um conjunto de pontos conhecidos a serem interpolados (de forma que as abscissas e as
    ordenadas estão dispostas intercaladas), além de um valor de x a ser calculado com um polinômio interpolador,
    calcula esse valor por meio do polinômio interpolador de Lagrange que interpola todos os pontos conhecidos.
    */
    double y_final = 0;
    for (int i = 0; i < 2*n_pontos; i = i + 2) {
        double y_parcial = dados[i + 1];
        for (int j = 0; j < 2*n_pontos; j = j + 2) {
            if (i != j)
                y_parcial = y_parcial * ((x - dados[j]) / (dados[i] - dados[j]));
        }
        y_final += y_parcial;
    }
    return y_final;
}

double trapezio(double dados[], int n_pontos, int n) {
    /*
    Método que aproxima a integral (trabalho da força) pela Regra do Trapézio Composto. Os argumentos dados[] e
    n_pontos são os mesmos do método de Lagrange. Além disso, n é quantidade de subintervalos nos quais se imple-
    menta o método.
    */
    double a = dados[0], b = dados[(2 * n_pontos) - 2];
    double h = fabs(b - a) / n;
    double soma = (dados[1] + dados[(2 * n_pontos) - 1]) / 2;
    for (int i = 1; i < n; i++) {
        double xi = a + h * i;
        soma += lagrange(dados, n_pontos, xi);
    }
    soma = h * soma;
    return soma;
}

double simpson(double dados[], int n_pontos, int n) {
    /*
    Método que aproxima a integral (trabalho da força) pela Regra de Simpson Composto. Os argumentos dados[] e
    n_pontos são os mesmos do método de Lagrange. Além disso, n é quantidade par de subintervalos nos quais se
    implementa o método.
    */
    double a = dados[0], b = dados[(2 * n_pontos) - 2];
    double h = fabs(b - a) / n;
    double soma_final = dados[1] + dados[(2 * n_pontos) - 1];
    double soma1 = lagrange(dados, n_pontos, a + h);
    double soma2 = 0;
    for (int i = 2; i < n - 1; i+= 2) {
        double xi = a + h * i;
        soma1 += lagrange(dados, n_pontos, xi + h);
        soma2 += lagrange(dados, n_pontos, xi);
    }
    soma_final += 4 * soma1 + 2 * soma2;
    soma_final *= h / 3;
    return soma_final;
}

int main() {
    double dados[] = {0, 0.0, 5, 1.5297, 10, 9.5120, 15, 8.7025, 20, 2.8087, 25, 1.0881, 30, 0.3537};
    int n_pontos = 7;
    int n;
    printf("Quantidade de subintervalos: ");
    scanf("%d",&n);
    printf("Trabalho calculado pela regra do trapézio composto: %f\n", trapezio(dados, n_pontos, n));
    printf("Trabalho calculado pela regra de simpson composto: %f\n", simpson(dados, n_pontos, n));
    return 0;
}