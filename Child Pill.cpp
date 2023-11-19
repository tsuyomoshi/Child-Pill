#include <graphics.h>
#include <conio.h>
#include <cstdlib>
#include <ctime>
#include <iostream>

const int LARGURA_TELA = 1200;
const int ALTURA_TELA = 800;
const int LARGURA_CELULA = 100;
const int ALTURA_CELULA = 100;
const int TAMANHO_ATAQUE = 50;  // Tamanho da animação de ataque
const int DURACAO_ATAQUE = 100;  // Duração da animação de ataque em milissegundos
const int GRAVIDADE = 1;
const int VELOCIDADE_PULO = 15;
const int TEMPO_RECARREGA_ATAQUE = 300;  // Tempo de recarga do ataque em milissegundos

void desenharPersonagem(int x, int y, bool atacando) {
    setfillstyle(SOLID_FILL, YELLOW);
    bar(x, y, x + LARGURA_CELULA, y + ALTURA_CELULA);

    // Desenha a animação de ataque se estiver atacando
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

    int personagemX = 0, personagemY = 0; // Inicializa a posição do personagem com base na matriz
    int velocidadeX = 0, velocidadeY = 0; // Velocidade do personagem
    int tempoRecarrega = 0;  // Tempo restante para recarregar o ataque

    bool atacando = false;  // Adiciona uma variável para controlar se o personagem está atacando
    int tempoDuracaoAtaque = 0;  // Controla o tempo de exibição da animação de ataque

    const int NUM_LINHAS = 8;
    const int NUM_COLUNAS = 50;

    int mapa[NUM_LINHAS][NUM_COLUNAS] = {
        {0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0},
        {0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 2, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0},
        {0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 1, 1, 1, 1, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 1, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0},
        {0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 1, 1, 1, 1, 1, 1, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 1, 1, 1, 0, 0, 0, 0, 0, 0, 0, 0, 3},
        {0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 0, 0, 0, 0, 0, 0, 0, 1, 1, 1, 1, 1, 1, 1, 0, 0, 0, 0, 0, 0, 1, 1},
        {0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 0, 0, 0, 0, 0, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 0, 0, 0, 0, 1, 1, 1},
        {0, 0, 0, 0, 1, 1, 0, 0, 0, 0, 0, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 0, 0, 0, 0, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1},
        {1, 1, 1, 1, 1, 1, 1 ,1 ,1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1}
    };

    const int ELEMENTO_SOLIDO = 9;

    // Localiza a posição inicial do personagem na matriz
    for (int i = 0; i < NUM_LINHAS; ++i) {
        for (int j = 0; j < NUM_COLUNAS; ++j) {
            if (mapa[i][j] == 2) {
                personagemX = j * LARGURA_CELULA;
                personagemY = i * ALTURA_CELULA;
            }
        }
    }

    bool vitoria = false;  // Adiciona uma variável para controlar a vitória

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

                if (posX < LARGURA_TELA && posX + LARGURA_CELULA > 0) {  // Verifica se a célula está dentro dos limites da tela
                    switch (mapa[i][j]) {
                        case 0:
                            desenharAreaVazia(posX, posY);
                            break;
                        case 1:
                        case ELEMENTO_SOLIDO:  // Elementos sólidos
                            desenharPlataforma(posX, posY);
                            break;
                        case 3:
                            desenharFimDeJogo(posX, posY);
                            if (personagemY == i * ALTURA_CELULA && !vitoria) {
                                vitoria = true;  // Define que o jogador venceu
                            }
                            break;
                        // ... (outras opções de desenho)
                    }
                }
            }
        }

        // Atualizar posição do personagem com base na velocidade
        personagemX += velocidadeX;
        personagemY += velocidadeY;

        // Aplicar gravidade apenas se não estiver em uma plataforma
        int colunaAtual = personagemX / LARGURA_CELULA;
        int linhaAtual = personagemY / ALTURA_CELULA;

        // Verificar colisão vertical
        if (linhaAtual >= 0 && linhaAtual < NUM_LINHAS && colunaAtual >= 0 && colunaAtual < NUM_COLUNAS) {
            if (mapa[linhaAtual][colunaAtual] != 1 && mapa[linhaAtual][colunaAtual] != ELEMENTO_SOLIDO) {
                velocidadeY += GRAVIDADE;
            } else {
                velocidadeY = 0;
                personagemY = linhaAtual * ALTURA_CELULA;
            }
        } else {
            // Se o personagem estiver fora dos limites, coloque-o de volta dentro
            personagemX = 0;
            personagemY = 0;
        }

        // Verificar colisão horizontal
        int novaColuna = (personagemX + velocidadeX) / LARGURA_CELULA;
        if (novaColuna >= 0 && novaColuna < NUM_COLUNAS) {
            if (mapa[linhaAtual][novaColuna] != 1 && mapa[linhaAtual][novaColuna] != ELEMENTO_SOLIDO) {
                personagemX += velocidadeX;
            }
        }

        // Garantir que o personagem não ultrapasse as bordas da matriz
        if (personagemX < 0) personagemX = 0;
        if (personagemX > (NUM_COLUNAS * LARGURA_CELULA) - LARGURA_CELULA) personagemX = (NUM_COLUNAS * LARGURA_CELULA) - LARGURA_CELULA;

        // Lógica do ataque
        if (tempoRecarrega > 0) {
            tempoRecarrega -= 5;  // Diminui o tempo restante para recarregar
        }

        if (GetKeyState(0x5A) & 0x80 && tempoRecarrega <= 0) {
            // Lógica do ataque
            atacando = true;  // Ativar a animação de ataque
            tempoDuracaoAtaque = DURACAO_ATAQUE;  // Define a duração da animação de ataque
            // Implemente o que você deseja que aconteça durante o ataque
            // Por exemplo, definir a variável de dano ou remover inimigos

            // Reinicia o tempo de recarga
            tempoRecarrega = TEMPO_RECARREGA_ATAQUE;
        }

        // Desenhar o personagem por último
        desenharPersonagem(personagemX - cameraX, personagemY, atacando);

        setvisualpage(pg);

        if (GetKeyState(VK_LEFT) & 0x80) velocidadeX = -5;
        else if (GetKeyState(VK_RIGHT) & 0x80) velocidadeX = 5;
        else velocidadeX = 0;

        if (GetKeyState(VK_SPACE) & 0x80 && personagemY == ALTURA_TELA - ALTURA_CELULA) {
            velocidadeY = -VELOCIDADE_PULO;
        }

        // Reduz o tempo de duração da animação de ataque
        if (tempoDuracaoAtaque > 0) {
            tempoDuracaoAtaque -= 5;
        } else {
            atacando = false;  // Desativar a animação de ataque quando a duração acabar
        }

        delay(5); // Adicione um pequeno atraso para controlar a velocidade do loop
    }

    closegraph();
    return 0;
}
