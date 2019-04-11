/*Este programa muestra la sincronizacion en la impresion de dos hilos*/
#include <stdio.h>
#include <stdlib.h>
#include <pthread.h>
#include <semaphore.h>
int i = 10; // Variable compartida
sem_t mutex1;
sem_t mutex2;


void Hilo1(void){
	while(i>0){
		sem_wait(&mutex1);
		printf("Soy el hilo 1 (%lu) y esta es la impresion %d\n", pthread_self(), i--);
		sem_post(&mutex2);
	}
		pthread_exit(0);
}
void Hilo2(void){
	while(i>0){
		sem_wait(&mutex2);
		printf("Soy el hilo 2 (%lu) y esta es la impresion %d\n", pthread_self(), i--);
		sem_post(&mutex1);
	}
		pthread_exit(0);
}

int main(void)
{
	pthread_t th1, th2;

	//Inicializa los semaforos
	sem_init(&mutex1, 0 ,1);
	sem_init(&mutex2, 0 ,0);

	//Crear hilos
	pthread_create(&th1, NULL, (void*)Hilo1, NULL);
	pthread_create(&th2, NULL, (void*)Hilo2, NULL);

	//Espera a que los hilos terminen
	pthread_join(th1, NULL);
	pthread_join(th2, NULL);

	exit(0);
}

