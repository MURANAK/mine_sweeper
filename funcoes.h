#include <stdio.h>
#include <stdlib.h>
#include <time.h>

//PROTÓTIPOS
void msg_inicial();
void ver_campo_cheat(int lin, int col, int campo[lin][col], int bomba);
void mostrar_campo(int lin, int col, int campo[lin][col], int jogadas [lin][col], int bomba);
void criar_campo(int lin, int col, int field[lin][col], int bomba);
    void colocar_bombas(int lin, int col, int cmp[lin][col], int bomba);
    void ver_bombas(int lin, int col, int cmp[lin][col], int bomba);
void fazer_jogada(int lin, int col, int jog[lin][col], int *x, int *y);
void analisar_jogada(int lin, int col, int cpm[lin][col], int jog[lin][col], int *x, int *y, int bomba);
int vitoria(int lin, int col, int cmp[lin][col], int jog[lin][col], int bomba);

//Para ver o campo com todos os espacos revelados
void ver_campo_cheat(int lin, int col, int campo[lin][col], int bomba){
    int l, c;
    for(l=0; l<lin; l++){
        for(c=0; c<col; c++)
            if(campo[l][c] == bomba)
                printf("# ");
            else
                printf("%d ", campo[l][c]);
        printf("\n");
    }

    printf("\n");
}

//Para mostrar o campo, inicialmente todo escondido e revelando aos poucos
void mostrar_campo(int lin, int col, int campo[lin][col], int jogadas [lin][col], int bomba){
    int l, c;

    printf("\n");
    for(l=0; l<lin; l++){
        for(c=0; c<col; c++){
            if(jogadas[l][c] == 1 && campo[l][c] == bomba){
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

//Mensagem com as regras do campo minado
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

//Juntando as duas funcoes de preparacao do campo em so uma
void criar_campo(int lin, int col, int field[lin][col], int bomba){

    colocar_bombas(lin, col, field, bomba);

    ver_bombas(lin, col, field, bomba);
}

//Colocando as bombas "aleatoriamente"
void colocar_bombas(int lin, int col, int cmp[lin][col], int bomba){
    //definindo a semente
    srand(time(NULL));

    int l, c;
    float aux;
    float tx_bomba = 0.3; //definir as chances de aparacer uma bomba

    for(l=0; l<lin; l++){
        for(c=0; c<col; c++){
            aux = (float)rand() / RAND_MAX;
            if(aux < tx_bomba)
                cmp[l][c] = bomba;
        }
    }
}

//Colocando quantas bombas ha no entorno dos espacos sem bomba
void ver_bombas(int lin, int col, int cmp[lin][col], int bomba){
    int l, c;
    int quant_bombas;

    for(l=0; l<lin; l++){
        for(c=0; c<col; c++){
            quant_bombas = 0;

            if(cmp[l][c] == 0){
                if(cmp[l-1][c] == bomba && (l-1)>=0) //vendo leste
                    quant_bombas++;
                if(cmp[l+1][c] == bomba && (l+1)<lin) //vendo oeste
                    quant_bombas++;
                if(cmp[l][c-1] == bomba && (c-1)>=0) //vendo norte
                    quant_bombas++;
                if(cmp[l][c+1] == bomba && (c+1)<col) //vendo sul
                    quant_bombas++;

                if(cmp[l-1][c-1] == bomba && (l-1)>=0) //vendo noroeste
                    quant_bombas++;
                if(cmp[l+1][c-1] == bomba && (l+1)<lin) //vendo sudoeste
                    quant_bombas++;
                if(cmp[l-1][c+1] == bomba && (c-1)>=0) //vendo nordeste
                    quant_bombas++;
                if(cmp[l+1][c+1] == bomba && (c+1)<col) //vendo suldeste
                    quant_bombas++;

                cmp[l][c] = quant_bombas;
            }
        }
    }

}

//Para registrar as jogadas
void fazer_jogada(int lin, int col, int jog[lin][col], int *x, int *y){
    do{
            printf("\nInsira a LINHA que deseja atacar entre [%d, %d] e aperte enter: ", 1, lin);
            scanf("%d", &*x);
            *x-=1;

            printf("\nInsira a COLUNA que deseja atacar entre [%d, %d] e aperte enter: ", 1, col);
            scanf("%d", &*y);
            *y-=1;

            if(*x<0 || *x>=lin || *y<0 || *y>=col)
                printf("\nCOORDENADA INVALIDA! TENTE NOVAMENTE!\n");
            else if(jog[*x][*y] == 1)
                printf("\nCOORDENADA JA REVELADA! TENTE NOVAMENTE!\n");
            
        }while(*x<0 || *x>=lin || *y<0 || *y>=col || jog[*x][*y] == 1);
}


//Vendo se atingiu uma bomba, se nao, registrando a jogada 
void analisar_jogada(int lin, int col, int cpm[lin][col], int jog[lin][col], int *x, int *y, int bomba){
    if(cpm[*x][*y] == bomba){
        printf("\nVoce atingiu uma bomba, mais sorte na proxima vez!\n");
        //imprimindo o campo completo
        printf("\n");
        ver_campo_cheat(lin, col, cpm, bomba);
    }
    else{
        //Registrando a jogada
        jog[*x][*y] = 1;

        if(*x-1>=0){
            jog[*x-1][*y] = 1;
            if(*y-1>=0)
                jog[*x-1][*y-1] = 1;
            if(*y+1<col)
                jog[*x-1][*y+1] = 1;
        }
        if(*x+1<lin){
            jog[*x+1][*y] = 1;
            if(*y-1>=0)
                jog[*x+1][*y-1] = 1;
            if(*y+1<col)
                jog[*x+1][*y+1] = 1;
        }
        if(*y-1>=0){
            jog[*x][*y-1] = 1;
        }
        if(*y+1<lin){
            jog[*x][*y+1] = 1;
        }
    }
}

//Vendo se as condicoes de vitoria foram satisfeitas
int vitoria(int lin, int col, int cmp[lin][col], int jog[lin][col], int bomba){
    int continuar = 0;
    int vit = 0;
    int l, c;

    //vendo se todos os espacos sem bombas foram revelados
    for(l=0; l<lin; l++){
            for(c=0; c<col; c++){
                if(jog[l][c] == 1)
                    vit = 1;
                else if(cmp[l][c] != bomba){
                    continuar = 1;
                }
            }
        }

        if(continuar){
            vit = 0;
        }
    
    return vit;
}