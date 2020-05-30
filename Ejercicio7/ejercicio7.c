/*Ejercicio 7*/
/*Planificación de bucles
Ejecute los siguientes códigos. Describa cual es la principal diferencia entre ellos.*/
/*
La diferencia de los codicos se encuentr en la clausula schecule
	- El primer programa realiza un reparto de iteraciones estatico. Se realiza una planificacion
	  estadica de que parte de la iteracion le toca a cada proceso.
	- El segundo programa hace un reparto de iteraciones dinamico. Va asignando en ejecucion a 
	  que hilo le toca cada tarea. dependiendo la carga que tenga en ese momento.
*/

/*Codigo 1*/
/*#include <omp.h>
#include <stdio.h>
#include <unistd.h>
#define N 40
int main () {
	int tid;
	int A[N];
	int i;
	for(i=0; i<N; i++)
		A[i]=-1;

	#pragma omp parallel for schedule(static,4) private(tid)
		for (i=0; i<N; i++){
			tid = omp_get_thread_num();
			A[i] = tid;
			usleep(1);
		}
	for (i=0; i<N/2; i++)
		printf (" %2d", i); 
	printf ("\n");
	for (i=0; i<N/2; i++) 
		printf (" %2d", A[i]);
	printf ("\n\n\n");
	for (i=N/2; i<N; i++)
		printf (" %2d", i);
	printf ("\n");
	for (i=N/2; i<N; i++)
		printf (" %2d", A[i]);
	printf ("\n\n");
}*/

#include <omp.h>
#include <stdio.h>
#include <unistd.h>
#define N 40
int main () {
	int tid;
	int A[N];
	int i;
	for(i=0; i<N; i++) 
		A[i]=-1;
	#pragma omp parallel for schedule(dynamic,4) private(tid)
		for (i=0; i<N; i++){
			tid = omp_get_thread_num();
			A[i] = tid;
			usleep(1);
		}
	for (i=0; i<N/2; i++) 
		printf (" %2d", i); 
	printf ("\n");
	for (i=0; i<N/2; i++) 
		printf (" %2d", A[i]);
	printf ("\n\n\n");
	for (i=N/2; i<N; i++) 
		printf (" %2d", i); 
	printf ("\n");
	for (i=N/2; i<N; i++) 
		printf (" %2d", A[i]);
	printf ("\n\n");
}