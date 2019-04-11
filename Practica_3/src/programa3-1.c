#include <sys/types.h>
#include <stdio.h>
#include <unistd.h>

int main(int argc, char **argv){
	printf("Identificador de usuario: %d\n", getuid());
	return 0;
}
