//Programa que permite o usuario inserir a precisao do PI
//Criado por Gustavo Lopes Rodrigues

#include <stdio.h>

//Função que encapsula o código do cálculo do PI
double calcularPi();

//Função main
int main(void){
   int precisao;
   scanf("%d", &precisao);
   double pi = calcularPi(precisao);
   printf("O valor de PI é: %f\n", pi);
}

double calcularPi(int precisao) {
   double x = 1, resultado = 4.0;
   for(int i=0; i < precisao; i++){
	x += 2;
	if ( i % 2 == 0 ) {
            resultado -= 4/x;
	}
	else {
            resultado += 4/x;
	}
   }
   return resultado;	  
}
