#include <graphics.h>
#include <conio.h>
#include <cstdlib>
#include <ctime>
#include <iostream>

const int LARGURA_TELA = 1200;
const int ALTURA_TELA = 800;
const int LARGURA_CELULA = 100;
const int ALTURA_CELULA = 100;
const int TAMANHO_ATAQUE = 50;
const int DURACAO_ATAQUE = 100;
const int GRAVIDADE = 1;
const int VELOCIDADE_PULO = 15;
const int TEMPO_RECARREGA_ATAQUE = 300;

struct Inimigo {
    int x, y;
    bool ativo;
};

void desenharPersonagem(int x, int y, bool atacando) {
    setfillstyle(SOLID_FILL, YELLOW);
    bar(x, y, x + LARGURA_CELULA, y + ALTURA_CELULA);

    if (atacando) {
        setfillstyle(SOLID_FILL, RED);
        bar(x + LARGURA_CELULA, y, x + LARGURA_CELULA + TAMANHO_ATAQUE, y + ALTURA_CELULA);
    }
}

void desenharPlataforma(int x, int y) {
    setfillstyle(SOLID_FILL, WHITE);
    bar(x, y, x + LARGURA_CELULA, y + ALTURA_CELULA);
}

void desenharAreaVazia(int x, int y) {
    setfillstyle(SOLID_FILL, BLACK);
    bar(x, y, x + LARGURA_CELULA, y + ALTURA_CELULA);
}

void desenharFimDeJogo(int x, int y) {
    setfillstyle(SOLID_FILL, RED);
    bar(x, y, x + LARGURA_CELULA, y + ALTURA_CELULA);
}

void desenharInimigo(int x, int y, bool ativo) {
    if (ativo) {
        setfillstyle(SOLID_FILL, BLUE);
        bar(x, y, x + LARGURA_CELULA, y + ALTURA_CELULA);
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
    int pg = 0;
    initwindow(LARGURA_TELA, ALTURA_TELA, "Child Pill");

    int personagemX = 0, personagemY = 0;
    int velocidadeX = 0, velocidadeY = 0;
    int tempoRecarrega = 0;
    bool atacando = false;
    int tempoDuracaoAtaque = 0;

    const int NUM_LINHAS = 8;
    const int NUM_COLUNAS = 50;

    // Adicione manualmente a matriz aqui
    int mapa[NUM_LINHAS][NUM_COLUNAS] = {
{0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0},
{0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0},
{0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 1, 1, 1, 1, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 1, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0},
{0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 1, 1, 1, 1, 1, 1, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 1, 1, 1, 0, 0, 0, 0, 0, 0, 0, 0, 3},
{0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 0, 0, 0, 0, 0, 0, 0, 1, 1, 1, 1, 1, 1, 1, 0, 0, 0, 0, 0, 0, 1, 1},
{0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 0, 0, 0, 0, 0, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 0, 0, 0, 0, 1, 1, 1},
{2, 0, 0, 0, 1, 1, 0, 0, 0, 0, 0, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 0, 0, 0, 0, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1},
{1, 1, 1, 4, 1, 1, 1 ,1 ,1, 1, 1, 4, 1, 1, 1, 4, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1}
    };

    const int ELEMENTO_SOLIDO = 9;

    const int INIMIGO = 4;
    const int MAX_INIMIGOS = 3; // Defina o número máximo de inimigos que deseja permitir

    Inimigo inimigos[MAX_INIMIGOS];

    // Inicializa os inimigos
    for (int i = 0; i < MAX_INIMIGOS; ++i) {
        inimigos[i].x = rand() % ((NUM_COLUNAS - 2) * LARGURA_CELULA) + LARGURA_CELULA; // Não nasce na borda esquerda
        inimigos[i].y = rand() % ((NUM_LINHAS - 2) * ALTURA_CELULA) + ALTURA_CELULA;    // Não nasce na borda superior
        inimigos[i].ativo = true;
    }

    bool vitoria = false;

    while (1) {
        trocarPaginas(pg);
        setactivepage(pg);
        cleardevice();

        int cameraX = personagemX - LARGURA_TELA / 2;
        if (cameraX < 0) cameraX = 0;
        if (cameraX > (NUM_COLUNAS * LARGURA_CELULA) - LARGURA_TELA) cameraX = (NUM_COLUNAS * LARGURA_CELULA) - LARGURA_TELA;

        for (int i = 0; i < NUM_LINHAS; ++i) {
            for (int j = 0; j < NUM_COLUNAS; ++j) {
                int posX = j * LARGURA_CELULA - cameraX;
                int posY = i * ALTURA_CELULA;

                if (posX < LARGURA_TELA && posX + LARGURA_CELULA > 0) {
                    switch (mapa[i][j]) {
                        case 0:
                            desenharAreaVazia(posX, posY);
                            break;
                        case 1:
                        case ELEMENTO_SOLIDO:
                            desenharPlataforma(posX, posY);
                            break;
                        case 3:
                            desenharFimDeJogo(posX, posY);
                            if (personagemY == i * ALTURA_CELULA && !vitoria) {
                                vitoria = true;
                            }
                            break;
                    }
                }
            }
        }

        // Verificar colisão com os inimigos
        for (int i = 0; i < MAX_INIMIGOS; ++i) {
            if (inimigos[i].ativo &&
                personagemX < inimigos[i].x + LARGURA_CELULA &&
                personagemX + LARGURA_CELULA > inimigos[i].x &&
                personagemY < inimigos[i].y + ALTURA_CELULA &&
                personagemY + ALTURA_CELULA > inimigos[i].y) {
                inimigos[i].ativo = false;
            }
        }

        personagemX += velocidadeX;
        personagemY += velocidadeY;

        int colunaAtual = personagemX / LARGURA_CELULA;
        int linhaAtual = personagemY / ALTURA_CELULA;

        if (linhaAtual >= 0 && linhaAtual < NUM_LINHAS && colunaAtual >= 0 && colunaAtual < NUM_COLUNAS) {
            if (mapa[linhaAtual][colunaAtual] != 1 && mapa[linhaAtual][colunaAtual] != ELEMENTO_SOLIDO) {
                velocidadeY += GRAVIDADE;
            } else {
                velocidadeY = 0;
                personagemY = linhaAtual * ALTURA_CELULA;
            }
        } else {
            personagemX = 0;
            personagemY = 0;
        }

        int novaColuna = (personagemX + velocidadeX) / LARGURA_CELULA;
        if (novaColuna >= 0 && novaColuna < NUM_COLUNAS) {
            if (mapa[linhaAtual][novaColuna] != 1 && mapa[linhaAtual][novaColuna] != ELEMENTO_SOLIDO) {
                personagemX += velocidadeX;
            }
        }

        if (personagemX < 0) personagemX = 0;
        if (personagemX > (NUM_COLUNAS * LARGURA_CELULA) - LARGURA_CELULA) personagemX = (NUM_COLUNAS * LARGURA_CELULA) - LARGURA_CELULA;

        // Lógica do ataque
        if (tempoRecarrega > 0) {
            tempoRecarrega -= 5;
        }

        // Modificado para verificar a tecla de ataque continuamente
        if (GetKeyState(0x5A) & 0x80 && tempoRecarrega <= 0) {
            atacando = true; // Ativar animação de ataque
            for (int i = 0; i < MAX_INIMIGOS; ++i) {
                if (inimigos[i].ativo &&
                    personagemX + LARGURA_CELULA >= inimigos[i].x &&
                    personagemX <= inimigos[i].x + LARGURA_CELULA &&
                    personagemY + ALTURA_CELULA >= inimigos[i].y &&
                    personagemY <= inimigos[i].y + ALTURA_CELULA) {
                    inimigos[i].ativo = false;
                    break; // Para o loop após atacar um inimigo
                }
            }

            tempoRecarrega = TEMPO_RECARREGA_ATAQUE;
        }

        for (int i = 0; i < MAX_INIMIGOS; ++i) {
            desenharInimigo(inimigos[i].x - cameraX, inimigos[i].y, inimigos[i].ativo);
        }

        desenharPersonagem(personagemX - cameraX, personagemY, atacando);

        setvisualpage(pg);

        if (GetKeyState(VK_LEFT) & 0x80) velocidadeX = -5;
        else if (GetKeyState(VK_RIGHT) & 0x80) velocidadeX = 5;
        else velocidadeX = 0;

        if (GetKeyState(VK_SPACE) & 0x80 && personagemY == ALTURA_TELA - ALTURA_CELULA) {
            velocidadeY = -VELOCIDADE_PULO;
        }

        if (tempoDuracaoAtaque > 0) {
            tempoDuracaoAtaque -= 5;
        } else {
            atacando = false;
        }

        delay(5);
    }

    closegraph();
    return 0;
}
