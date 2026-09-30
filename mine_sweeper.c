#include <stdio.h>
#include <stdlib.h>
#include <time.h>

#define LIN 9
#define COL 9
#define BOMBA 5 //precisa ser uma valor maior que o valor max de bombas no entorno

//PROTÓTIPOS
void msg_inicial();
void ver_campo_cheat(int campo[LIN][COL]);
void mostrar_campo(int campo[LIN][COL], int jogadas [LIN][COL]);

int main(){
    //definindo a semente
    srand(time(NULL));

    //Declaracao de variaveis
    int campo[LIN][COL] = {0};
    int jogadas[LIN][COL] = {0};
    float tx_bomba = 0.3; //probabilidade de aparecer uma bomba
    float aux;
    int l, c;
    int quant_bombas;
    int x, y;
    int ganhou = 0, continuar;

    //preenchendo o campo com bombas
    for(l=0; l<LIN; l++){
        for(c=0; c<COL; c++){
            aux = (float)rand() / RAND_MAX;
            if(aux < tx_bomba)
                campo[l][c] = BOMBA;
        }
    }

    //visualizando o campo
    //ver_campo_cheat(campo);

    //colocando quantas bombas tem no entorno dos espacos vazios
    for(l=0; l<LIN; l++){
        for(c=0; c<COL; c++){
            quant_bombas = 0;

            if(campo[l][c] == 0){
                if(campo[l-1][c] == BOMBA && (l-1)>=0) //vendo leste
                    quant_bombas++;
                if(campo[l+1][c] == BOMBA && (l+1)<LIN) //vendo oeste
                    quant_bombas++;
                if(campo[l][c-1] == BOMBA && (c-1)>=0) //vendo norte
                    quant_bombas++;
                if(campo[l][c+1] == BOMBA && (c+1)<COL) //vendo sul
                    quant_bombas++;

                campo[l][c] = quant_bombas;
            }
        }
    }

    //visualizando o campo
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
            if(x-1>=0)
                jogadas[x-1][y] = 1;
            if(x+1<LIN)
                jogadas[x+1][y] = 1;
            if(y-1>=0)
                jogadas[x][y-1] = 1;
            if(y+1<COL)
                jogadas[x][y+1] = 1;
        }

        //vendo quanto se o campo inteiro foi revelado
        //printf("\n");
        continuar = 0;
        for(l=0; l<LIN; l++){
            for(c=0; c<COL; c++){
                //printf("%d ", jogadas[l][c]);
                if(jogadas[l][c] == 1)
                    ganhou = 1;
                else if(campo[l][c] != BOMBA){
                    continuar = 1;
                }
            }
            //printf("\n");
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


//DECLARANDO FUNCOES
void ver_campo_cheat(int campo[LIN][COL]){
    int l, c;
    for(l=0; l<LIN; l++){
        for(c=0; c<COL; c++)
            printf("%d ", campo[l][c]);
        printf("\n");
    }
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
    printf("OS NUMEROS MOSTRAM QUANTAS BOMBAS EXISTEM NO ENTORNO IMEDIADO DAQUELA CASA (NORTE, SUL LESTE OESTE)\n");
    printf("VOCE NAO PODE CHUTAR COORDENADAS QUE JA FORAM REVELADAS\n");
    printf("SEU OBJETIVO EH REVELAR O CAMPO INTEIRO SEM PEGAR UMA BOMBA\n");
    printf("BOA SORTE!\n");
}
