#include <pthread.h>
#include <stdio.h>
#include <unistd.h>
#include <stdlib.h>
#define MAX_HILOS 10

void funcion(){
	printf("Hilo %lu\n", pthread_self());
	sleep(3);
	pthread_exit(NULL);
}

void main(){
	int i;
	pthread_attr_t atributos;
	pthread_t thid[MAX_HILOS];

	/*Se inicializan los atributos como independientes*/
	pthread_attr_init(&atributos);
	pthread_attr_setdetachstate(&atributos, PTHREAD_CREATE_DETACHED);

	for (i = 0; i<MAX_HILOS; i++){
		pthread_create(&thid[i], &atributos, (void*)funcion, NULL);
		/*El hilo principal se supende 6 segundos, para esperar a que los hilos hijos terminen.
		De lo contrario al terminar el proceso principal, tambien todos su hijos terminarian*/
		sleep(6);
	}
}