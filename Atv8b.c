#include "raylib.h"
#include "entidade.h"
#include <stdlib.h>

int main(void) {
    // Inicializa a janela
    InitWindow(800, 600, "Atividade 8b - Reuso de Modulos");
    SetTargetFPS(60);

    // Criando 3 entidades de tipos diferentes reutilizando o módulo
    Entidade *jogador = entidadeCriar(ENTIDADE_JOGADOR, (Vector2){ 400, 300 });
    Entidade *inimigo = entidadeCriar(ENTIDADE_INIMIGO, (Vector2){ 200, 200 });
    Entidade *item = entidadeCriar(ENTIDADE_ITEM, (Vector2){ 600, 400 });

    while (!WindowShouldClose()) {
        BeginDrawing();
            ClearBackground(RAYWHITE);
            entidadeDesenhar(jogador);
            entidadeDesenhar(inimigo);
            entidadeDesenhar(item);
            
            DrawText("Programa 8b: Reaproveitando o modulo entidade!", 180, 50, 20, DARKGRAY);
            DrawText("Pressione ESC para sair", 180, 80, 16, GRAY);
        EndDrawing();
    }

    free(jogador);
    free(inimigo);
    free(item);

    CloseWindow();
    return 0;
}