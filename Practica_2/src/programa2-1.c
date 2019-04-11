#include <stdio.h>
#include <stdlib.h>
#include <string.h>

int main(int argc, char *argv[]){
	int tokens;

	for(tokens = 0; tokens < argc; tokens++){
		if(argv[tokens][0] == '-') 
			printf("opcion: %s\n", argv[tokens]+1);
		else{
			printf("argumento: %d: %s, num: %d\n", tokens, argv[tokens], strlen(argv[tokens]));
		}
	}
	exit(0);
}
