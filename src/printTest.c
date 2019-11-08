#include <stdio.h>
#include <stdlib.h>
#include <pthread.h>
#include <unistd.h>
#ifdef _WIN32
#define CLEAR "cls"
#else
#define CLEAR "clear"
#endif
void  printEmptyTrail(){
    printf("|       |       |       |       |\n");
}

int  main(void){
    int j=0;
    int pos=0;
    char tecla;
    while(tecla!= 'q'){
        system(CLEAR);
        for(int i=0;i<8;i++)printEmptyTrail();
        /*printEmptyTrail(); //printf("|       |       |       |       |\n");
        printEmptyTrail();//printf("|       |       |       |       |\n");
        printEmptyTrail();//printf("|       |       |       |       |\n");
        printEmptyTrail();//printf("|       |       |       |       |\n");
        printEmptyTrail();//printf("|       |       |       |       |\n");
        printEmptyTrail();//printf("|       |       |       |       |\n");
        printEmptyTrail();//printf("|       |       |       |       |\n");
        printEmptyTrail();//printf("|       |       |       |       |\n");
        printEmptyTrail();//printf("|       |       |       |       |\n");*/
if(j==0)printf("|       | \033[0;31m  #  \033[0m |       |       |\n");
    else{
        if(pos==0){
            if(tecla=='a'){
                pos=-1;
                printf("|\033[0;31m   #   \033[0m|       |       |       |\n");
            }else if(tecla ==  'd'){
                pos=1;
                printf("|       |       |\033[0;31m   #   \033[0m|       |\n");
            }
        }else if(pos==-1){
            if(tecla=='d'){
                pos=0;
                printf("|       |\033[0;31m   #   \033[0m|       |       |\n");
            }
        }else if(pos==1){
            if(tecla=='a'){
                pos=0;
                printf("|       |\033[0;31m   #   \033[0m|       |       |\n");
            }else if(tecla=='d'){
                pos=2;
                printf("|       |       |       |\033[0;31m   #   \033[0m|\n");
            }
        }else if(pos==2){
            if(tecla=='a'){
                pos=1;
                printf("|       |       |\033[0;31m   #   \033[0m|       |\n");
            }
        }
        system ("/bin/stty raw"); // chamada de sistema para ler sem \n
        scanf("%c",&tecla);
        system ("/bin/stty cooked");
      /*printf("|   #   |       |       |       |\n");
        printf("|       |       |   #   |       |\n");
        printf("|       |       |       |   #   |\n");*/
    }
        j++;
    }
    system ("/bin/stty cooked");
    return 0;
}