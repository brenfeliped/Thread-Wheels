#include <stdio.h>
#include <stdlib.h>
#include <pthread.h>
#include <string.h>
#include <unistd.h>
#ifndef _WIN32
    #include <termios.h>
    #include <fcntl.h>
    int kbhit(){
        struct termios oldt, newt;
        int ch, oldf;
        tcgetattr(STDIN_FILENO,&oldt);
        newt = oldt;
        newt.c_lflag &= ~(ICANON | ECHO);
        tcsetattr(STDIN_FILENO, TCSANOW, &newt);
        oldf = fcntl(STDIN_FILENO, F_GETFL, 0);
        fcntl(STDIN_FILENO, F_SETFL, oldf | O_NONBLOCK);
        ch = getchar();    
        tcsetattr(STDIN_FILENO, TCSANOW, &oldt);
        fcntl(STDIN_FILENO, F_SETFL, oldf);
    if( ch != EOF){
        ungetc(ch,stdin);
        return 1;
    }
    return 0;
    }
    int getch(void) {
        int ch;
        struct termios oldt;
        struct termios newt;
        tcgetattr(STDIN_FILENO,&oldt);
        newt = oldt;
        newt.c_lflag &= ~(ICANON | ECHO);
        tcsetattr(STDIN_FILENO, TCSANOW, &newt);
        ch = getchar();
        tcsetattr(STDIN_FILENO, TCSANOW, &oldt);
        return ch;
    }
#else
    #include <conio.h>
#endif
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
int playerCol = 1;
int playerRow = 8;
char tecla;
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
    int i=0;
    int * numtrail = (int *) id;
    int idTrail = * numtrail;
    //printf("IdTrail = %d\n",idTrail);
    while(tecla != 'q'){ // condicao temporaria
        pthread_mutex_lock(&acesso[i][idTrail]);
        matrix[i][idTrail] = idTrail;
        if(i==0){
            switch (idTrail){
            case 0:
                if(matrix[8][idTrail]=='!')matrix[8][idTrail]='0';
                matrix[i][idTrail] = '!';
                break;
            case 1:
                if(matrix[8][idTrail]=='P')matrix[8][idTrail]='0';
                matrix[i][idTrail] = 'P';
                break;
            case 2:
                if(matrix[8][idTrail]=='&')matrix[8][idTrail]='0';
                matrix[i][idTrail] = '&';
                break;
            default:
                if(matrix[8][idTrail]=='U')matrix[8][idTrail]='0';
                matrix[i][idTrail] = 'U';
                break;
            }
        }else{
            matrix[i-1][idTrail] = '0';
            switch (idTrail){
            case 0:
                matrix[i][idTrail] = '!';
                break;
            case 1:
                matrix[i][idTrail] = 'P';
                break;
            case 2:
                matrix[i][idTrail] = '&';
                break;
            default:
                matrix[i][idTrail] = 'U';
                break;
            }
        }
        pthread_mutex_unlock(&acesso[i][idTrail]);
        i++;
        if(i==9) i=0;
        sleep(idTrail*1+1);
    }
    //sleep(1);
    pthread_mutex_lock(&somaThreads);
    CountThreads+=1;
    pthread_mutex_unlock(&somaThreads);
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
    //char tecla;
    while(tecla!='q'){
        if(kbhit()==1){ // se uma tecla for digitada
            tecla = (char)getch();
            switch (tecla){
            case 'd':
                if(playerCol!=3){
                    playerCol+=1;
                    if(pthread_mutex_trylock(&acesso[playerRow][playerCol])){ // posicao a  direita ocupada
                        playerCol-=1; // continua na mesma posicao
                    }else{
                        matrix[playerRow][playerCol-1] = '0';
                        matrix[playerRow][playerCol] = '@';
                        pthread_mutex_unlock(&acesso[playerRow][playerCol]);
                    }
                }
                break;
            case 'a':
                if(playerCol!=0){
                    playerCol-=1;
                    if(pthread_mutex_trylock(&acesso[playerRow][playerCol])){// posicao a  esquerda ocupada
                        playerCol+=1;
                    }else{
                        matrix[playerRow][playerCol+1] = '0';
                        matrix[playerRow][playerCol] = '@';
                        pthread_mutex_unlock(&acesso[playerRow][playerCol]);
                    }
                }
                break;
            case 's':
                if(playerRow!=8){
                    playerRow+=1;
                    if(pthread_mutex_trylock(&acesso[playerRow][playerCol])){// posicao abaixo  ocupada
                        playerRow-=1;
                    }else{
                        matrix[playerRow-1][playerCol] = '0';
                        matrix[playerRow][playerCol] = '@';
                        pthread_mutex_unlock(&acesso[playerRow][playerCol]);
                    }
                }
                break;
            case 'w':
                if(playerRow!=0){
                    playerRow=playerRow-1;
                    if(pthread_mutex_trylock(&acesso[playerRow][playerCol])){//posicao acima ocupada(morte)
                        // implementa a morte e diminuicao de life
                        tecla='q'; // temporario
                    }else{
                        matrix[playerRow+1][playerCol] = '0';
                        matrix[playerRow][playerCol] = '@';
                        pthread_mutex_unlock(&acesso[playerRow][playerCol]);
                    }
                }
                break;
            default:
                break;
            }
        }
    }
    pthread_exit(NULL);
}
void loopGame(){
    
}
int main(){
    int * id;
    pthread_t trails[4];
    pthread_t player;
    //pthread_t screen;
      for(int i=0;i<9;i++){ // iniciando a matriz logica
        for(int j=0;j<4;j++){
            if(i==8 && j==1)matrix[i][j]='@'; // posicao incial player
            else matrix[i][j]='0';
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
    //pthread_create(&screen,NULL,&printMatrix,NULL);
    while(CountThreads<3){
        usleep(10500);
        screen();
        printf("\n");
    } // loop de espera
    for(int i=0;i<9;i++){
        for(int j=0;j<4;j++){
            pthread_mutex_destroy(&acesso[i][j]);
        }
    }
    pthread_mutex_destroy(&somaThreads);
    //pthread_join((pthread_t)&player,NULL);
    //printf("Cheguei no printMatrix\n");
    //sleep(1);
    //printMatrix();
    return 0;
}