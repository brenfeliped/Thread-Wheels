# Thread-Wheels
Jogo de corrida para matéria de programação concorrente 
## Gameplay
   O jogo consiste em ultrapassar os carros adversários para obter pontos. O jogo acaba quando o player perder as três vidas, só é perdida uma vida quando o player bate de frente com outro carro.
## Implementação
  A pista foi implementa com uma matriz, cada pista tem uma thread resposável pelos carros. A cada elemento da matriz é uma região crítica que controlado o acesso por uma matriz do tipo mutex.
 ## Execução
   ~~~bash
       gcc -Wall -pthread main.c -o main
       .\main
   ~~~
      
  ## Referências
  [Documentação Pthread](https://pubs.opengroup.org/onlinepubs/7908799/xsh/pthread.h.html) \
  [Road Fighter NES](https://www.retrogames.cz/play_065-NES.php)
