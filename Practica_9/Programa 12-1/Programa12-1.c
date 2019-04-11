#include <pthread.h>
#include <stdio.h>
#include <stdlib.h>
#include <unistd.h>

void funcion(void)
{
printf("Hilo %lu \n", pthread_self());
sleep(2);
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
