#include <stdio.h>
#include <signal.h>
#include <unistd.h>


void tratar_alarma(int)
{
	printf("Alarma activada \n");
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
	sigaddset(&mask, SIGQUIT);
	sigprocmask(SIG_SETMASK, &mask, NULL);
	sigaction(SIGALRM, &act, NULL);
	for (;;)
	{
		alarm(3); /*Se arma el temporizador*/
		pause(); /*Se suspende el proceso hasta que se reciba la senial*/
	}
}