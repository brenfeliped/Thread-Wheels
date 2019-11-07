#include <stdio.h>
#include <stdlib.h>
#include <pthread.h>
#include <unistd.h>

int  main(void){
    int j=0;
    int pos=0;
    char tecla;
    while(1){
        printf("|       |       |       |       |\n");
        printf("|       |       |       |       |\n");
        printf("|       |       |       |       |\n");
        printf("|       |       |       |       |\n");
        printf("|       |       |       |       |\n");
        printf("|       |       |       |       |\n");
        printf("|       |       |       |       |\n");
        printf("|       |       |       |       |\n");
        printf("|       |       |       |       |\n");
if(j==0)printf("|       |   #   |       |       |\n");
    else{
        if(pos==0){
            if(tecla=='a'){
                pos=-1;
                printf("|   #   |       |       |       |\n");
            }else if(tecla ==  'd'){
                pos=1;
                printf("|       |       |   #   |       |\n");
            }
        }else if(pos==-1){
            if(tecla=='d'){
                pos=0;
                printf("|       |   #   |       |       |\n");
            }
        }else if(pos==1){
            if(tecla=='a'){
                pos=0;
                printf("|       |   #   |       |       |\n");
            }else if(tecla=='d'){
                pos=2;
                printf("|       |       |       |   #   |\n");
            }
        }else if(pos==2){
            if(tecla=='a'){
                pos=1;
                printf("|       |       |   #   |       |\n");
            }
        }
        scanf("%c",&tecla);
      /*printf("|   #   |       |       |       |\n");
        printf("|       |       |   #   |       |\n");
        printf("|       |       |       |   #   |\n");*/
    }
        j++;
    }
    return 0;
}