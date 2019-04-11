#include <pthread.h>
#include <stdio.h>
#include <stdlib.h>
#include <unistd.h>

void funcion(void)
{
	/*Averigua su ID*/
	printf("Hilo %lu \n", pthread_self());
	//pthread_t th3;
	//pthread_create(&th3, NULL, (void *)funcion, NULL);
	sleep(2);

	/*Se finaliza el hilo*/
	pthread_exit(NULL);
}

int main(){
	pthread_t th1, th2;
	/*Se crean dos hilos con atributos predeterminados */
	pthread_create(&th1, NULL, (void *)funcion, NULL);
	pthread_create(&th2, NULL, (void *)funcion, NULL);
	printf("El hilo principal espera a sus hijos\n");


	/*Se espera su terminacion*/
	pthread_join(th1, NULL);
	pthread_join(th2, NULL);
	printf("El hilo principal termina\n");

	exit(0);
}
