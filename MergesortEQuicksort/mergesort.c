#include <stdio.h>
#include <omp.h>
#include <time.h>
#include <stdlib.h>

#define MAX_THREADS 4096 
#define MAX 1000000
#define bool short
#define true 1
#define false 0

int vet[MAX];

//Funcao para configurar o vetor
void setVetor();

//Funcoes gerais
bool IsSorted(int *a);
void imprimir(int *a);
void copiarVetor(int *entrada, int *saida);

//Funcoes do quicksort sequencial
void quicksortSequencial();
void quick_sort(int *a, int left, int right);

//Funcoes do mergesort sequencial
void mergesortSequencial();
void mergesort(int arr[], int size);
void Merge(int vec[], int vecSize); //Essa funcao tambem sera utilizado no mergesort paralelo

//Funcoes do quicksort paralelo
void quicksortParalelo();
void quickParallel(int *a, int left, int right, int stop);
void quickSequential(int *a, int left, int right);
int partition(int *a, int left,int right,int pivot);
void swap(int *a, int i, int j);

//Funcoes de mergesort paralelo
void mergesortParalelo();
void mergesortParallel(int arr[], int size, int stop);
void mergesortSequential(int arr[], int size);

void main() {
	int opcao = 0;
	setVetor();
	printf("\nBem vindo a Ãºltima tarefa de SeminÃ¡rios II!\n");
	printf("\nTamanho do vetor: %d\n", MAX);
	while ( opcao != 6 ) {
	     printf("\nPor favor, escolha uma das opÃ§Ãµes abaixo:\n1 - Quicksort Sequencial\t2 - Mergesort Sequencial\n3 - Quicksort Paralelo");
	     printf("\t\t4 - Mergesort Paralelo\n5 - Imprimir o vetor criado\t6 - Sair do programa\n");
             scanf("%d", &opcao);
	     if ( opcao == 1 )
                quicksortSequencial();
	     else if ( opcao == 2 ) 
 		mergesortSequencial();
	     else if ( opcao == 3 ) 
		quicksortParalelo();
	     else if ( opcao == 4 ) 
		mergesortParalelo();
	     else if ( opcao == 5 ) 
		imprimir(vet);
	     else if ( opcao == 6 ) 
		printf("\nObrigado por utilizar o programa!\n");
	     else 
		printf("\nOpÃ§Ã£o invalida! Tente novamente!\n");	
	}
}
void setVetor() {
for (int i = 0; i < MAX; i++)
     vet[i] = rand() % MAX;
}

void imprimir(int *a) {
    for(int i = 0; i < MAX; i++) {
        printf("%d\t", a[i]);
        if ( i % 10 == 0 && i != 0) 
            printf("\n");
    }
}

bool IsSorted(int *a) {
	bool result = true;

	for(int i = 1; i < MAX; i++)
		if(a[i-1] > a[i]) {
			result = false;
			i = MAX;
		}

	return result;
}

void copiarVetor(int *entrada, int *saida) {

    for (int i = 0 ; i < MAX; i++)
	saida[i] = entrada[i];

}
void quicksortSequencial() {

    double start, end;
    int *arr;

    arr = malloc(MAX* sizeof(int)); 
    copiarVetor(vet,arr);

    start = omp_get_wtime();
    quick_sort(arr, 0, MAX - 1);
    end = omp_get_wtime();
 
    if (IsSorted(arr) == true)
        printf("\nResultado: ordenado!\n");
    else 
        printf("\nResultado: NÃƒO ordenado!\n");
    
    printf("Tempo gasto = %.3f\n", end - start);
    free(arr);
}

void quick_sort(int *a, int left, int right) {
    int i, j, x, y;
     
    i = left;
    j = right;
    x = a[(left + right) / 2];
     
    while(i <= j) {
        while(a[i] < x && i < right) {
            i++;
        }
        while(a[j] > x && j > left) {
            j--;
        }
        if(i <= j) {
            y = a[i];
            a[i] = a[j];
            a[j] = y;
            i++;
            j--;
        }
    }
     
    if(j > left) {
        quick_sort(a, left, j);
    }
    if(i < right) {
        quick_sort(a, i, right);
    }
}

void mergesortSequencial() {

	double start, end;
	int *arr;

        arr = malloc(MAX* sizeof(int)); 
	copiarVetor(vet,arr);

	start = omp_get_wtime();
	mergesort(arr, MAX);
	end = omp_get_wtime();

	printf("Tempo: %.3f\n", end - start);

	if(IsSorted(arr) == true)
		printf("Resultado: ordenado!\n");
	else
		printf("Resultado: NÃƒO ordenado!\n");
	free(arr);
}
// Tempo MÃ©dio : 0,2359 segundos

void mergesort(int arr[], int size) {
	int mid;
	if(size > 1) {
		mid = size / 2;
		mergesort(arr, mid);
		mergesort(arr + mid, size - mid);
		Merge(arr, size);
	}
}

void Merge(int vec[], int vecSize) {
	int mid;
	int i, j, k;
	int* tmp;

	tmp = (int*) malloc(vecSize * sizeof(int));
	if (!tmp)
		exit(1);

	mid = vecSize / 2;

	i = 0;
	j = mid;
	k = 0;

	while (i < mid && j < vecSize) {
		if (vec[i] < vec[j])
			tmp[k] = vec[i++];
		else
			tmp[k] = vec[j++];
		++k;
	}

	if (i == mid)
		while (j < vecSize)
			tmp[k++] = vec[j++];
	else
		while (i < mid)
			tmp[k++] = vec[i++];

	for (i = 0; i < vecSize; ++i)
		vec[i] = tmp[i];

	free(tmp);
}

void swap(int *a, int i, int j) {
    int tmp = a[i];
    a[i] = a[j];
    a[j] = tmp;
}

int partition(int *a, int left,int right,int pivot) {
    int pos, i;
    swap(a, pivot, right);
    pos = left;
    for(i = left; i < right; i++)
    {
        if (a[i] < a[right])
        {
            swap(a, i, pos);
            pos++;
        }
    }
    swap(a, right, pos);
    return pos;
}

void quickSequential(int *a, int left, int right) {
    if (left < right)
    {
        int pivot = (left + right) / 2;
        int pos = partition(a,left,right,pivot);

        quickSequential(a, left, pos - 1);
        quickSequential(a, pos + 1, right);
    }
}

void quickParallel(int *a, int left, int right, int stop) {
    if (left < right)
    {
        int pivot = (left + right) / 2;
        int pos = partition(a,left,right,pivot);
        if (stop > 1) {     // chamadas paralelizadas
          #pragma omp parallel sections 
	  {
		#pragma omp section 
          	quickParallel(a, left, pos - 1, stop);
		#pragma omp section 
          	quickParallel(a, pos + 1, right, stop );
	  }
        }
        else {              // chamadas sequenciais
          quickSequential(a, left, pos - 1);
          quickSequential(a, pos + 1, right);
        }
    }
}

void quicksortParalelo() { 

	int *arr;
        int i = 0;
	double start, end,speedup = 0.0;

        arr = malloc(MAX* sizeof(int)); 
	copiarVetor(vet,arr);

	for (int threads =  1; threads <= MAX_THREADS; threads *= 2) {
            #pragma omp_set_num_threads(threads);   // threads equals to 1 should be sequential...
            for (int nested = 0; nested <= 1; nested++) {  // false or true
                #pragma omp_set_nested( nested );
                for (int stop = 2; stop <= 64; stop *= 2) {
                    start = omp_get_wtime();
                    quickParallel(arr, 0, MAX - 1, stop);
                    end = omp_get_wtime();
		    speedup += end - start;
 		    i++;
                    printf("Tempo: %.3f threads: %d  nested: %d stop: %d\n", end - start, threads, nested, stop);

                    if(IsSorted(arr) == true)
                         printf("Resultado: Ordenado\n");
                    else
                         printf("Resultado: NÃ£o Ordenado\n");
                }
            }
	}
	free(arr);
	printf("\nTempo mÃ©dio : %.3f\n", speedup / i);
}

void mergesortParalelo() {

	int *arr;
        int i = 0;
	double start, end,speedup = 0.0;

        arr = malloc(MAX* sizeof(int)); 
	copiarVetor(vet,arr);

	for (int threads =  1; threads <= MAX_THREADS; threads *= 2) {
             #pragma omp_set_num_threads(threads);   // threads equals to 1 should be sequential...
            for (int nested = 0; nested <= 1; nested++) {  // false or true
                 #pragma omp_set_nested( nested );
                for (int stop = 2; stop <= 64; stop *= 2) {
                    start = omp_get_wtime();
                    mergesortParallel(arr, MAX, stop);
                    end = omp_get_wtime();
		    speedup += end - start;
		    i++;
                    printf("Tempo: %.3f threads: %d  nested: %d stop: %d\n", end - start, threads, nested, stop);

                    if(IsSorted(arr) == true)
                         printf("Resultado: Ordenado\n");
                    else
                         printf("Resultado: NÃ£o Ordenado\n");
                }
            }
	}
	free(arr);
	printf("\nTempo mÃ©dio : %.3f\n", speedup / i);
}

void mergesortSequential(int arr[], int size) {
	int mid;
	if(size > 1) {
		mid = size / 2;
		mergesortSequential(arr, mid);
		mergesortSequential(arr + mid, size - mid);
		Merge(arr, size);
	}
}

void mergesortParallel(int arr[], int size, int stop) {
	int mid;
	if(size > 1) {
		mid = size / 2;
       		if (stop > 1) {     // chamadas paralelizadas
		     #pragma omp parallel sections 
		     {
			  #pragma omp section 
     	           	  mergesortParallel(arr, mid,stop/2);
			  #pragma omp section 
		    	  mergesortParallel(arr + mid, size - mid,stop/2);
		     }
		     	  Merge(arr, size);
        	}
        	else {              // chamadas sequenciais
		     mergesortSequential(arr, mid);
		     mergesortSequential(arr + mid, size - mid);
		     Merge(arr, size);
        	}
	}
}

/*
Anotacoes sobre o desempenho dos cÃ³digos acima
 _________________________________________________________________________________________
|    	           |  Quicksort Seq| Mergesort Seq   | Quicksort Paral | Mergesort Paral |    
|------------------|---------------|-----------------|-----------------|-----------------|
| velocidade mÃ©dia |    0,1422 seg |     0,178 seg   |   0,402 seg     |    0,033 seg    |
|------------------|---------------|-----------------|-----------------|-----------------|
| MAX_THREADS      |       x       |        x        |       64        |       512       |
|------------------|---------------|-----------------|-----------------|-----------------|
| speedup          |       x       |        x        |    +-0,30       |     +-5,72      |
|------------------|---------------|-----------------|-----------------|-----------------|
| melhor tempo     |    0,128 seg  |    0,166 seg    |   0,388 seg     |    0,029 seg    |
|------------------|---------------|-----------------|-----------------|-----------------|
| pior tempo       |    0,149 seg  |    0,188 seg    |   0,529 seg     |    0,086 seg    |
|------------------|---------------|-----------------|-----------------|-----------------|
|__________________|_______________|_________________|_________________|_________________|

ObservaÃ§Ãµes finais:

Ã‰ interessante antes observar que para as execuÃ§Ãµes realizadas no meu hardware, eu tambÃ©m utilizei a funcao "-O3" para a renderizaÃ§Ã£o do
programa, em mÃ©dia, os programas em geral ficaram 45% mais rÃ¡pido.

Sobre os mÃ©todos de organizaÃ§Ã£o: o quicksort apresentou melhores resultados, quando sequencial, com tempos que variavam desde 
0,128 atÃ© 0,149 , enquanto que o mergesort varia entre 0,166 e 0,188. PorÃ©m, ao paralelizar os cÃ³digos, o quicksort ficou mais
lento( com uma mÃ©dia de 0,429 seg ), enquanto que o mergesort fica mais rÃ¡pido (com um tempo mÃ©dio de 0,033 seg ).

*/
