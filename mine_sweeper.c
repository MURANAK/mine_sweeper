#include <stdio.h>
#include <stdlib.h>
#include <time.h>

#define LIN 9
#define COL 9
#define BOMBA -1 //precisa ser uma valor maior/menor que o valor max/min de bombas no entorno

//PROTÓTIPOS
void msg_inicial();
void ver_campo_cheat(int campo[LIN][COL]);
void mostrar_campo(int campo[LIN][COL], int jogadas [LIN][COL]);
void criar_campo(int field[LIN][COL]);
    void colocar_bombas(int cmp[LIN][COL]);
    void ver_bombas(int cmp[LIN][COL]);
void fazer_jogada(int jog[LIN][COL]);

int main(){

    //Declaracao de variaveis
    int campo[LIN][COL] = {0};
    int jogadas[LIN][COL] = {0};
    int l, c;
    int x, y;
    int ganhou = 0, continuar;

    criar_campo(campo);

   //ver_campo_cheat(campo);


    msg_inicial();


    do{
        mostrar_campo(campo, jogadas);

        do{
            printf("\nInsira a coordenada X que deseja atacar entre [%d, %d] e aperte enter: ", 1, LIN);
            scanf("%d", &x);
            x-=1;

            printf("\nInsira a coordenada Y que deseja atacar entre [%d, %d] e aperte enter: ", 1, COL);
            scanf("%d", &y);
            y-=1;

            if(x<0 || x>=LIN || y<0 || y>=COL)
                printf("\nCOORDENADA INVALIDA! TENTE NOVAMENTE!\n");
            else if(jogadas[x][y] == 1)
                printf("\nCOORDENADA JA REVELADA! TENTE NOVAMENTE!\n");
            
        }while(x<0 || x>=LIN || y<0 || y>=COL || jogadas[x][y] == 1);
        

        if(campo[x][y] == BOMBA){
            printf("\nVoce atingiu uma bomba, mais sorte na proxima vez!\n");
            //imprimindo o campo completo
            printf("\n");
            ver_campo_cheat(campo);
        }
        else{
            //Registrando a jogada
            jogadas[x][y] = 1;

            if(x-1>=0){
                jogadas[x-1][y] = 1;
                if(y-1>=0)
                    jogadas[x-1][y-1] = 1;
                if(y+1<COL)
                    jogadas[x-1][y+1] = 1;
            }
            if(x+1<LIN){
                jogadas[x+1][y] = 1;
                if(y-1>=0)
                    jogadas[x+1][y-1] = 1;
                if(y+1<COL)
                    jogadas[x+1][y+1] = 1;
            }
            if(y-1>=0){
                jogadas[x][y-1] = 1;
            }
            if(y+1<COL){
                jogadas[x][y+1] = 1;
            }
        }

        //vendo quanto se o campo inteiro foi revelado
        continuar = 0;
        for(l=0; l<LIN; l++){
            for(c=0; c<COL; c++){
                if(jogadas[l][c] == 1)
                    ganhou = 1;
                else if(campo[l][c] != BOMBA){
                    continuar = 1;
                }
            }
        }

        if(continuar){
            ganhou = 0;
        }


    }while(campo[x][y] != BOMBA && ganhou == 0);

    if(ganhou){
        printf("\nPARABENS! VOCE VENCEU!!\n");
        printf("\n");
        ver_campo_cheat(campo);
    }

    return 0;
}

/*
****************************************************************************************************************************
DECLARANDO FUNCOES
****************************************************************************************************************************
*/

void ver_campo_cheat(int campo[LIN][COL]){
    int l, c;
    for(l=0; l<LIN; l++){
        for(c=0; c<COL; c++)
            if(campo[l][c] == BOMBA)
                printf("# ");
            else
                printf("%d ", campo[l][c]);
        printf("\n");
    }

    printf("\n");
}

void mostrar_campo(int campo[LIN][COL], int jogadas [LIN][COL]){
    int l, c;

    printf("\n");
    for(l=0; l<LIN; l++){
        for(c=0; c<COL; c++){
            if(jogadas[l][c] == 1 && campo[l][c] == BOMBA){
                printf("# ");
            }
            else if(jogadas[l][c] == 1)
                printf("%d ", campo[l][c]);
            else{
                printf("? ");
            }
        }
        printf("\n");
    }
}

void msg_inicial(){
    printf("\nBEM VINDO AO CAMPO MINADO\n");
    printf("BOMBAS SAO REPRESENTADAS COM O CARACTERE '#'\n");
    printf("OS NUMEROS MOSTRAM QUANTAS BOMBAS EXISTEM NO ENTORNO DAQUELA CASA\n");
    printf("VOCE NAO PODE CHUTAR COORDENADAS QUE JA FORAM REVELADAS\n");
    printf("SEU OBJETIVO EH REVELAR O CAMPO INTEIRO SEM PEGAR UMA BOMBA\n");
    printf("BOA SORTE!\n");
}

/*
As proximas funcoes usam do recurso de "ponteiros"
esse recurso permite que eu crie um placeholder na declaracao da funcao e depois
o valor alterado sera o valor da funcao que eu ira ser colocada no parametro
eh preciso colocar o & antes do nome da variavel na chamada de funcao para passar para o
compilador o endereco daquela variavel na memoria

matrizes nao precisam que seja criado um ponteiro, seus nomes ja naturalmente indicam a primeira linha
so eh preciso informar o numero de colunas
*/

void criar_campo(int field[LIN][COL]){

    colocar_bombas(field);

    ver_bombas(field);
}

void colocar_bombas(int cmp[LIN][COL]){
    //definindo a semente
    srand(time(NULL));

    int l, c;
    float aux;
    float tx_bomba = 0.3; //definir as chances de aparacer uma bomba

    for(l=0; l<LIN; l++){
        for(c=0; c<COL; c++){
            aux = (float)rand() / RAND_MAX;
            if(aux < tx_bomba)
                cmp[l][c] = BOMBA;
        }
    }
}

void ver_bombas(int cmp[LIN][COL]){
    int l, c;
    int quant_bombas;

    for(l=0; l<LIN; l++){
        for(c=0; c<COL; c++){
            quant_bombas = 0;

            if(cmp[l][c] == 0){
                if(cmp[l-1][c] == BOMBA && (l-1)>=0) //vendo leste
                    quant_bombas++;
                if(cmp[l+1][c] == BOMBA && (l+1)<LIN) //vendo oeste
                    quant_bombas++;
                if(cmp[l][c-1] == BOMBA && (c-1)>=0) //vendo norte
                    quant_bombas++;
                if(cmp[l][c+1] == BOMBA && (c+1)<COL) //vendo sul
                    quant_bombas++;

                if(cmp[l-1][c-1] == BOMBA && (l-1)>=0) //vendo noroeste
                    quant_bombas++;
                if(cmp[l+1][c-1] == BOMBA && (l+1)<LIN) //vendo sudoeste
                    quant_bombas++;
                if(cmp[l-1][c+1] == BOMBA && (c-1)>=0) //vendo nordeste
                    quant_bombas++;
                if(cmp[l+1][c+1] == BOMBA && (c+1)<COL) //vendo suldeste
                    quant_bombas++;

                cmp[l][c] = quant_bombas;
            }
        }
    }

}

