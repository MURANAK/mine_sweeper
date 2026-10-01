#include <stdio.h>
#include "funcoes.h"

#define LIN 9
#define COL 9
#define BOMBA -1 //precisa ser uma valor maior/menor que o valor max/min de bombas no entorno


int main(){

    //PREPARANDO O JOGO
    int campo[LIN][COL] = {0};
    criar_campo(LIN, COL, campo, BOMBA);
   //ver_campo_cheat(LIN, COL, campo, BOMBA);


   //INICIANDO O JOGO
    msg_inicial();

    int jogadas[LIN][COL] = {0};
    int x, y;
    int ganhou = 0;

    do{
        mostrar_campo(LIN, COL, campo, jogadas, BOMBA);

        fazer_jogada(LIN, COL, jogadas, &x, &y);
        
        analisar_jogada(LIN, COL, campo, jogadas, &x, &y, BOMBA);

        //vendo se venceu
        ganhou = vitoria(LIN, COL, campo, jogadas, BOMBA);


        //mensagem de vitória
        if(ganhou){
            printf("\nPARABENS! VOCE VENCEU!!\n");
            printf("\n");
            ver_campo_cheat(LIN, COL, campo, BOMBA);
        }


    }while(campo[x][y] != BOMBA && ganhou == 0);


    return 0;
}