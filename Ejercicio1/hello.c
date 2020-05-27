/**Ejercicio 1**/
/*EJERCICIO 1: Hello World!!!
Desarrollar un Programa OpenMp denominado “Hola” que declare una región paralela
y dentro de la misma cada thread en ejecución imprima por pantalla “Hola Mundo
Desde El Thread (Numero thread)”. Ejecutar variando el número de threads.*/

#include <omp.h>
#include <stdio.h>

int main()
{
	int cantidad;
	printf("Ingrese la cantidad de hilos:\n");
	scanf("%d",&cantidad);

	omp_set_num_threads(cantidad);
	#pragma omp parallel
	{
		printf("hola mundo desde el Thread %d\n", omp_get_thread_num());
	}

	return 0;
}
