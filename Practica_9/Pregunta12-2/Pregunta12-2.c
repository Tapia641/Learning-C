#include <stdio.h>
#include <stdlib.h>
#include <pthread.h>
#include <unistd.h>


void Hilo1(int i){
	while(1){
		printf("Soy el hilo 1 (%lu) y el valor de i = %d\n", pthread_self(), i++);
		sleep(1);
	}
}
void Hilo2(int i){
	while(1){
		printf("Soy el hilo 2 (%lu) y el valor de i = %d\n", pthread_self(), i--);
		sleep(1);
	}
}

int main(void)
{
	pthread_t proceso1, proceso2;
	int i = 0; // Variable compartida

	//Crear hilos
	pthread_create(&proceso1, NULL, (void*)Hilo1, NULL);
	pthread_create(&proceso2, NULL, (void*)Hilo2, NULL);

	//Espera a que los hilos terminen
	pthread_join(proceso1, NULL);
	pthread_join(proceso2, NULL);

	exit(0);
}

