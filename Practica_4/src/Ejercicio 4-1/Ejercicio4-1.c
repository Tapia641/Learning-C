#include <stdio.h>
#include <sys/types.h>
#include <sys/wait.h>
#include <unistd.h>
#include <stdlib.h>

int main(){
	pid_t  pid;
	int i = 0, estado;
	pid = fork();
	if (pid == -1){ //error del fork
			perror("Error en el fork");
//			break;
	}else if (pid == 0){ //proceso hijo
			printf("Soy el hijo: PID %d; PPID = %d i = %d\n", getpid(), getppid(),  ++i);
			exit(0);
//			break;
	}else{ //proceso padre
			printf("Soy el padre: PID %d; PPID = %d i =  %d\n", getpid(), getppid(), --i);
			wait(&estado);
	}

}
