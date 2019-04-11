#include <stdio.h>
#include <pthread.h>
#include <stdlib.h>
#include <unistd.h>

void Nieto(void * data){
	char *texto =(char*)data;
	printf("%s\n", texto);
	sleep(3);
}

void Hijo(void * data){
	char *texto =(char*)data;
	printf("%s\n", texto);
	pthread_t proceso2;
	pthread_create(&proceso2, NULL, (void*)Nieto, "Hola soy un hilo nieto");
	pthread_join(proceso2, NULL);
	printf("Termino el nieto\n");
}

int main(void){
	pthread_t proceso1;
	/*Se crean dos hilos con atributos predeterminados */
	pthread_create(&proceso1, NULL, (void*)Hijo, "Hola soy un hilo hijo");
	/*Se espera su terminacion*/
	pthread_join(proceso1, NULL);
	printf("Termino el hijo\n");
	return 0;

}