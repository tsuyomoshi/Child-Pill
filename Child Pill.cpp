#include<stdio.h>
#include<conio.h>
#include<graphics.h>
#include <windows.h>

#define ESC    	27

/* variáveis globais */
int GlbLar, GlbAlt;
int GlbBtnLar, GlbBtnAlt;

/* funções usadas neste programa */
void TelaInicial();
void Creditos();
void Jogo();


const int LARGURA_TELA = 1200;
const int ALTURA_TELA = 800;
const int TAMANHO_CELULA = 100;

int LARGURA_LOADING = 5000;
int ALTURA_LOADING = 800;
int WINDOW_LOADINGX = -4000;
int WINDOW_LOADINGY = -4000;

const int linhas = 8;
const int colunas = 100;

int x, y;
int passoX = 25;

const int cameraFollowOffset = 100;

int larguraPersonagem = TAMANHO_CELULA;
int alturaPersonagem = TAMANHO_CELULA;
int plataformaLargura = TAMANHO_CELULA;
int plataformaAltura = TAMANHO_CELULA;
int larguraInimigo = TAMANHO_CELULA;
int alturaInimigo = TAMANHO_CELULA;

int fimJogo = false;  // Adicionamos uma variável para controlar o estado do jogo

void *fundo, *vazio, *plataforma, *personagemMasc, *personagem, *protaCorreMasc, *protaCorre, *inimigo, *inimigoMasc, *portaMasc, *porta, *derrota;

int pg = 0;
int cameraX;

int* inimigoX;
int* inimigoY;

float velocityY = 0;
float gravity = 4;

bool canJump = true;

int contaInimigos = 0;

int mapa[linhas][colunas] = {
	{0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0},
	{0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0},
	{0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 4, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 4, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 3},
	{0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 1, 1, 1, 1, 1, 1, 1, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 1, 1, 1},
	{0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 1, 1, 1, 1, 1, 1, 0, 0, 0, 0, 4, 0, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 0, 4, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 4, 0, 0, 0, 0, 1, 1, 1, 1, 1},
	{0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 0, 0, 0, 0, 4, 0, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 0, 0, 0, 0, 0, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1},
	{0, 2, 0, 0, 1, 1, 1, 0, 0, 0, 0, 0, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1},
	{1, 1, 1, 1, 1, 1, 1 ,1 ,1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1}
};

void gameOver() {
    cleardevice(); // Limpe a tela

    // Exiba a imagem de derrota
	putimage(0, 0, derrota, COPY_PUT); // Era para ser uma imagem de fim de jogo, mas não foi bem como terminou, erro de logica provavelmente
    
    delay(2000); // Aguarde 2 segundos
    closegraph(); // Feche a janela do jogo
    exit(0); // Encerre o programa
}

bool colisao(int px, int py, int largura, int altura) {
    int colunaEsquerda = (px + cameraX) / TAMANHO_CELULA;
    int colunaDireita = (px + largura + cameraX) / TAMANHO_CELULA;
    int linhaSuperior = py / TAMANHO_CELULA;
    int linhaInferior = (py + altura) / TAMANHO_CELULA;

    for (int i = linhaSuperior; i <= linhaInferior; ++i) {
        for (int j = colunaEsquerda; j <= colunaDireita; ++j) {
            if (mapa[i][j] == 1) { // Verifica se há uma plataforma na posição
                int plataformaX = j * TAMANHO_CELULA - cameraX;
                int plataformaY = i * TAMANHO_CELULA;
                


                // Verifica se há sobreposição de retângulos
                if (px < plataformaX + TAMANHO_CELULA &&
                    px + largura > plataformaX &&
                    py < plataformaY + TAMANHO_CELULA &&
                    py + altura > plataformaY
					) {
					//rectangle((j * (TAMANHO_CELULA))  - cameraX, i * TAMANHO_CELULA, (j * (TAMANHO_CELULA))  - cameraX + TAMANHO_CELULA, i * TAMANHO_CELULA + TAMANHO_CELULA); (Debug para fazer testes de colisão)
                    // Colisão detectada, ajuste a posição do personagem
                    return true;
                }
            }
        }
    }

    for (int i = linhaSuperior; i <= linhaInferior; ++i) {
        for (int j = colunaEsquerda; j <= colunaDireita; ++j) {
            if (mapa[i][j] == 4) { // Verifica se há uma plataforma na posição
                int plataformaX = j * TAMANHO_CELULA - cameraX;
                int plataformaY = i * TAMANHO_CELULA;
                


                // Verifica se há sobreposição de retângulos
                if (px < plataformaX + TAMANHO_CELULA &&
                    px + largura > plataformaX &&
                    py < plataformaY + TAMANHO_CELULA &&
                    py + altura > plataformaY
					) {
					//rectangle((j * (TAMANHO_CELULA))  - cameraX, i * TAMANHO_CELULA, (j * (TAMANHO_CELULA))  - cameraX + TAMANHO_CELULA, i * TAMANHO_CELULA + TAMANHO_CELULA); (Debug para fazer testes de colisão)
                    // Colisão detectada, ajuste a posição do personagem
                    gameOver(); // Chame a função de game over
                    return true;
                }
            }
        }
    }
}

void cargaImagens() {
//	readimagefile("area_vazia.bmp", 0, 0, TAMANHO_CELULA, TAMANHO_CELULA);
//  getimage(0, 0, TAMANHO_CELULA, TAMANHO_CELULA, vazio);
    
    readimagefile(".\\imagens\\fundo.bmp", 0, 0, LARGURA_TELA, ALTURA_TELA);
    getimage(0, 0, LARGURA_TELA, ALTURA_TELA, fundo);
    
    readimagefile(".\\imagens\\plataforma.bmp", 0, 0, plataformaLargura, plataformaAltura);
    getimage(0, 0, plataformaLargura, plataformaAltura, plataforma);
    
    readimagefile(".\\imagens\\protagonistaMasc.bmp", 0, 0, larguraPersonagem, alturaPersonagem);
    getimage(0, 0, larguraPersonagem, alturaPersonagem, personagemMasc);

    readimagefile(".\\imagens\\protagonista.bmp", 0, 0, larguraPersonagem, alturaPersonagem);
    getimage(0, 0, larguraPersonagem, alturaPersonagem, personagem);
	    
//  readimagefile(".\\imagens\\protaCorreMasc.bmp", 0, 0, larguraPersonagem, alturaPersonagem);
//  getimage(0, 0, larguraPersonagem, alturaPersonagem, protaCorreMasc);

//  readimagefile(".\\imagens\\protaCorre.bmp", 0, 0, larguraPersonagem, alturaPersonagem);
//  getimage(0, 0, larguraPersonagem, alturaPersonagem, protaCorre);
				    
    readimagefile(".\\imagens\\inimigoMasc.bmp", 0, 0, larguraInimigo, alturaInimigo);
    getimage(0, 0, larguraInimigo, alturaInimigo, inimigoMasc);
    
    readimagefile(".\\imagens\\inimigo.bmp", 0, 0, larguraInimigo, alturaInimigo);
    getimage(0, 0, larguraInimigo, alturaInimigo, inimigo);
    
    readimagefile(".\\imagens\\portaMasc.bmp", 0, 0, TAMANHO_CELULA, TAMANHO_CELULA);
    getimage(0, 0, TAMANHO_CELULA, TAMANHO_CELULA, portaMasc);
    
    readimagefile(".\\imagens\\porta.bmp", 0, 0, TAMANHO_CELULA, TAMANHO_CELULA);
    getimage(0, 0, TAMANHO_CELULA, TAMANHO_CELULA, porta);
    
    readimagefile(".\\imagens\\derrota.bmp", 0, 0, TAMANHO_CELULA, TAMANHO_CELULA);
    getimage(0, 0, TAMANHO_CELULA, TAMANHO_CELULA, derrota);
}

void memorias() {
	fundo = malloc(imagesize(0, 0, LARGURA_TELA, ALTURA_TELA));
    vazio = malloc(imagesize(0, 0, TAMANHO_CELULA, TAMANHO_CELULA));
    plataforma = malloc(imagesize(0, 0, plataformaLargura, plataformaAltura));
    personagemMasc = malloc(imagesize(0, 0, larguraPersonagem, alturaPersonagem));
    personagem = malloc(imagesize(0, 0, larguraPersonagem, alturaPersonagem));
    protaCorreMasc = malloc(imagesize(0, 0, larguraPersonagem, alturaPersonagem));
    protaCorre = malloc(imagesize(0, 0, larguraPersonagem, alturaPersonagem));
    inimigoMasc = malloc(imagesize(0, 0, larguraInimigo, alturaInimigo));
    inimigo = malloc(imagesize(0, 0, larguraInimigo, alturaInimigo));
    portaMasc = malloc(imagesize(0, 0, TAMANHO_CELULA, TAMANHO_CELULA));
    porta = malloc(imagesize(0, 0, TAMANHO_CELULA, TAMANHO_CELULA));
    derrota = malloc(imagesize(0, 0, TAMANHO_CELULA, TAMANHO_CELULA));
}

void limpaMemorias() {
	free(fundo);
	free(vazio);
    free(plataforma);
    free(personagemMasc);
    free(personagem);
    free(protaCorreMasc);
    free(protaCorre);
    free(inimigo);
    free(inimigoMasc);
    free(portaMasc);
    free(porta);
    free(derrota);
    free(inimigoX);
    free(inimigoY);
}

void achandoPersonagem() {
    int i, j;
    
    for (i = 0; i < linhas; i++) {
        for (j = 0; j < colunas; j++) {
            if (mapa[i][j] == 2) { //Ponto de start personagem
                x = j * TAMANHO_CELULA; // Ajuste na posição inicial do personagem
                y = i * TAMANHO_CELULA;
            } if (mapa[i][j] == 4) {
            	inimigoX[contaInimigos] = j * TAMANHO_CELULA;
            	inimigoY[contaInimigos] = i * TAMANHO_CELULA;
            	contaInimigos++;
            }
        }
    }
}
 
void desenharFundo() {
	putimage(0, 0, fundo, COPY_PUT);
} 
            
void desenharFase() {
    int i, j;
    
    for (i = 0; i < linhas; ++i) {
        for (j = 0; j < colunas; ++j) {
			if (mapa[i][j] == 1) { //Plataformas
            	putimage((j * (TAMANHO_CELULA))  - cameraX, i * TAMANHO_CELULA, plataforma, COPY_PUT);
            	
            } if (mapa[i][j] == 3) { //Final
                putimage((j * (TAMANHO_CELULA))  - cameraX, i * TAMANHO_CELULA, portaMasc, AND_PUT);
                putimage((j * (TAMANHO_CELULA))  - cameraX, i * TAMANHO_CELULA, porta, OR_PUT);
            }
        }
    }
}

void desenharPersonagem() {
    putimage(x, y, personagemMasc, AND_PUT);
    putimage(x, y, personagem, OR_PUT);
}

void desenharInimigos() {
	int k;
	for (k = 0; k < contaInimigos; k++) {
		putimage(inimigoX[k] - cameraX, inimigoY[k], inimigoMasc, AND_PUT);	
	    putimage(inimigoX[k] - cameraX, inimigoY[k], inimigo, OR_PUT);
	}
}

bool colisaoFimFase(int px, int py, int largura, int altura) {
    int colunaAtual = (px + cameraX) / TAMANHO_CELULA;
    int linhaAtual = py / TAMANHO_CELULA;

    return (mapa[linhaAtual][colunaAtual] == 3);
}

void andarPersonagem() {
    if (GetKeyState(VK_LEFT) & 0x80) {
        if (!colisao(x - passoX, y - 10, larguraPersonagem, alturaPersonagem)) {
            //
            if(x < (LARGURA_TELA / 2) - cameraFollowOffset && cameraX > 0)
            {
            	cameraX -= passoX;
			}
			else
			{
				x = x - passoX;
			}
            
        }else
        {
        	//mova para o lado da plataforma
		}
    }

    if (GetKeyState(VK_RIGHT) & 0x80) {
        if (!colisao(x + passoX, y - 10, larguraPersonagem, alturaPersonagem)) {
            if(x > (LARGURA_TELA / 2) + cameraFollowOffset && cameraX < (colunas * TAMANHO_CELULA) - LARGURA_TELA)
            {
            	cameraX += passoX;
			}
			else
			{
				x = x + passoX;
			}
        }
    }

    if (GetKeyState(VK_UP) & 0x80) {
        if (!colisao(x, y - passoX, larguraPersonagem, alturaPersonagem) && canJump) {
        	canJump = false;
            velocityY = -40
			;
        }
    }

        if (!colisao(x, y + velocityY, larguraPersonagem, alturaPersonagem)) {
            velocityY += gravity;
        }
        else
        {
        	canJump = true;
        	velocityY = 0;
		}
    
    if(velocityY > 20)
    {
    	velocityY = 20;
	}
    
    y += velocityY;
	
        if (colisaoFimFase(x, y, larguraPersonagem, alturaPersonagem)) {
        fimJogo = true;
        return;
    }

}

void trocarPaginas(int &pg) {
    if (pg == 1) {
        pg = 2;
    } else {
        pg = 1;
    }
}




int main() {
  GlbLar = 1200;
  GlbAlt = 700;
  GlbBtnLar = 250;
  GlbBtnAlt = 80;

  /* inicia área gráfica */
  initwindow(GlbLar, GlbAlt, "Child Pill", 10, 10);
  /* transfere execução para a função TelaInicial() */
  TelaInicial();
  /* finaliza área gráfica */
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
  
  mciSendString("open .\\musicas\\piano.mp3 type MPEGVideo alias repetido", NULL, 0, 0);
  
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
  /* carga da imagem dos botões */
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
  
  janela = GetForegroundWindow(); // Obtém o Handle da janela gráfica
  while (!Fim) {
    if (pg == 1) pg = 2; else pg = 1;
    setactivepage(pg);
    putimage(0, 0, Fundo, COPY_PUT);
    
    mciSendString("play repetido repeat", NULL, 0, 0);
    
    if (btnJogarSelecionado)
      putimage(100, 600, btnJogarSel, COPY_PUT); // retângulo do botão 900, 400, 900+GlbBtnLar-1, 400+GlbBtnAlt-1
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
    if (GetCursorPos(&P)) // captura a posição do mouse. A variável P é carregada com coordenadas físicas de tela
      if (ScreenToClient(janela, &P)) { // Converte as coordenadas físicas de tela para as coordenadas 
  
        /* configura a troca da imagem do botão quando o mouse está sobre ele */
        btnJogarSelecionado = false; // botão jogar
        if (100 <= P.x && P.x <= 100+GlbBtnLar-1 && 600 <= P.y && P.y <= 600+GlbBtnAlt-1)
          btnJogarSelecionado = true;
        btnCreditosSelecionado = false; // botão créditos
        if (475 <= P.x && P.x <= 475+GlbBtnLar-1 && 600 <= P.y && P.y <= 600+GlbBtnAlt-1)
          btnCreditosSelecionado = true;
        btnSairSelecionado = false; // botão sair
        if (850 <= P.x && P.x <= 850+GlbBtnLar-1 && 600 <= P.y && P.y <= 600+GlbBtnAlt-1)
          btnSairSelecionado = true;

        /* verifica se o mouse foi pressionado na área de algum botão */          
        if(GetKeyState(VK_LBUTTON)&0x80) {
          // botão jogar
          mciSendString("close repetido", NULL, 0, 0);

          if (100 <= P.x && P.x <= 100+GlbBtnLar-1 && 600 <= P.y && P.y <= 600+GlbBtnAlt-1)
            Jogo();    
          // botão créditos
          else if (475 <= P.x && P.x <= 475+GlbBtnLar-1 && 600 <= P.y && P.y <= 600+GlbBtnAlt-1)
            Creditos();
          // botão sair
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
	
	inimigoX = (int *)malloc(sizeof(int) * 6);
	inimigoY = (int *)malloc(sizeof(int) * 6);
	
	initwindow(LARGURA_LOADING, ALTURA_LOADING, "LOADING",  WINDOW_LOADINGX, WINDOW_LOADINGY); //Tela de LOADING
	
	memorias();
	cargaImagens();
	
	mciSendString("open .\\musicas\\moonlight.mp3 type MPEGVideo alias repetido", NULL, 0, 0);
    
    achandoPersonagem();
    
    closegraph();
    
    initwindow(LARGURA_TELA, ALTURA_TELA, "Child Pill");

	
    while (1) {
        trocarPaginas(pg);
        setactivepage(pg);
        cleardevice();
        
        if (cameraX < 0) cameraX = 0;
        if (cameraX > (colunas * TAMANHO_CELULA) - LARGURA_TELA) cameraX = (colunas * TAMANHO_CELULA) - LARGURA_TELA;
	
		mciSendString("play repetido repeat", NULL, 0, 0);
		
		desenharFundo();		
		desenharFase();
		desenharInimigos();
        desenharPersonagem();
        andarPersonagem();

        setvisualpage(pg);
        
        if (fimJogo)
        break;
        
        delay(15);

    }
	
	mciSendString("close repetido", NULL, 0, 0);
	    
    closegraph();
    
    limpaMemorias();
}
