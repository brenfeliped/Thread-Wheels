#include <stdio.h>
#include <stdlib.h>
#include <pthread.h>
#include <string.h>
#include <unistd.h>
#ifdef _WIN32
#define CLEAR "cls"
#else
#define CLEAR "clear"
#endif
#define RED  "\033[0;31m"
#define GREEN "\033[0;32m"
#define RESET "\033[0m"
#define YELLOW "\033[0;33m"
#define BLUE   "\033[0;34m"
#define MARGENTA "\033[0;35m"

void * trail(void *);
void printMatrix();
void * car(void *);

int lifes = 3;
int points=0;

char matrix[9][4];
int CountThreads=0;
pthread_mutex_t  acesso[9][4];
pthread_mutex_t somaThreads;
//Interface funtions
void  printEmptyTrail(){
    printf("|       |       |       |       |\n");
}
void scoreboard(){
    char lifeStr[4];
    switch (lifes){
    case 1:
        strcpy(lifeStr,"#");
        break;
    case 2:
        strcpy(lifeStr,"##");
        break;
    case 3:
        strcpy(lifeStr,"###");
        break;
    default:
        strcpy(lifeStr,"###");
        break;
    }
    printf("%s===================================%s\n",GREEN,RESET);
    printf("%s==Points:%d            Life:%s%s %s==\n",GREEN,points,RED,lifeStr,GREEN);
    printf("%s===================================%s\n",GREEN,RESET);
}
void screen(){
    system(CLEAR);
    scoreboard();
    for(int i=0;i<9;i++){
        for(int j=0;j<4;j++){
            printf("|");
            printf("    ");
            if(matrix[i][j]!='0'){
                if(matrix[i][j]!='@'){ // entao eh um inimigo
                    switch(j){
                    case 0:
                        printf("%s#%s   ",YELLOW,RESET);
                        break;
                    case 1:
                        printf("%s#%s   ",GREEN,RESET);
                        break;
                    case 2:
                        printf("%s#%s   ",BLUE,RESET);
                        break;
                    case 3:
                        printf("%s#%s   ",MARGENTA,RESET);
                        break;
                    default:
                        printf("%s#%s   ",MARGENTA,RESET);
                        break;
                    }
                }else{
                    printf("%s#%s   ",RED,RESET);
                }
            }else{
                printf("    ");
            }
            if(j==3) printf("|");
        }
        printf("\n");
    }
}
// end Interface funtions
void * trail(void * id){
    int j=0;
    int * numtrail = (int *) id;
    int idTrail = * numtrail;
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
                matrix[j][idTrail] = 'P';
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
                matrix[j][idTrail] = 'P';
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
        if(j==8)matrix[j][idTrail] = '0';
        j++;
        if(j==9) j=0;
        sleep(idTrail+1);
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
    for(int i=0;i<9;i++){
        for(int j=0;j<4;j++){
            printf("%c  ",matrix[i][j]);
        }
        printf("\n");
    }
}
void * car(void * id){
    char caracter;
    while(1){
        scanf("%c",&caracter);
        printf("Estou na car\n");
    }
    return NULL;
}
int main(){
    int * id;
    pthread_t trails[4];
    pthread_t player;
    //pthread_t screen;
      for(int i=0;i<9;i++){ // iniciando a matriz
        for(int j=0;j<4;j++){
            matrix[i][j]='0';
        }
    }
    for(int i=0;i<9;i++){ // iniciando os mutex
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
    pthread_create(&player,NULL,car,NULL);
    sleep(1);
    //pthread_create(&screen,NULL,&printMatrix,NULL);
    while(CountThreads<3){
        sleep(2);
        screen();
        printf("\n");
    } // loop de espera
    for(int i=0;i<9;i++){
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