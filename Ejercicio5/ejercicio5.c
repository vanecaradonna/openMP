/*Ejercicio 5: Suma de arreglos*/
/*
	Realice un programa OpenMP que realice la suma de dos arreglos componente a
	componente y deje el resultado en un nuevo arreglo. Ejecute el programa variando
	el número de threads.
*/
#include <omp.h>
#include <stdio.h>
#include <stdio.h>

int main(int argc, char **argv){
	int n, cantidad, posiciones;
	
	printf("Ingrese la cantidad de hilos:\n");
	scanf("%d",&cantidad);
	
	printf("Ingrese la cantidad de posiciones para los arreglos:\n");
	scanf("%d",&posiciones);

	int a[posiciones], b[posiciones], c[posiciones];

	omp_set_num_threads(cantidad);
	#pragma omp parallel private (n)
	{
		/*Inicializar arreglos*/
		#pragma omp for
			for(n=0;n<posiciones;n++){
				a[n]= n;
				b[n]= n;
				c[n]=0;
			}
		/*Sumar los dos arreglos*/
		#pragma omp for
			for(n=0;n<posiciones;n++){
				c[n]=a[n]+b[n];
				printf("proceso %d iteracion %d: %d + %d = %d \n",omp_get_thread_num(), n, a[n], b[n],c[n]);
			}
	}
	return(0);
}






