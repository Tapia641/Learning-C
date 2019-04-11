#include <sys/types.h>
#include <sys/wait.h>
#include <signal.h>
#include <stdio.h>
#include <unistd.h>
#include <stdlib.h>

pid_t pid;

int main(int argc, char const *argv[])
{
	struct sigaction act;
	sigset_t mask;
	/*Especifica el manejador*/
	act.sa_flags = 0; // Ninguna accion especifica

	int pid, status, salida;
	char comando[100] = "";
	/*Se cre el proceso hijo*/
	pid = fork();
	switch(pid)
	{
		case -1:
			exit(-1);
		case 0:
		/*El proceso hijo ejecuta el comando solicitado*/		
			sprintf(comando,argv[1],getenv("USER"));
			salida = system(comando);
			//sleep(6);
		default:
		/*Establece el manejador*/
			if (wait(&status) >=5 )
			{
				kill(pid,SIGKILL);
			}
		/*Espera al proceso hijo*/
			wait(&status); /*Vease con man para mas detalles sobre wait*/
	}
	exit(0);
	return 0;
}