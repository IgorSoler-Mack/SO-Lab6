#include <stdio.h>		// Header de Entrada e Sa�da, como printf
#include <sys/types.h>	// Defini��es de tipos de dados, como pid_t
#include <unistd.h>		// Define fun��es como pipe() e fork()
#include <sys/wait.h>	// Define fun��es de espera como wait()	
#include <stdlib.h>		// Define fun��es gerais como exit()
#include <semaphore.h>  // Define fun��es e tipos para cria��o de semaforos

// n = Numero de processos
void init_filosofo(int n){
	int i=0;
	int status=0;

	printf("Creating %d children\n", n);
	for(i=0;i<n;i++){	// Gera n processos filhos do processo principal
		pid_t pid=fork();
		if (pid==0){ 	// Apenas child chegam nesta Parte
			printf("%d\n", i);
			exit(0);	// Finaliza o processo
		}
	}
	// Apenas Parent Chega nesta Parte
	while(wait(NULL) > 0); // Aguarda at� que todos os processos tenham acabado
	printf("teste\n");
}


int main(int argc, char **argv){
	int num;
	
	printf(" Quantidade de Filosofos\n");
	printf(" ->");
	scanf("%d", &num);
	init_filosofo(num);

	return 0;
}
