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

#include <omp.h>
#include <stdio.h>
#include <math.h>
#include <stdlib.h>
#define N 4

void inicializar(int[]);
int minimo (int[]);
int maximo (int[]);
int multiplicacion(int[]);
float desviacion(int []);

int main(){
	int a[N], min, max, mul;
	float des;
	inicializar(a);
	min= minimo(a);
	max= maximo(a);
	mul=multiplicacion(a);
	des=desviacion(a);

	for (int i = 0; i < N; i++)
	{
		printf("%d  ", i);
	}

	printf("\n");

	for (int i = 0; i < N; i++)
	{
		printf("%d  ", a[i]);
	}
	printf("\n");	


	printf("El minimo del arreglo es: %d\n", min);
	printf("El maximo del arreglo es: %d\n", max);
	printf("La multiplicación del arreglo es: %d\n", mul);
	printf("La desviación del arreglo es: %f\n", des);

}

void inicializar(int arreglo[]){
	for (int i = 0; i < N; i++)
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
	int multaux=1;
	for (int i = 0; i < N; i++)
	{
		multaux=multaux * arreglo[i];
	}
	return (multaux);

}

float desviacion (int arreglo[]){
	float media=0, suma=0, aux=0, aux2=0, des=0;
	for (int i = 0; i < N; i++)
	{
		suma=suma + arreglo[i];
	}
	media= suma / N;
	suma=0;
	for (int i = 0; i < N; i++)
	{
		aux2= arreglo[i]-media;
		suma= suma + pow(aux2, 2);
	}

	aux= suma/N;
	des= sqrt(aux);
	return (des);
}

