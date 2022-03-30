#include <stdio.h>		// Header de Entrada e Saída, como printf
#include <sys/types.h>	// Definições de tipos de dados, como pid_t
#include <sys/wait.h>	// Define funções de espera como wait()	
#include <stdlib.h>		// Define funções gerais como exit()
#include <semaphore.h>  // Define funções e tipos para criação de semaforos
#include <unistd.h>		// Define funções como pipe() e fork()
#include <time.h>		// Define funções que utilizam o tempo
#include <fcntl.h>           /* For O_* constants */



// n = Numero de processos
void init_filosofo(int n){
	printf("Gerando %d Filosofos\n", n);
	sem_t *sem_vetor = malloc(n * sizeof(sem_t)); 

	// Gera uma lista de N semáforos
	int i;
	char buf[12];
	for(i=0;i<n;i++){
		snprintf(buf,12,"Semaforo%d",i); //
		sem_t *sem = sem_open(buf, O_CREAT, 0644, 1);
		sem_post(sem);
	}


	for(i=0;i<n;i++){	// Gera n processos filhos do processo principal
		pid_t pid=fork();
		if (pid==0){ 	// Apenas child chegam nesta Parte
			char buf[12];
			snprintf(buf,12,"Semaforo%d",i);
			printf("%s\n", buf);
			sem_t *sem1 = sem_open(buf, 1);

			if( i-1 < 0) snprintf(buf,12,"Semaforo%d",n-1);
			else snprintf(buf,12,"Semaforo%d",i-1);
			printf("%s\n", buf);
			sem_t *sem2 = sem_open(buf, 1);
			/* INICIO DO CÓDIGO DO FILHO */
			while(1){
				srand(time(NULL));
				printf("Filosofo %d PENSANDO\n", i);
				sleep(rand() % 3);
				
				// Espera garfos estarem livres
				printf("Filosofo %d esperando garfo %d\n", i, i);
				sem_wait(sem1);
				printf("Filosofo %d pegou o garfo %d\n", i, i);

				printf("Filosofo %d esperando garfo %d\n", i, i-1);
				sem_wait(sem2);
            	printf("Filosofo %d pegou o garfo %d\n", i, i-1);

				printf("Filosofo %d COMENDO\n", i);
				sleep(rand() % 3);

				// Libera Garfos
				sem_post(sem1);
				sem_post(sem2);
				printf("Filosofo %d soltou os garfos\n", i);

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
