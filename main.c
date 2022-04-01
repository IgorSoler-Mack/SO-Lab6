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
          printf("UM FILOSOFO %d esperando garfo %d\n", filosofo, filosofo);
          sem_wait(&sem_vetor[filosofo]);
          printf("FILOSOFO %d PEGOU O GARFO %d\n", filosofo, filosofo);
          if (filosofo-1 < 0){
              printf("UM FILOSOFO %d esperando garfo %d\n", filosofo, 5);
              sem_wait(&sem_vetor[5]);
              printf("FILOSOFO %d PEGOU O GARFO %d\n", filosofo, 5);

          } else {
              printf("UM FILOSOFO %d esperando garfo %d\n", filosofo, filosofo-1);
              sem_wait(&sem_vetor[5]);
              printf("FILOSOFO %d PEGOU O GARFO %d\n", filosofo, filosofo-1);

          }
          printf("FILOSOFO %d soltou os garfos\n", filosofo);
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
