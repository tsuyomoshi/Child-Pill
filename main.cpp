#include<stdio.h>
#include<conio.h>
#include<graphics.h>

#define ESC    	27

/* vari�veis globais */
int GlbLar, GlbAlt;
int GlbBtnLar, GlbBtnAlt;

/* fun��es usadas neste programa */
void TelaInicial();
void Creditos();
void Jogo();


int main() {
  GlbLar = 1200;
  GlbAlt = 700;
  GlbBtnLar = 250;
  GlbBtnAlt = 80;

  /* inicia �rea gr�fica */
  initwindow(GlbLar, GlbAlt, "Esqueleto de jogo com tela inicial e cr�ditos", 10, 10);
  /* transfere execu��o para a fun��o TelaInicial() */
  TelaInicial();
  /* finaliza �rea gr�fica */
  closegraph();
  return(0);
}

void TelaInicial() {
  bool Fim = false;
  int pg = 1;
  POINT P;
  HWND janela;
  
  bool btnJogarSelecionado = false; 
  bool btnCreditosSelecionado = false; 
  bool btnSairSelecionado = false;
  
  int tam;
  void *Fundo;
  void *btnJogar, *btnJogarSel;
  void *btnCreditos, *btnCreditosSel;
  void *btnSair, *btnSairSel;
  /* carga da imagem de fundo */
  tam = imagesize(0, 0, GlbLar-1, GlbAlt-1);
  Fundo = malloc(tam);
  readimagefile(".\\imagens\\telainicial.bmp", 0, 0, GlbLar-1, GlbAlt-1);
  getimage(0, 0, GlbLar-1, GlbAlt-1, Fundo);
  /* carga da imagem dos bot�es */
  cleardevice();
  tam = imagesize(0, 0, GlbBtnLar-1, GlbBtnAlt-1);
  btnJogar = malloc(tam);
  readimagefile(".\\imagens\\btnjogar.bmp", 0, 0, GlbBtnLar-1, GlbBtnAlt-1);
  getimage(0, 0, GlbBtnLar-1, GlbBtnAlt-1, btnJogar);
  btnJogarSel = malloc(tam);
  readimagefile(".\\imagens\\btnjogarsel.bmp", 0, 0, GlbBtnLar-1, GlbBtnAlt-1);
  getimage(0, 0, GlbBtnLar-1, GlbBtnAlt-1, btnJogarSel);
  btnCreditos = malloc(tam);
  readimagefile(".\\imagens\\btncreditos.bmp", 0, 0, GlbBtnLar-1, GlbBtnAlt-1);
  getimage(0, 0, GlbBtnLar-1, GlbBtnAlt-1, btnCreditos);
  btnCreditosSel = malloc(tam);
  readimagefile(".\\imagens\\btncreditossel.bmp", 0, 0, GlbBtnLar-1, GlbBtnAlt-1);
  getimage(0, 0, GlbBtnLar-1, GlbBtnAlt-1, btnCreditosSel);
  btnSair = malloc(tam);
  readimagefile(".\\imagens\\btnsair.bmp", 0, 0, GlbBtnLar-1, GlbBtnAlt-1);
  getimage(0, 0, GlbBtnLar-1, GlbBtnAlt-1, btnSair);
  btnSairSel = malloc(tam);
  readimagefile(".\\imagens\\btnsairsel.bmp", 0, 0, GlbBtnLar-1, GlbBtnAlt-1);
  getimage(0, 0, GlbBtnLar-1, GlbBtnAlt-1, btnSairSel);
  
  janela = GetForegroundWindow(); // Obt�m o Handle da janela gr�fica
  while (!Fim) {
    if (pg == 1) pg = 2; else pg = 1;
    setactivepage(pg);
    putimage(0, 0, Fundo, COPY_PUT);
    if (btnJogarSelecionado)
      putimage(100, 600, btnJogarSel, COPY_PUT); // ret�ngulo do bot�o 900, 400, 900+GlbBtnLar-1, 400+GlbBtnAlt-1
    else
      putimage(100, 600, btnJogar, COPY_PUT);
    if (btnCreditosSelecionado)
      putimage(475, 600, btnCreditosSel, COPY_PUT);
    else
      putimage(475, 600, btnCreditos, COPY_PUT);
    if (btnSairSelecionado)
      putimage(850, 600, btnSairSel, COPY_PUT);
    else
      putimage(850, 600, btnSair, COPY_PUT);
    setvisualpage(pg);
    /* Verifica movimento do mouse independente de haver clique */
    if (GetCursorPos(&P)) // captura a posi��o do mouse. A vari�vel P � carregada com coordenadas f�sicas de tela
      if (ScreenToClient(janela, &P)) { // Converte as coordenadas f�sicas de tela para as coordenadas 
  
        /* configura a troca da imagem do bot�o quando o mouse est� sobre ele */
        btnJogarSelecionado = false; // bot�o jogar
        if (100 <= P.x && P.x <= 100+GlbBtnLar-1 && 600 <= P.y && P.y <= 600+GlbBtnAlt-1)
          btnJogarSelecionado = true;
        btnCreditosSelecionado = false; // bot�o cr�ditos
        if (475 <= P.x && P.x <= 475+GlbBtnLar-1 && 600 <= P.y && P.y <= 600+GlbBtnAlt-1)
          btnCreditosSelecionado = true;
        btnSairSelecionado = false; // bot�o sair
        if (850 <= P.x && P.x <= 850+GlbBtnLar-1 && 600 <= P.y && P.y <= 600+GlbBtnAlt-1)
          btnSairSelecionado = true;

        /* verifica se o mouse foi pressionado na �rea de algum bot�o */          
        if(GetKeyState(VK_LBUTTON)&0x80) {
          // bot�o jogar
          if (100 <= P.x && P.x <= 100+GlbBtnLar-1 && 600 <= P.y && P.y <= 600+GlbBtnAlt-1)
            Jogo();    
          // bot�o cr�ditos
          else if (475 <= P.x && P.x <= 475+GlbBtnLar-1 && 600 <= P.y && P.y <= 600+GlbBtnAlt-1)
            Creditos();
          // bot�o sair
          else if (850 <= P.x && P.x <= 850+GlbBtnLar-1 && 600 <= P.y && P.y <= 600+GlbBtnAlt-1)
            Fim = true;
        }
      }
  }  
}

void Creditos() {
  char tecla = 0;
  int tam;
  void *Fundo;
  bool Fim = false;
  int pg = 1;

  tam = imagesize(0, 0, GlbLar-1, GlbAlt-1);
  Fundo = malloc(tam);
  readimagefile(".\\imagens\\creditos.bmp", 0, 0, GlbLar-1, GlbAlt-1);
  getimage(0, 0, GlbLar-1, GlbAlt-1, Fundo);

  while (!Fim) {
    if (pg == 1) pg = 2; else pg = 1;
    setactivepage(pg);
    putimage(0, 0, Fundo, COPY_PUT);
    setvisualpage(pg);
    if (kbhit()){
      tecla = getch();
      if (tecla == ESC)
        Fim = true;
    }
  }
}

void Jogo() {
  int pg = 1;
  char tecla = 0;
  char s[50];
  int  x, y, raio;
  double passox, passoy;
  x = 100;
  y = 100;
  raio = 18; 
  passox = 3;
  passoy = 1;
  strcpy(s, "pressione Esc para Sair");

  while(tecla != ESC) {
    if (pg == 1) pg = 2; else pg = 1;
    setactivepage(pg);
    /* Prepara o fundo */
    cleardevice();
    setcolor(RGB(255, 50, 50));
    rectangle(10, 10, GlbLar-11, GlbAlt-31);
    /* desenha o objeto m�vel */
    setfillstyle(1, YELLOW);
    setcolor (YELLOW);
    fillellipse(x, y, raio, raio);

    setbkcolor(RGB(75, 75, 75));
    setcolor(RGB(255, 155, 155));
    outtextxy(12, GlbAlt-25, s);

    setvisualpage(pg);

    x = x + passox; 
    if (x <= 10+raio || x >= GlbLar-31-raio) 
      passox = -passox;
    y = y + passoy;
    if (y <= 10+raio || y >= GlbAlt-31-raio)
      passoy = -passoy;

    delay(5);

    fflush(stdin);
    if (kbhit())
      tecla = getch();   
  }
}

