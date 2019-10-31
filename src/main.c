#include <stdio.h>
#include <stdlib.h>
#include <pthread.h>
#include <unistd.h>

int matrix[4][4]; 
pthread_mutex_t  acesso[4][4];

void * trail(void * id, void * numTrail){
    
}
void * car(void * id){

}
int main(){
    for(int i=0;i<4;i++){
        for(int j=-0;j<4;j++){
            matrix[i][j]=0;
        }
    }
    
    return 0;
}