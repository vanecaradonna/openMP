/*Ejercicio 6*/
/*
Multiplicación de matrices
Realice un programa OpenMP que realice la multiplicación de matrices.
*/

#include <omp.h>
#include <stdio.h>

int main(int argc, char **argv){
	int indice_filas, indice_columnas, indice_multiplicacion, cantidad_hilos, filas_a, filas_b, filas_c, columnas_c, columnas_a, columnas_b;
	
	/*Ingreso los datos*/
	printf("Ingrese la cantidad de hilos:\n");
	scanf("%d",&cantidad_hilos);
	
	printf("Ingrese la cantidad de filas para la primera matriz:\n");
	scanf("%d",&filas_a);

	printf("Ingrese la cantidad de columnas para la primera matriz:\n");
	scanf("%d",&columnas_a);

	filas_b = columnas_a; /*para podes realizar la multiplicacion deben ser iguales*/
	printf("Ingrese la cantidad de columnas para la segunda matriz:\n");
	scanf("%d",&columnas_b);

	filas_c=filas_a;
	columnas_c=columnas_b;

	/*Creo las matrices*/
	int a[filas_a][columnas_a] , b[filas_b][columnas_b], c[filas_c][columnas_c];

	omp_set_num_threads(cantidad_hilos);
	#pragma omp parallel private (indice_filas, indice_columnas)
	{
		/*Inicializar matrices*/
		/*A*/
		for(indice_filas=0;indice_filas<filas_a;indice_filas++){
			#pragma omp for
				for(indice_columnas=0;indice_columnas<columnas_a;indice_columnas++){
					a[indice_filas][indice_columnas]= ((indice_filas+1)*columnas_a)-(columnas_a-(indice_columnas+1));
					//printf("hilo %d:  a[%d][%d]= %d\n", omp_get_thread_num() ,indice_filas, indice_columnas, a[indice_filas][indice_columnas] );
				}
		}

		/*b*/
		for(indice_filas=0;indice_filas<filas_b;indice_filas++){
			#pragma omp for
				for(indice_columnas=0;indice_columnas<columnas_b;indice_columnas++){
					b[indice_filas][indice_columnas]= ((indice_filas+1)*columnas_b)-(columnas_b-(indice_columnas+1));
					//printf("hilo %d:  b[%d][%d]= %d\n", omp_get_thread_num() ,indice_filas, indice_columnas, b[indice_filas][indice_columnas] );
				}
		}

		/*c*/
		for(indice_filas=0;indice_filas<filas_c;indice_filas++){
			#pragma omp for
				for(indice_columnas=0;indice_columnas<columnas_c;indice_columnas++){
					c[indice_filas][indice_columnas]= 0;
					//printf("hilo %d:  b[%d][%d]= %d\n", omp_get_thread_num() ,indice_filas, indice_columnas, b[indice_filas][indice_columnas] );
				}
		}

		/*Multiplicacion de matrices*/
		#pragma omp for collapse(2) private (indice_multiplicacion, indice_columnas)
		for(indice_filas=0;indice_filas<filas_a;indice_filas++){
			for(indice_columnas=0;indice_columnas<columnas_b;indice_columnas++){
				for (indice_multiplicacion=0; indice_multiplicacion<filas_b; indice_multiplicacion++){ //cloumnas_a = filas_b	
					c[indice_filas][indice_columnas]= c[indice_filas][indice_columnas]+(a[indice_filas][indice_multiplicacion]*b[indice_multiplicacion][indice_columnas]);
					//printf("hilo %d:  b[%d][%d]= %d\n", omp_get_thread_num() ,indice_filas, indice_columnas, b[indice_filas][indice_columnas] );
				} 
				printf("hilo %d:  c[%d][%d]= %d\n", omp_get_thread_num() ,indice_filas, indice_columnas, c[indice_filas][indice_columnas] );	
			}
		}

		
					

		/*Sumar los dos arreglos
		#pragma omp for
			for(n=0;n<posiciones;n++){
				c[n]=a[n]+b[n];
				printf("proceso %d iteracion %d: %d + %d = %d \n",omp_get_thread_num(), n, a[n], b[n],c[n]);
			}
		*/
	}
	return(0);
}