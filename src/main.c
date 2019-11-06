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
    while(j<4){
        printf("Entrei Coluna=%d\n",idTrail);
        pthread_mutex_lock(&acesso[j][idTrail]);
        if(idTrail==0) matrix[j][idTrail] = 9;
        else matrix[j][idTrail] = idTrail;
        pthread_mutex_unlock(&acesso[j][idTrail]);
        j++;
        printf("estou no loop final j=%d\n",j);
        //if(j==4) j=0;
    }
    pthread_mutex_lock(&somaThreads);
    CountThreads+=1;
    pthread_mutex_unlock(&somaThreads);
    //sleep(1);
    printf("Incrementei o count = %d\n",CountThreads);
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
}
int main(){
    int * id;
    pthread_t trails[4];
    //pthread_t player;
    //pthread_t screen;
    for(int i=0;i<3;i++){
        for(int j=0;j<3;j++){
            pthread_mutex_init(&acesso[i][j],0);
        }
    }
    pthread_mutex_init(&somaThreads,0);
    for(int i=0;i<4;i++){
        for(int j=0;j<4;j++){
            matrix[i][j]=0;
        }
    }
    for(int i=0;i<4;i++){
        id = (int *)malloc(sizeof(int));
        *id = i;
        pthread_create(&trails[i],NULL,trail,(void *) id);
        printf("Criei a thread=%d\n",i);
    }
    printf("Creie todas as threads\n");
    //id = (int *)malloc(sizeof(int));
    //*id =99;
    //pthread_create(&player,NULL,car,(void *)id);
    //pthread_create(&screen,NULL,&printMatrix,NULL);
    while(CountThreads<3){}
    for(int i=0;i<4;i++){
        pthread_join((pthread_t)&trails[i],NULL);
    }
    for(int i=0;i<4;i++){
        for(int j=0;j<4;j++){
            pthread_mutex_destroy(&acesso[i][j]);
        }
    }
    pthread_mutex_destroy(&somaThreads);
    //pthread_join((pthread_t)&player,NULL);
    printMatrix();
    //pthread_join(&screen,NULL);

    return 0;
}