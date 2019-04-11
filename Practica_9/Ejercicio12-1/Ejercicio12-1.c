#include <stdio.h>
#include <stdlib.h>
#include <pthread.h>
#include <unistd.h>

int i = 0, seconds; // Variable compartida

void Hilo1(void){
	for (int j = 0; j < seconds; j++){
		i++;
		//printf("%d\n",i);
		sleep(1);
	}
}
void Hilo2(void){
	for (int j = 0; j < seconds; j++){
		i--;
		//printf("%d\n",i);		
		sleep(1);
	}
}

int main(int argc, char *argv[])
{
	if (argc == 1)
	{
		printf("Debes ingresar el numero de segundos...\n");
		exit(0);
	}

	//Crear hilos
	pthread_t proceso1, proceso2;
	seconds = (int)*argv[1]-'0';//Recibimor parametros de la linea de comandos
	pthread_create(&proceso1, NULL, (void*)Hilo1, NULL);
	pthread_create(&proceso2, NULL, (void*)Hilo2, NULL);

	//Espera a que los hilos terminen
	pthread_join(proceso1, NULL);
	pthread_join(proceso2, NULL);

	printf("El valor final de la variable i es : %d\n", i);
	exit(0);
}

