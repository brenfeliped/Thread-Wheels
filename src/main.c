#include <stdio.h>
#include <stdlib.h>
#include <pthread.h>
#include <unistd.h>


void * trail(void *);
void printMatrix();
void * car(void *);

char matrix[4][4];
int CountThreads=0;

pthread_mutex_t  acesso[4][4];
pthread_mutex_t somaThreads;
void * trail(void * id){
    int j=0;
    int * numtrail = (int *) id;
    int idTrail = * numtrail ;
    //printf("IdTrail = %d\n",idTrail);
    while(1){
        pthread_mutex_lock(&acesso[j][idTrail]);
        matrix[j][idTrail] = idTrail;
        if(j==0){
            switch (idTrail){
            case 0:
                matrix[j][idTrail] = '!';
                break;
            case 1:
                matrix[j][idTrail] = '@';
                break;
            case 2:
                matrix[j][idTrail] = '&';
                break;
            default:
                matrix[j][idTrail] = '#';
                break;
            }
        }else{
            matrix[j-1][idTrail] = '0';
            switch (idTrail){
            case 0:
                matrix[j][idTrail] = '!';
                break;
            case 1:
                matrix[j][idTrail] = '@';
                break;
            case 2:
                matrix[j][idTrail] = '&';
                break;
            default:
                matrix[j][idTrail] = '#';
                break;
            }
        }
        pthread_mutex_unlock(&acesso[j][idTrail]);
        if(j==3)matrix[j][idTrail] = '0';
        j++;
        if(j==4) j=0;
        sleep(1);
    }
    //sleep(1);
    pthread_mutex_lock(&somaThreads);
    CountThreads+=1;
    pthread_mutex_unlock(&somaThreads);
    //printf("Incrementei o count = %d  e idTrail=%d\n",CountThreads,idTrail);
    //sleep(1);
    pthread_exit(NULL);
    //return NULL;
}
void  printMatrix(){
    for(int i=0;i<4;i++){
        for(int j=0;j<4;j++){
            printf("%c  ",matrix[i][j]);
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
    pthread_t player;
    //pthread_t screen;
      for(int i=0;i<4;i++){ // iniciando a matriz
        for(int j=0;j<4;j++){
            matrix[i][j]='0';
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
    }
    sleep(1);
    //pthread_create(&player,NULL,car,(void *)id);
    //pthread_create(&screen,NULL,&printMatrix,NULL);
    while(CountThreads<3){
        sleep(1);
        printMatrix();
        printf("\n");
    } // loop de espera
    for(int i=0;i<4;i++){
        for(int j=0;j<4;j++){
            pthread_mutex_destroy(&acesso[i][j]);
        }
    }
    //printf("Detruir os mutex\n");
    pthread_mutex_destroy(&somaThreads);
    //pthread_join((pthread_t)&player,NULL);
    //printf("Cheguei no printMatrix\n");
    sleep(1);
    printMatrix();
    //pthread_join(&screen,NULL);
    return 0;
}