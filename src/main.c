#include <stdio.h>
#include <stdlib.h>
#include <pthread.h>
#include <unistd.h>


void * trail(void *);
void printMatrix();
void * car(void *);

int matrix[4][4];
int CountThreads=0;

pthread_mutex_t  acesso[4][4];
pthread_mutex_t somaThreads;
void * trail(void * id){
    int j=0;
    int * numtrail = (int *) id;
    int idTrail = * numtrail ;
    printf("IdTrail = %d\n",idTrail);
    while(j<4){
        if(pthread_mutex_lock(&acesso[j][idTrail])){
            printf("Bloqueado\n");
        }
        if(idTrail==0) matrix[j][idTrail] = 9;
        else matrix[j][idTrail] = idTrail;
        if(pthread_mutex_unlock(&acesso[j][idTrail]))printf("Unlock error\n");
        j++;
        //if(j==4) j=0;
    }
    //sleep(1);
    pthread_mutex_lock(&somaThreads);
    CountThreads+=1;
    pthread_mutex_unlock(&somaThreads);
    printf("Incrementei o count = %d  e idTrail=%d\n",CountThreads,idTrail);
    sleep(1);
    pthread_exit(NULL);
    //return NULL;
}
void  printMatrix(){
    for(int i=0;i<4;i++){
        for(int j=0;j<4;j++){
            printf("%d  ",matrix[i][j]);
        }
        printf("\n");
    }
}
void * car(void * id){
    // thread do player
    return NULL;
}
int main(){
    int * id;
    pthread_t trails[4];
    //pthread_t player;
    //pthread_t screen;
      for(int i=0;i<4;i++){ // iniciando a matriz
        for(int j=0;j<4;j++){
            matrix[i][j]=0;
        }
    }
    for(int i=0;i<4;i++){ // iniciando os mutex
        for(int j=0;j<4;j++){
            pthread_mutex_init(&acesso[i][j],0);
        }
    }
    pthread_mutex_init(&somaThreads,0);

    for(int i=0;i<4;i++){ // criando as threads trails
        id = (int *)malloc(sizeof(int));
        *id = i;
        pthread_create(&trails[i],NULL,trail,(void *) id);
        //printf("Criei a thread=%d\n",i);
    }
    //printf("Creie todas as threads\n");
    //id = (int *)malloc(sizeof(int));
    //*id =99;
    //pthread_create(&player,NULL,car,(void *)id);
    //pthread_create(&screen,NULL,&printMatrix,NULL);
    while(CountThreads<3){} // loop de espera
    //printf("Dei join nas threads\n");
    for(int i=0;i<4;i++){
        for(int j=0;j<4;j++){
        pthread_mutex_destroy(&acesso[i][j]);
        }
    }
    //printf("Detruir os mutex\n");
    pthread_mutex_destroy(&somaThreads);
    //pthread_join((pthread_t)&player,NULL);
    printf("Cheguei no printMatrix\n");
    printMatrix();
    //pthread_join(&screen,NULL);
    return 0;
}