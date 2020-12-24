#include <stdio.h>
#include <stdlib.h>
#include <pthread.h>
#include<semaphore.h>
#include <unistd.h>
#define N 20
	int contPostIt=0;
	int TAM;  // numero de usuarios
	sem_t semaforo1 ;  //declarando os semaforos
	sem_t semaforo2 ;
	

void dorme_aleatorio(){
	printf("dormindo... \n");
	sleep((rand() % 3)+1);
}

void colaPostIt(){

	printf("Colando um PostIt: \n"); 
	
}

void leva_mochila_ate_B_e_volta(){
	printf("\n");
	printf(" ...O pombo esta levando a mochila ate B... \n");
	printf("\n");
	sleep((rand() % 3)+1); 	
}



static void * usuario() { 		
 
 	while(1){
 		
 	dorme_aleatorio();
	 	
 	sem_wait(&semaforo1);
 	colaPostIt();
 	contPostIt++;
	sem_post(&semaforo1);

 		if (contPostIt == N){
 				printf("\n");
				printf(">>> mochila cheia <<<\n");
				printf("\n");
				sem_post(&semaforo2);
 				sem_wait(&semaforo1);
			 }
 				
 	}	
 	
} 

static void * pombo () {

	 while(1){
	 	
		sem_wait(&semaforo2);
		printf("Ei pombo, acorda!! \n");
		leva_mochila_ate_B_e_volta();
 		contPostIt = 0;
 		
		int i;
 		for (i=0; i<N; i++){	
		 	
 			printf("Adic. msg %d\n", i);
 		}
 			printf("\n");
 			printf("...O pombo voltou para A...\n");		
 			printf("\n");
 			sem_post(&semaforo1);
 	}	
 		pthread_exit(NULL);
 	  				
} 

int main(int argc, char *argv[]) {

		printf("Numero de usuarios: ");
		scanf("%d",&TAM);
		printf("\n");
		int j;
		sem_init(&semaforo1,0,1);	// iniciando os semaforos de controle
		sem_init(&semaforo2,0,0);

	
		pthread_t thPombo;
		pthread_t thUsuario[TAM];
			
		for (j=0 ; j<TAM ; j++){		// criando o grupo de trheads usuario
			pthread_create (&thUsuario[j] , NULL , *usuario , NULL);
		}
		pthread_create (&thPombo , NULL , *pombo , NULL);
		
		pthread_join(thPombo, NULL);       // terminando por inteiro a thread
		for (j=0 ; j<TAM ; j++){
			pthread_join(thUsuario[j], NULL);
		}
	    

	return 0;
}
