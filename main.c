#include <stdio.h>		// Header de Entrada e Saída, como printf
#include <sys/types.h>	// Definições de tipos de dados, como pid_t
#include <sys/wait.h>	// Define funções de espera como wait()	
#include <stdlib.h>		// Define funções gerais como exit()
#include <semaphore.h>  // Define funções e tipos para criação de semaforos
#include <unistd.h>		// Define funções como pipe() e fork()
#include <time.h>		// Define funções que utilizam o tempo



// n = Numero de processos
void init_filosofo(int n){
	printf("Gerando %d Filosofos\n", n);
	sem_t *sem_vetor = malloc(n * sizeof(sem_t)); 

	// Gera uma lista de N semáforos
	int i;
	for(i=0;i<n;i++){
		sem_init(&sem_vetor[i], 0, 1);
	}


	for(i=0;i<n;i++){	// Gera n processos filhos do processo principal
		pid_t pid=fork();
		if (pid==0){ 	// Apenas child chegam nesta Parte
			/* INICIO DO CÓDIGO DO FILHO */
			while(1){
				srand(time(0)+i);
				printf("Filosofo %d PENSANDO\n", i);
				
				// Espera garfos estarem livres
				sem_wait(&sem_vetor[i]);
				if( i-1 < 0) sem_wait(&sem_vetor[n-1]);
				else sem_wait(&sem_vetor[i-1]);

				printf("Filosofo %d COMENDO\n", i);
				sleep(3);

				// Libera Garfos
				sem_post(&sem_vetor[i]);
				if( i-1 < 0) sem_post(&sem_vetor[n-1]);
				else sem_post(&sem_vetor[i-1]);
			}
			/*  FIM DO CÓDIGO DO FILHO  */
			exit(0);	// Finaliza o processo
		}
	}
	// Apenas Parent Chega nesta Parte
	while(wait(NULL) > 0); // Aguarda até que todos os processos tenham acabado
	free(sem_vetor);
}

int main(int argc, char **argv){
	int num;

	printf(" Quantidade de Filosofos\n");
	printf(" ->");
	scanf("%d", &num);

	printf("\n");

	init_filosofo(num); // Gera N Filosofos, cada um sendo um unico processo

	return 0;
}
