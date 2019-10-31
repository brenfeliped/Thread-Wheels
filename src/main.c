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
        //sleep(*numtrail);
        if(j==0){
            matrix[*numtrail][j] = idTrail;
        }else{
            matrix[*numtrail][j] = 0;
            matrix[*numtrail][j+1] = idTrail;
        }
        pthread_mutex_unlock(&acesso[*numtrail][j]);
        j++;
        if(j==4) j=0;
    }
    
}
void  printMatrix(){
    for(int i=0;i<4;i++){
        for(int j=0;j<4;j++){
            printf("%d ",matrix[i][j]);
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
    pthread_t player;
    pthread_t screen;
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
    pthread_create(&player,NULL,car,(void *)id);
    //pthread_create(&screen,NULL,&printMatrix,NULL);
    printMatrix();
    for(int i=0;i<4;i++){
        pthread_join(&trails[i],NULL);
    }
    pthread_join(&player,NULL);
    printMatrix();
    //pthread_join(&screen,NULL);
    return 0;
}