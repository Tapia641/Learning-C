/*Programa para ilustrar el uso de semaforos*/
#include <stdio.h>
#include <stdlib.h>
#include <unistd.h>
#include <sys/types.h>
#include <sys/ipc.h>
#include <sys/sem.h>


#define SEMAFORO_PADRE 1
#define SEMAFORO_HIJO 0

int main(int argc, char const *argv[])
{
	int semid, pid, j = 10;
	struct sembuf operacion;
	//printf("%u\n", operacion.sem_num);
	//printf("%u\n", operacion.sem_op);
	//printf("%u\n", operacion.sem_flg);

	key_t llave;
	llave = ftok(argv[0], 'U');

	if ((semid = semget(llave,2,IPC_CREAT | 0600)) == -1)
	{
		perror("Error al ejecutar segmet");
		exit(-1);
	}
	semctl (semid, SEMAFORO_HIJO, SETVAL, 0);
	semctl (semid, SEMAFORO_PADRE, SETVAL, 1);

	/*Se cre el proceso hijo*/
	if ((pid = fork()) == -1)
	{
		perror("Error al ejecutar fork");
		exit(-1);
	}
	else if (pid == 0)
	{
		/*Codigo correspondiente al proceso hijo*/
		while(j)
		{
			/*Se realiza la operacion DOWN en el semaforo del proceso hijo*/
			operacion.sem_flg = 0;
			operacion.sem_op = 1;
			operacion.sem_num = SEMAFORO_HIJO;
			//printf("%u\n", operacion.sem_num);
			//printf("%u\n", operacion.sem_op);
			semop(semid, &operacion,1);
			printf("SOY EL PROCESO HIJO. IMPRESION: %d\n", j--);
			/*Se realiza la operacion UP en el semaforo del proceso padre*/
			operacion.sem_op = 1;
			operacion.sem_num = SEMAFORO_PADRE;
			semop(semid,&operacion,1);
		}
		/*Borramos el semaforo*/
		semctl(semid,0,IPC_RMID,0);
	}else
	{
		/*Codigo correspondiente al proceso padre*/
				while(j)
		{
			/*Se realiza la operacion DOWN en el semaforo del proceso padre*/
			operacion.sem_flg = 0;
			operacion.sem_op = 1;
			operacion.sem_num = SEMAFORO_PADRE;
			//printf("%u\n", operacion.sem_num);
			//printf("%u\n", operacion.sem_op);
			semop(semid, &operacion,1);
			printf("SOY EL PROCESO PADRE. IMPRESION: %d\n", j--);
			/*Se realiza la operacion UP en el semaforo del proceso hijo*/
			operacion.sem_op = 1;
			operacion.sem_num = SEMAFORO_HIJO;
			semop(semid,&operacion,1);
		}
		/*Borramos el semaforo*/
		semctl(semid,0,IPC_RMID,0);

	}
	return 0;
}	
