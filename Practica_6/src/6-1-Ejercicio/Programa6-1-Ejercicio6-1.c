#include <stdio.h>
#include <stdlib.h>
#include <sys/types.h>
#include <sys/ipc.h>
#include <sys/shm.h>

int main(int argc, char const *argv[])
{
	int shmid, *variable;
	key_t llave;
	llave = ftok(argv[0],'K');
	if ((shmid = shmget(llave, sizeof(int), IPC_CREAT | 0600)) == -1)
	{
		perror("Error en shmget");
		exit(-1);
	}
	/*Nos atamos a la memoria compartida*/

	if ((variable = (int *) shmat(shmid, NULL, 0)) == (int *) (-1))
	{
		perror("Fallo shmat");
		exit(-1);
	}
	char pila[10] = {32,32,32,32,32,32,32,32,32,32};
	*variable = 100;
	char x;
	int i = 9, j = 65;
	printf("\nIntroduzca p para producir, c para consumir y v para visualizar, t para terminar\n");
	while(scanf("%c",&x) != EOF)
	{
		printf("\nIntroduzca p para producir, c para consumir y v para visualizar, t para terminar\n");
		switch(x)
		{
			case 'p': /*Productor*/
				pila[i] = j; i--; j++;
				printf("Producido con exito!\n");
				break;
			case 'c':/*Consumidor*/
				for (int k = 0; k < 10; ++k)
				{
					if(pila[k] != 32) {
						j = pila[k];
						pila[k] = 32;
						i = k;
						break;
					}
				}
				printf("Consumido con exito!\n");
				break;
			case 'v':/*Visualizar*/
				for (int i = 0; i < 10; i++){ printf("%c\n", pila[i]);}
				printf("Visualizado con exito!\n");
				break;
			case 't':/*Terminar*/
				shmctl(shmid, IPC_RMID, 0);
				exit(0);
				break;
			default:
				printf("Se introdujo una letra incorrecta\n");
				break;
		}
	}
	return 0;
}
