#include <stdio.h>
#include <stdlib.h>
#include <pthread.h>
#include <unistd.h>

int matrix[4][4]; 
pthread_mutex_t  acesso[4][4];
void * trail(void * id){
    int j=0;
    int * numtrail = (int *) id;
    int idTrail = * numtrail ;//+ 100;
    while(1){
        pthread_mutex_lock(&acesso[j][*numtrail]);
        //sleep(*numtrail);
        if(j==0){
            matrix[j][*numtrail] = idTrail;
        }else{
            matrix[j][*numtrail] = 0;
           matrix[j+1][*numtrail] = idTrail;
        }
        pthread_mutex_unlock(&acesso[j][*numtrail]);
        j++;
        if(j==4) j=0;
    }
    
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