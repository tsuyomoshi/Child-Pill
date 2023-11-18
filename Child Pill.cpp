#include <graphics.h>
#include <conio.h>
#include <cstdlib>
#include <ctime>
#include <iostream>
using namespace std;

const int LARGURA_TELA = 1200;
const int ALTURA_TELA = 800;
const int LARGURA_CELULA = 100;
const int ALTURA_CELULA = 100;
const int NUM_COLUNAS = LARGURA_TELA / LARGURA_CELULA;
const int NUM_LINHAS = ALTURA_TELA / ALTURA_CELULA;

const int GRAVIDADE = 1;
const int VELOCIDADE_PULO = 15;

void desenharPersonagem(int x, int y) {
    setfillstyle(SOLID_FILL, YELLOW);
    bar(x, y, x + LARGURA_CELULA, y + ALTURA_CELULA);
}

void desenharPlataforma(int x, int y) {
    setfillstyle(SOLID_FILL, BLACK);
    bar(x, y, x + LARGURA_CELULA, y + ALTURA_CELULA);
}

void desenharAreaVazia(int x, int y) {
    setfillstyle(SOLID_FILL, WHITE);
    bar(x, y, x + LARGURA_CELULA, y + ALTURA_CELULA);
}

void desenharFimDeJogo(int x, int y) {
    setfillstyle(SOLID_FILL, RED);
    bar(x, y, x + LARGURA_CELULA, y + ALTURA_CELULA);
}

void trocarPaginas(int &pg) {
    if (pg == 1) {
        pg = 2;
    } else {
        pg = 1;
    }
}

int main() {
    int pg = 0;
    initwindow(LARGURA_TELA, ALTURA_TELA, "Child Pill");

    // Inicializa a posição do personagem com base na matriz
    int personagemX = 0, personagemY = 0;
    int velocidadeX = 0;
    int velocidadeY = 0;

    const int NUM_LINHAS = 8;
    const int NUM_COLUNAS = 50;

    int mapa[NUM_LINHAS][NUM_COLUNAS] = {
        {1, 1, 1, 1, 1, 1, 1 ,1 ,1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1},
		{1, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 1},
		{1, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 1, 1, 1, 1, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 1, 0, 0, 0, 0, 0, 0, 0, 0, 0, 1},
		{1, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 1, 1, 1, 1, 1, 1, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 1, 1, 1, 0, 0, 0, 0, 0, 0, 0, 3, 1},
		{1, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 0, 0, 0, 0, 0, 0, 0, 1, 1, 1, 1, 1, 1, 1, 0, 0, 0, 0, 0, 0, 1, 1},
		{1, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 0, 0, 0, 0, 0, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 0, 0, 0, 0, 1, 1, 1},
		{1, 2, 0, 0, 1, 1, 0, 0, 0, 0, 0, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 0, 0, 0, 0, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1},
		{1, 1, 1, 1, 1, 1, 1 ,1 ,1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1}};

    // Localiza a posição inicial do personagem na matriz
    for (int i = 0; i < NUM_LINHAS; ++i) {
        for (int j = 0; j < NUM_COLUNAS; ++j) {
            if (mapa[i][j] == 2) {
                personagemX = j * LARGURA_CELULA;
                personagemY = i * ALTURA_CELULA;
            }
        }
    }

    while (1) {
        trocarPaginas(pg);
        setactivepage(pg);
        cleardevice();

        // Lógica da câmera
        int cameraX = personagemX - LARGURA_TELA / 2;
        if (cameraX < 0) cameraX = 0;
        if (cameraX > (NUM_COLUNAS * LARGURA_CELULA) - LARGURA_TELA) cameraX = (NUM_COLUNAS * LARGURA_CELULA) - LARGURA_TELA;

        // Desenhar o mapa
        for (int i = 0; i < NUM_LINHAS; ++i) {
            for (int j = 0; j < NUM_COLUNAS; ++j) {
                int posX = j * LARGURA_CELULA - cameraX;
                int posY = i * ALTURA_CELULA;

                switch (mapa[i][j]) {
                    case 0:
                        desenharAreaVazia(posX, posY);
                        break;
                    case 1:
                        desenharPlataforma(posX, posY);
                        break;
                    case 3:
                        desenharFimDeJogo(posX, posY);
                        break;
                    // ... (outras opções de desenho)
                }
            }
        }

        // Atualizar posição do personagem com base na velocidade
        personagemX += velocidadeX;
        personagemY += velocidadeY;

        // Aplicar gravidade apenas se não estiver em uma plataforma
        int colunaAtual = personagemX / LARGURA_CELULA;
        int linhaAtual = personagemY / ALTURA_CELULA;

        if (mapa[linhaAtual][colunaAtual] != 1) {
            velocidadeY += GRAVIDADE;
        } else {
            velocidadeY = 0;
            personagemY = linhaAtual * ALTURA_CELULA;
        }

        // Garantir que o personagem não ultrapasse as bordas da matriz
        if (personagemX < 0) personagemX = 0;
        if (personagemX > (NUM_COLUNAS * LARGURA_CELULA) - LARGURA_CELULA) personagemX = (NUM_COLUNAS * LARGURA_CELULA) - LARGURA_CELULA;

        // Desenhar o personagem por último
        desenharPersonagem(personagemX - cameraX, personagemY);

        setvisualpage(pg);

        if (GetKeyState(VK_LEFT) & 0x80) velocidadeX = -5;
        else if (GetKeyState(VK_RIGHT) & 0x80) velocidadeX = 5;
        else velocidadeX = 0;

        if (GetKeyState(VK_SPACE) & 0x80 && personagemY == ALTURA_TELA - ALTURA_CELULA) {
            velocidadeY = -VELOCIDADE_PULO;
        }

        delay(5); // Adicione um pequeno atraso para controlar a velocidade do loop
    }

    closegraph();
    return 0;
}

