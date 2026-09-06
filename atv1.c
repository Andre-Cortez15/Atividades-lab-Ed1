#include "raylib.h"
#include <stdlib.h>
#include <time.h>

#define LARGURA_JANELA 800
#define ALTURA_JANELA  600
#define TAM_CELULA     40   

typedef struct {
    Vector2 pos;
    Vector2 vel;
    float   raio;
    Color   cor;
} Bola;

int **criarMatriz(int linhas, int colunas) {
    int **matriz = (int **)malloc(linhas * sizeof(int *));
    if (matriz == NULL) return NULL;

    for (int i = 0; i < linhas; i++) {
        matriz[i] = (int *)malloc(colunas * sizeof(int));
        for (int j = 0; j < colunas; j++) {
            matriz[i][j] = 0; 
        }
    }
    return matriz;
}

void liberarMatriz(int **matriz, int linhas) {
    for (int i = 0; i < linhas; i++) {
        free(matriz[i]);
    }
    free(matriz);
}

void desenharMatriz(int **matriz, int linhas, int colunas) {
    for (int i = 0; i < linhas; i++) {
        for (int j = 0; j < colunas; j++) {
            Color cor = (matriz[i][j] == 1) ? (Color){50, 120, 180, 255} 
                                            : (Color){15, 30, 55, 255};
            
            DrawRectangle(j * TAM_CELULA, i * TAM_CELULA,
                          TAM_CELULA - 2, TAM_CELULA - 2, cor);
        }
    }
}

Bola *criarBolas(int quantidade) {
    Bola *bolas = (Bola *)malloc(quantidade * sizeof(Bola));
    if (bolas == NULL) return NULL;

    for (int i = 0; i < quantidade; i++) {
        Bola *b = (bolas + i);
        b->pos = (Vector2){ (float)GetRandomValue(50, LARGURA_JANELA - 50),
                            (float)GetRandomValue(50, ALTURA_JANELA - 50) };
        b->vel = (Vector2){ (float)GetRandomValue(-4, 4),
                            (float)GetRandomValue(-4, 4) };
        if (b->vel.x == 0) b->vel.x = 2; // Evita bola parada
        if (b->vel.y == 0) b->vel.y = 2;
        b->raio = (float)GetRandomValue(10, 20);
        b->cor  = (Color){ GetRandomValue(100,255), GetRandomValue(100,255),
                            GetRandomValue(100,255), 255 };
    }
    return bolas;
}

void atualizarBola(Bola *b) {
    b->pos.x += b->vel.x;
    b->pos.y += b->vel.y;

    if (b->pos.x - b->raio < 0 || b->pos.x + b->raio > LARGURA_JANELA)
        b->vel.x *= -1;
    if (b->pos.y - b->raio < 0 || b->pos.y + b->raio > ALTURA_JANELA)
        b->vel.y *= -1;
}

int main(void) {
    srand((unsigned int)time(NULL));

    InitWindow(LARGURA_JANELA, ALTURA_JANELA, "Exercicios 1 e 2 - Raylib");
    SetTargetFPS(60);

    int linhas   = ALTURA_JANELA / TAM_CELULA;
    int colunas  = LARGURA_JANELA / TAM_CELULA;
    int **grade  = criarMatriz(linhas, colunas);
    int quantidadeBolas = 12;
    Bola *bolas = criarBolas(quantidadeBolas);

    int celulasVisitadas = 0;

    while (!WindowShouldClose()) {
    
//exercicio 1

        if (IsKeyPressed(KEY_SPACE)) {
            quantidadeBolas++;
            bolas = (Bola *) realloc(bolas, quantidadeBolas * sizeof(Bola));

            if (bolas != NULL) {
                Bola *novaBola = bolas + (quantidadeBolas - 1);
                novaBola->pos = (Vector2){ (float)GetRandomValue(50, LARGURA_JANELA - 50),
                                           (float)GetRandomValue(50, ALTURA_JANELA - 50) };
                novaBola->vel = (Vector2){ (float)GetRandomValue(-4, 4),
                                           (float)GetRandomValue(-4, 4) };
                if (novaBola->vel.x == 0) novaBola->vel.x = 2;
                if (novaBola->vel.y == 0) novaBola->vel.y = 2;
                novaBola->raio = (float)GetRandomValue(10, 20);
                novaBola->cor  = (Color){ GetRandomValue(100, 255), GetRandomValue(100, 255),
                                           GetRandomValue(100, 255), 255 };
            }
        }

        if (IsKeyPressed(KEY_BACKSPACE) && quantidadeBolas > 0) {
            quantidadeBolas--;
            if (quantidadeBolas > 0) {
                bolas = (Bola *) realloc(bolas, quantidadeBolas * sizeof(Bola));
            } else {
                free(bolas);
                bolas = NULL;
            }
        }

        for (int i = 0; i < quantidadeBolas; i++) {
            atualizarBola(bolas + i);

            //exercicio 2
            Bola *b = bolas + i;
            int col = (int)(b->pos.x / TAM_CELULA);
            int lin = (int)(b->pos.y / TAM_CELULA);

            if (lin >= 0 && lin < linhas && col >= 0 && col < colunas) {
                if (grade[lin][col] == 0) {
                    grade[lin][col] = 1;      
                    celulasVisitadas++;       
                }
            }
        }

        BeginDrawing();
            ClearBackground(RAYWHITE);
            desenharMatriz(grade, linhas, colunas);
            for (int i = 0; i < quantidadeBolas; i++) {
                DrawCircleV(bolas[i].pos, bolas[i].raio, bolas[i].cor);
            }

            DrawText(TextFormat("Bolas ativas: %d  (ESPACO: +1 | BACKSPACE: -1)", quantidadeBolas), 
                     10, 10, 18, WHITE);
            
            DrawText(TextFormat("Celulas visitadas: %d / %d", celulasVisitadas, linhas * colunas), 
                     10, 32, 18, YELLOW);

            DrawText("Pressione ESC para sair", 10, ALTURA_JANELA - 25, 16, WHITE);

        EndDrawing();
    }
    if (bolas != NULL) {
        free(bolas);
    }
    liberarMatriz(grade, linhas);

    CloseWindow();
    return 0;
}