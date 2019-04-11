#include <sys/types.h>
#include <unistd.h>
#include <stdlib.h>
#include <stdio.h>
#include <string.h>
#include <stdio.h>
int main(){
	int bytes_enviados, bytes_enviados2, bytes_leidos,bytes_leidos2, i, descriptor_archivo[2],descriptor_archivo2[2];
	char buffer[BUFSIZ+1], buffer2[BUFSIZ+1];
	pid_t pid;
	if (pipe(descriptor_archivo) == 0){
		pid = fork();
		if (pid == -1){
			perror("Error al ejecutar fork");
			exit(-1);
		}
		if (pid == 0){//proceso hijo
			//Obtine
			for (i = 0; i < 27; i++){
				memset(buffer, '\0', sizeof(buffer));
				bytes_leidos = read(descriptor_archivo[0], buffer, BUFSIZ);
				printf("El proceso hijo ha leido %d bytes y el contenido es: %s\n", bytes_leidos, buffer);
			}
			exit(0);
		}else{//proceso padre
			//Envia

			for (i = 65; i < 91; i++){
				bytes_enviados = write(descriptor_archivo[1], (char*) &i, sizeof(char));
				printf("El proceso padre ha enviado por la tuberia %d bytes\n",bytes_enviados);
				sleep(1);
			}
		}
	}
	if (pipe(descriptor_archivo2) == 0){
		pid = fork();
		if (pid == -1){
			perror("Error al ejecutar fork");
			exit(-1);
		}
		if (pid == 0){//proceso hijo

			//Envia
			for (i = 97; i < 123; i++){
				bytes_enviados2 = write(descriptor_archivo2[1], (char*) &i, sizeof(char));
				printf("El proceso hijo ha enviado por la tuberia %d bytes\n", bytes_enviados2);
				sleep(1);
			}
		}else{//proceso padre

			//Obtiene
			for (i = 0; i < 27; i++){
				memset(buffer2, '\0', sizeof(buffer2));
				bytes_leidos2 = read(descriptor_archivo2[0], buffer2, BUFSIZ);
				printf("El proceso padre ha leido %d bytes y el contenido es: %s\n", bytes_leidos2, buffer2);
			}
			exit(0);
		}
	}
exit(0);
}
