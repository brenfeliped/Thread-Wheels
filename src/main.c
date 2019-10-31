#include <stdio.h>
#include <stdlib.h>
#include <pthread.h>
#include <unistd.h>

int matrix[4][4]; 
pthread_mutex_t  acesso[4][4];
int j=0;
void * trail(void * id){
    int * numtrail = (int *) id;
    int idTrail = * numtrail + 100;
    while(1){
        pthread_mutex_lock(&acesso[*numtrail][j]);
        sleep(*numtrail);
        matrix[*numtrail,j] = idTrail;
        pthread_mutex_unlock(&acesso[*numtrail][j]);
        j++;
        if(j==4) j=0;
    }
    
}

void * car(void * id){

}
int main(){
    int * id;
    pthread_t trails[4];
    pthread_t player;
    for(int i=0;i<4;i++){
        for(int j=0;j<4;j++){
            matrix[i][j]=0;
        }
    }
    for(int i=0;i<4;i++){
        id = (int *)malloc(sizeof(int));
        *id =i;
        pthread_create(&trails[i],NULL,trail,(void *) id);
    }
    id = (int *)malloc(sizeof(int));
    *id =99;
    phread_create(&player,NULL,car,(void *)id);
    return 0;
}