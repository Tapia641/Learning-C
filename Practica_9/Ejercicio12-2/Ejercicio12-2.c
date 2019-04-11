#include <stdio.h>
#include <stdlib.h>
#include <pthread.h>
#include <unistd.h>

struct fraccion
{
	float num;
	float dem;
}f1;

float res(struct fraccion *f){
	return (f->num)/(f->dem);
}

void Hilo1(struct fraccion *f){
	printf("La fracion en decimal de %d/%d es %f\n", (int)f->num, (int)f->dem,res(f));
}

int main(int argc, char *argv[])
{
	//Crear hilos
	pthread_t proceso1;
	struct fraccion *f;
	f->num = 1;//Inicializamos valores a la estructura
	f->dem = 8;
	pthread_create(&proceso1, NULL, (void*)Hilo1, f);

	//Espera a que los hilos terminen
	pthread_join(proceso1, NULL);

	exit(0);
}

