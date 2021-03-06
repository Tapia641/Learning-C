#include <stdio.h>
#include <signal.h>
#include <unistd.h>
#include <stdlib.h>

void tratar_alarma(int sig)
{
	if (sig == 20 || sig == 18 ||sig == 24)
	{
		printf("Me han intentado detener\n");
	}
	printf("Alarma activada \n");
	printf("%d\n", sig);
}

int main(void)
{
	struct sigaction act;
	sigset_t mask;

	/*Especifica el manejador*/
	act.sa_handler = tratar_alarma; // Funcion a ejecutar
	act.sa_flags = 0; // Ninguna accion especifica

	/*Se bloquea la senial 3 SIGQUIT*/
	sigemptyset(&mask);

	sigaddset(&mask, SIGQUIT);//Aniadimos a la lista que evita
	//sigaddset(&mask, SIGTSTP);//Aniadimos a la lista que evita

	sigprocmask(SIG_SETMASK, &mask, NULL);
	sigaction(SIGALRM, &act, NULL);
	sigaction(SIGTSTP,&act,NULL);
	for (;;)
	{
		//Alarma para que se active, 1000000 microsegundos = 1 seg
		//Entonces 500000 microseg = .5 seg
		ualarm(500000,0); /*Se arma el temporizador*/
		pause(); /*Se suspende el proceso hasta que se reciba la senial*/
	}
}