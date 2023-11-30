#include<graphics.h>

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

void *fundo, *vazio, *plataforma, *personagemMasc, *personagem, *inimigo, *fim;

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
	{0, 2, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0},
	{0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 4, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 4, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 3},
	{0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 1, 1, 1, 1, 1, 1, 0, 0, 4, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 1, 1, 1, 1, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1},
	{0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 0, 0, 0, 0, 0, 0, 0, 0, 0, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 0, 0, 0, 0, 0, 4, 0, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1},
	{0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 0, 0, 0, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1},
	{0, 0, 0, 0, 1, 1, 1, 0, 0, 0, 4, 0, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1},
	{1, 1, 1, 1, 1, 1, 1 ,1 ,1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1}
};

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
					rectangle((j * (TAMANHO_CELULA))  - cameraX, i * TAMANHO_CELULA, (j * (TAMANHO_CELULA))  - cameraX + TAMANHO_CELULA, i * TAMANHO_CELULA + TAMANHO_CELULA);
                    // Colisão detectada, ajuste a posição do personagem
                    return true;
                }
            }
        }
    }

    return false;
}


void cargaImagens() {
//	readimagefile("area_vazia.bmp", 0, 0, TAMANHO_CELULA, TAMANHO_CELULA);
//  getimage(0, 0, TAMANHO_CELULA, TAMANHO_CELULA, vazio);
    
    readimagefile("fundo.bmp", 0, 0, LARGURA_TELA, ALTURA_TELA);
    getimage(0, 0, LARGURA_TELA, ALTURA_TELA, fundo);
    
    readimagefile("plataforma.bmp", 0, 0, plataformaLargura, plataformaAltura);
    getimage(0, 0, plataformaLargura, plataformaAltura, plataforma);
    
    readimagefile("protagonistaMasc.bmp", 0, 0, larguraPersonagem, alturaPersonagem);
    getimage(0, 0, larguraPersonagem, alturaPersonagem, personagemMasc);

    readimagefile("protagonista.bmp", 0, 0, larguraPersonagem, alturaPersonagem);
    getimage(0, 0, larguraPersonagem, alturaPersonagem, personagem);
	    
/*  readimagefile("protaCorre.bmp", 0, 0, larguraPersonagem, alturaPersonagem);
    getimage(0, 0, larguraPersonagem, alturaPersonagem, personagem);

    readimagefile("protaCorreMasc.bmp", 0, 0, larguraPersonagem, alturaPersonagem);
    getimage(0, 0, larguraPersonagem, alturaPersonagem, personagem);

    readimagefile("protaPula.bmp", 0, 0, larguraPersonagem, alturaPersonagem);
    getimage(0, 0, larguraPersonagem, alturaPersonagem, personagem);

    readimagefile("protaPulaMasc.bmp", 0, 0, larguraPersonagem, alturaPersonagem);
    getimage(0, 0, larguraPersonagem, alturaPersonagem, personagem); */
				    
    readimagefile("inimigo.bmp", 0, 0, larguraInimigo, alturaInimigo);
    getimage(0, 0, larguraInimigo, alturaInimigo, inimigo);
    
    readimagefile("fim_da_fase.bmp", 0, 0, TAMANHO_CELULA, TAMANHO_CELULA);
    getimage(0, 0, TAMANHO_CELULA, TAMANHO_CELULA, fim);
}

void memorias() {
	fundo = malloc(imagesize(0, 0, LARGURA_TELA, ALTURA_TELA));
    vazio = malloc(imagesize(0, 0, TAMANHO_CELULA, TAMANHO_CELULA));
    plataforma = malloc(imagesize(0, 0, plataformaLargura, plataformaAltura));
    personagem = malloc(imagesize(0, 0, larguraPersonagem, alturaPersonagem));
    personagemMasc = malloc(imagesize(0, 0, larguraPersonagem, alturaPersonagem));    
    inimigo = malloc(imagesize(0, 0, larguraInimigo, alturaInimigo));
    fim = malloc(imagesize(0, 0, TAMANHO_CELULA, TAMANHO_CELULA));
}

void limpaMemorias() {
	free(fundo);
	free(vazio);
    free(plataforma);
    free(personagemMasc);
    free(personagem);
    free(inimigo);
    free(fim);
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
                putimage((j * (TAMANHO_CELULA))  - cameraX, i * TAMANHO_CELULA, fim, COPY_PUT);
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
		putimage(inimigoX[k] - cameraX, inimigoY[k], inimigo, COPY_PUT);
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
            velocityY = -45
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
	
	inimigoX = (int *)malloc(sizeof(int) * 6);
	inimigoY = (int *)malloc(sizeof(int) * 6);
	
	initwindow(LARGURA_LOADING, ALTURA_LOADING, "LOADING",  WINDOW_LOADINGX, WINDOW_LOADINGY); //Tela de LOADING
	
	memorias();
	cargaImagens();
    
    achandoPersonagem();
    
    closegraph();
    
    initwindow(LARGURA_TELA, ALTURA_TELA, "Child Pill");


    while (1) {
        trocarPaginas(pg);
        setactivepage(pg);
        cleardevice();
        
        //cameraX = x;// * 5;
        if (cameraX < 0) cameraX = 0;
        if (cameraX > (colunas * TAMANHO_CELULA) - LARGURA_TELA) cameraX = (colunas * TAMANHO_CELULA) - LARGURA_TELA;

		desenharFundo();		
		desenharFase();
		desenharInimigos();
        desenharPersonagem();
        andarPersonagem();

        setvisualpage(pg);
        
        if (fimJogo)
        break;
        
        delay(5);

    }

    closegraph();
    
    limpaMemorias();
    
    return 0;
}
