
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
void mudaCor(int cor);
