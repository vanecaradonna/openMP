/*Ejercicio 2
Repartición de tareas
1) ¿Qué diferencia hay en la ejecución de estos dos programas?
	En el programa 1 se ejecuta en cada hilo un bucle de 10 iteraciones.
	En el programa 2 se fragmenta el bucle entre los hilos disponibles, es decir cada hilo realiza un pedacito
	de la ejecucion del bucle, es decir, el for se hace solo una vez.
2) ¿Qué sucedería si la variable n no fuera privada?
	En el programa 1, como ahora n es compartida, todos los hilos la modifican, entonces el bucle pierde la coherencia
	y se omiten iteraciones en algunos hilos.
*/


//Programa 1

#include <omp.h>
#include <stdio.h>
int main(int argc, char **argv){
	int n,tid;
	omp_set_num_threads(5);
	#pragma omp parallel private (tid, n)
	{
		tid = omp_get_thread_num();
		for(n=0;n<10;n++){
			printf("Hola mundo %d \n",tid);
		}
	}
	return(0);
}

//Programa 2
/*#include <stdio.h>
int main(int argc, char **argv){
	int n,tid;
	omp_set_num_threads(5);
	#pragma omp parallel private (tid,n)
	{
		tid = omp_get_thread_num();
		#pragma omp for
			for(n=0;n<10;n++){
				printf("Hola mundo %d \n",tid);
			}
	}
	return(0);
}*/