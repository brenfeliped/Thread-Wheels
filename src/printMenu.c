#include <stdio.h>
#include <stdlib.h>
#include <pthread.h>
#include <unistd.h>

void Controls(){
	  char c;
		while(1){
			system("clear");
			printf("\nControles:\n");
			printf("W avança o veiculo\n");
			printf("S retrocede o veiculo\n");
			printf("A/D muda de pista\n");
			printf("Digite 's' e aperte enter para sair:");
			scanf("\n%c",&c);
			if(c == 's'){break;}
		}
}

void Menu(){
	int selected = 0;
	
	while(1){
		system("clear");
		//usleep(100000);
		system ("/bin/stty cooked");
		printf("\n\n");
		printf(" ########  ##  ## #####    #####  ####    #####\n");
		printf("    ##     ##  ## ##   ##  ##    ##   ##  ##   ##\n");
		printf("    ##     ###### ######   ####  #######  ##   ##\n");
		printf("    ##     ##  ## ####     ##    ##   ##  ##   ##\n");
		printf("    ##     ##  ## ##  ##   ##### ##   ##  ######  \n");
		printf("\n");

		printf(" ##    ## ##  ## #####  ##### ##       ###\n");
		printf(" ##    ## ##  ## ##     ##    ##     ##   \n");
		printf(" ##    ## ###### ####   ####  ##      ##  \n");
		printf(" ## ## ## ##  ## ##     ##    ##        ##\n");
		printf(" ###  ### ##  ## #####  ##### ###### #### \n");
		printf("\n");
		printf("1.Startgame\n");
		printf("2.Controles\n");
		printf("3.Sair\n");
		printf("\nDigite um número e aperte enter para selecionar a opção:\n");
		scanf("%d\n",&selected);
		switch(selected){
			case 1:
			break;
			case 2:
			Controls();
			break;
			case 3:
			exit(0);
			break;
			}
		}
}

int main()
{
	Menu();
	return 0;
}