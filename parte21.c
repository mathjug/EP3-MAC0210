/*
    EP3 MAC0210 - PARTE 2
    ALUNOS: Matheus Sanches Jurgensen (12542199) e André Nogueira Ribeiro (12542230)
    COMO COMPILAR: gcc -o parte21 parte21.c -lm
    COMO EXECUTAR: ./parte21
*/

#include <stdio.h>
#include <stdlib.h> // rand() e srand()
#include <time.h> // time()
#include <math.h> 


double uniMonteCarlo(int n, double (*f)(double)) {
    /*
    Implementa o Método de Monte Carlo para o caso univariado. Nesse sentido, são 2 os seus parâmetros:
    n = quantidade de número aleatórios a serem gerados
    f = função cuja integral deseja-se aproximar
    Retorna o valor da integral aproximado pelo método.
    */
    double valor_final = 0;
    srand(time(NULL));
    for (int i = 0; i < n; i++) {
        valor_final += f((double)rand() / (double)RAND_MAX);
    }
    valor_final = (valor_final / n);
    return valor_final;
}

double sen(double x){
    /*
    Deseja-se aproximar a integral de 0 até 1 de sen(x).
    Visando esse objetivo, essa função servirá para retornar o valor de sen(x)
    para função que realiza a aproximação.
     */
    return (sin(x));
}

double x3(double x){
    /*
    Deseja-se aproximar a integral de 3 até 7 de (x³).
    Visando esse objetivo, essa função servirá para retornar o valor de 
    ((4*u+3)*(4*u+3)*(4*u+3))*4 para função que realiza a aproximação.
    Explicando melhor, como a função em questão aproxima integrais de 0 até
    1, foi necessário realizar uma substituição, utilizando u = (x-3)/4 
    e 4*du = dx, de modo a ajustar os limites de integração. Substituindo 
    esses valores na integral inicial, conclui-se que a integral inicial 
    e igual a integral de 0 até 1 de ((4*u+3)*(4*u+3)*(4*u+3))*4.
     */
    double u = x;
    return (pow((4*u+3),3)*4);
}

double ex(double x){
    /*
    Deseja-se aproximar a integral de 3 até 7 de e^(⁻x).
    Visando esse objetivo, essa função servirá para retornar o valor de 
    1 para função que realiza a aproximação.Explicando melhor, como o método
    utilizado aproxima integrais de 0 até 1, foi necessário realizar uma 
    substituição, utilizando u = -e^(-x) + 1 e du = e^(-x) dx, de modo a 
    ajustar os limites de integração. Substituindo esses valores na integral 
    inicial, conclui-se que a integral inicial é igual a integral de 0 até 1 
    de 1.
     */
    return (1);
}

int main() {
    int n;
    printf("Qual o valor de n? ");
    scanf("%d", &n);
    
    double s = uniMonteCarlo(n, sen);
    printf("aprox integral de sen(x) de 0 ate 1: %f\n", s);

    double t = uniMonteCarlo(n, x3);
    printf("aprox integral de (x)^3 de 3 ate 7: %f\n", t);

    double e = uniMonteCarlo(n, ex);
    printf("aprox integral de 0 até +infinito de e^(⁻x): %f\n", e);
}
