/*Ejercicio 8*/
/*
Secciones
	Realice un programa OpenMP el cual disponga de un conjunto de funciones capaces de 
	calcular el mínimo, máximo, la multiplicación y desviación estándar de un conjunto
	de un millón de elementos contenidos en un arreglo.
	Cada una de estas funciones deberá recibir por parámetro los datos a procesar y
	deberá devolver el valor resultante.
	Se pide que realice un programa OpenMP que sea capaz de realizar en paralelo todas
	estas operaciones. El programa además deberá informar por pantalla que thread ha
	realizado que operación.
	Finalmente se pide que calcule el speedup de esta aplicación. Para realizar este
	cálculo debe trabajar con los valores promedios obtenidos de 50 ejecuciones tanto
	para la solución paralela como para la solución secuencial.
*/

/*Librerias*/
#include <omp.h>
#include <stdio.h>
#include <math.h>
#include <stdlib.h>
#include <time.h>

/*constantes*/
#define N 1000000
#define ITERACIONES 50

void ejecucion_opemnMP(int []);
void ejecucion_secuncial(int []);

void imprimir_costo (double []);

void inicializar(int[]);
int minimo (int[]);
int maximo (int[]);
int multiplicacion(int[]);
float desviacion(int []);

double promedio (double []);

int main() {
	int arreglo[N],i, j;
	double start, end;
    double costo_open=0, costo_secuncial=0, promedio_open=0, promedio_secuencial=0, speedup=0;

    /*Inicializo el arreglo*/
	for (i = 0; i < N; i++)
	{
		arreglo[i]=rand() % (100) +1;//Numero ramdom entre N y 1
		//printf("arreglo[%d]=%d\n", i, arreglo[i]);
	}
	

	for (j = 0; j < ITERACIONES; j++)
	{
		printf("Ejecicion de openMP\n");
		start = omp_get_wtime();	
		ejecucion_opemnMP(arreglo);
		end = omp_get_wtime();
		costo_open= costo_open + (end - start);
		printf("_____________________________________________________________________________________\n");

		printf("Ejecicion secuencial\n");
		start = omp_get_wtime();
		ejecucion_secuncial(arreglo);
		end = omp_get_wtime();
		costo_secuncial=costo_secuncial+ (end - start);
		//printf("costo_secuncial[%d]=%f  ",j, costo_secuencial[i]);
		printf("_____________________________________________________________________________________\n");
		
	}

	//printf("\nCosto_open\n");
	//imprimir_costo(costo_open);
	promedio_open=costo_open/ITERACIONES;
	printf("El promedio de la ejecucion con OpenMP es de: %f \n", promedio_open );
	
	//printf("\nCosto secuencial\n");
	//imprimir_costo(costo_secuncial);
	promedio_secuencial=costo_secuncial/ITERACIONES;
	printf("El promedio de la ejecucion secuencial es de: %f \n", promedio_secuencial );
    
	/*Calcular speedup*/
	speedup = promedio_secuencial/promedio_open;
	printf("El speed up obtenido es de: %f\n",speedup); 
}

double promedio (double costo[]){
	double suma=0, prom=0;
	int i=0;
	for (i = 0; i < ITERACIONES; ++i)
	{
		suma=suma+costo[i];
	}
	prom=suma/ITERACIONES;
	return(prom);

}


void imprimir_costo (double costo[]){
	int i=0;
	for (i = 0; i < ITERACIONES/2; i++)
	{
		printf("  %d  	", i);
	}

	printf("\n");

	for (i = 0; i < ITERACIONES/2; i++)
	{
		printf("%f  ", costo[i]);
	}
	printf("\n");	

	for (i = ITERACIONES/2; i < ITERACIONES; i++)
	{
		printf("%d  	", i);
	}

	printf("\n");

	for (i = ITERACIONES/2; i < ITERACIONES; i++)
	{
		printf("%f  ", costo[i]);
	}
	printf("\n");

}

void ejecucion_opemnMP(int arreglo[]){
	int min, max,  i=0, j=0, k=0, l=0;
	float media=0, suma=0, aux=0, aux2=0, des;
	double mult=1;
	#pragma omp parallel 
	{
		#pragma omp sections 
		{
			/*Minimo*/
			#pragma omp section
			{
				min=minimo(arreglo);
				printf("Hilo %d: El minimo del arreglo es: %d\n",omp_get_thread_num(), min);
			}
			/*Maximo*/
			#pragma omp section
			{
				max=maximo(arreglo);
				printf("Hilo %d: El maximo del arreglo es: %d\n",omp_get_thread_num(), max);

			}
			/*Multiplicacion*/
			#pragma omp section
			{
				mult = multiplicacion(arreglo);
				
				printf("Hilo %d: La multiplicación del arreglo es: %f\n", omp_get_thread_num(), mult);

			}

			/*Desviacion*/
			#pragma omp section
			{
				des= desviacion(arreglo);
				printf("Hilo %d: La desviación del arreglo es: %f\n", omp_get_thread_num(), des);

			}

		}

	}

}

void ejecucion_secuncial(int a[]){
	int min, max, mul;
	float des;
	min= minimo(a);
	max= maximo(a);
	mul= multiplicacion(a);
	des= desviacion(a);
	printf("El minimo del arreglo es: %d\n", min);
	printf("El maximo del arreglo es: %d\n", max);
	printf("La multiplicación del arreglo es: %d\n", mul);
	printf("La desviación del arreglo es: %f\n", des);

}

void inicializar(int arreglo[]){
	int i=0;
	for (i = 0; i < N; i++)
	{
		arreglo[i]=rand() % (N) +1;//Numero ramdom entre N y 1
	}

}

int minimo(int arreglo[]){
	int i=0, minaux=arreglo[0];
	for (i = 0; i < N; i++)
	{
		if (minaux>arreglo[i]){
			minaux= arreglo[i];
		}
	}
	return (minaux);
}

int maximo(int arreglo[]){
	int i=0, maxaux=arreglo[0];
	for (i = 0; i < N; i++)
	{
		if (maxaux<arreglo[i]){
			maxaux= arreglo[i];
		}
	}
	return (maxaux);
}

int multiplicacion (int arreglo[]){
	int multaux=1, i=0;
	for (i = 0; i < N; i++)
	{
		multaux=multaux * arreglo[i];
	}
	return (multaux);

}

float desviacion (int arreglo[]){
	float media=0, suma=0, aux=0, aux2=0, des=0;
	int i=0;
	for ( i = 0; i < N; i++)
	{
		suma=suma + arreglo[i];
	}
	media= suma / N;
	suma=0;
	for (i = 0; i < N; i++)
	{
		aux2= arreglo[i]-media;
		suma= suma + pow(aux2, 2);
	}

	aux= suma/N;
	des= sqrt(aux);
	return (des);
}
