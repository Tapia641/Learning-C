#include <sys/types.h>
#include <stdio.h>
#include <unistd.h>

int main(){
	pid_t pid;
	int j,cont=0;

	for(j = 0; j < 10; j++){
		pid = fork();
		if(pid ==0) break;
	}
	printf("El padre del proceso %d es %d, j = %d\n", getpid(), getppid(), j);
	sleep(3);
	return 0;
}
