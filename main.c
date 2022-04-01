#include <stdio.h>
#include <string.h>
#include <sys/wait.h>    // Define funções de espera como wait()    
#include <semaphore.h>  // Define funções e tipos para criação de semaforos
#include <pthread.h>
#include<stdlib.h>
#include<unistd.h>
#include <time.h>        // Define funções que utilizam o tempo


// Global variable:
sem_t sem_vetor[5];
int i;

void* jantarFilosofos(void* f){
    srand(time(NULL));
      int filosofo = *(int *) f; 
      while(1){
          sleep(rand()%8);
          printf("UM FILOSOFO %d ESPERANDO GARFO %d\n", filosofo, filosofo);
          sem_wait(&sem_vetor[filosofo]);
          printf("FILOSOFO %d PEGOU O GARFO %d\n", filosofo, filosofo);
          if (filosofo-1 < 0){
              printf("UM FILOSOFO %d ESPERANDO GARFO %d\n", filosofo, 5);
              if (sem_trywait(&sem_vetor[5]) != -1){
              	printf("FILOSOFO %d PEGOU O GARFO %d\n", filosofo, 5);
              	printf("FILOSOFO %d COMEU E SOLTOU OS GARFOS\n", filosofo);

			  }
	          else {
	          	printf("FILOSOFO %d LARGOU PRIMEIRO GARFO %d (PENSANDO) \n", filosofo, 5);
	          	sem_post(&sem_vetor[5]);
	          	continue;
			  }
          } else {
              printf("UM FILOSOFO %d ESPERANDO GARFO %d\n", filosofo, filosofo-1);
              if (sem_trywait(&sem_vetor[5]) != -1){
              	printf("FILOSOFO %d PEGOU O GARFO %d\n", filosofo, filosofo-1);
              	printf("FILOSOFO %d COMEU E SOLTOU OS GARFOS\n", filosofo);

			  }
	          else {
	          	printf("FILOSOFO %d LARGOU O PRIMEIRO GARFO %d (PENSANDO) \n", filosofo, filosofo-1);
	          	sem_post(&sem_vetor[filosofo-1]);
	          	continue;
			  }

          }
          sem_post(&sem_vetor[filosofo]);

          if (filosofo-1 < 0 ) {
            sem_post(&sem_vetor[5]);
          } else {
              sem_post(&sem_vetor[filosofo-1]);
          }
          sleep(2);
    }
}


int main(void){
      printf("Gerando 5 Filosofos\n");
    for(i = 0;i<5;i++){
        sem_init(&sem_vetor[i], 0, 1);
    }

      pthread_t tid[5];

      for(i = 0; i < 5; i++){
          pthread_create(&tid[i], NULL, jantarFilosofos, &i);
    }
    int* ptr;

    for(i = 0; i < 5; i++){
      pthread_join(tid[i], (void**)&ptr);
    }
}
