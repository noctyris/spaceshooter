#include "ui.c"

#define MAX_SPEED 4
#define MAX_MOMENTUM 0.02
#define HISTORY_SIZE 20
#define EDGE_THRESHOLD 100

int main() {
    init();

    int running = 1;
    Coordinate pos = {0, 300};
    float angle = 0;
    float vX = 3, vY = 0;
    float momentum = 0;
    
    Coordinate history[HISTORY_SIZE];
    int history_index = 0;
    int history_size = 0;

    while (running) {
        while (SDL_PollEvent(&event)) {
            if (event.type == SDL_QUIT) running = 0;
        }

        Uint8 const *keys = SDL_GetKeyboardState(NULL);

        if (keys[SDL_SCANCODE_UP]) {
            vX += cos(angle) * 0.1;
            vY += sin(angle) * 0.1;
        }
        if (keys[SDL_SCANCODE_DOWN]) {
            vX -= cos(angle) * 0.1;
            vY -= sin(angle) * 0.1;
        }

        float speed = sqrt(vX * vX + vY * vY);
        if (speed > MAX_SPEED) {
            vX = (vX / speed) * MAX_SPEED;
            vY = (vY / speed) * MAX_SPEED;
        }

        if (keys[SDL_SCANCODE_LEFT]) momentum -= 0.0025;
        if (keys[SDL_SCANCODE_RIGHT]) momentum += 0.0025;
        angle += momentum;
        momentum *= 0.95;

        if (!keys[SDL_SCANCODE_UP] && !keys[SDL_SCANCODE_DOWN]) {
            vX *= 0.99;
            vY *= 0.99;
        }
        if (fabs(vX) + fabs(vY) < 0.01) vX = 0, vY = 0;

        pos.x += vX;
        pos.y += vY;

        // Gestion des limites de l'écran
        if (pos.x < 0) pos.x = WIDTH;
        if (pos.x > WIDTH) pos.x = 0;
        if (pos.y < 0) pos.y = HEIGHT;
        if (pos.y > HEIGHT) pos.y = 0;

        // Gestion de l'historique
        history[history_index] = pos;
        history_index = (history_index + 1) % HISTORY_SIZE;
        if (history_size < HISTORY_SIZE) history_size++;

        // Effacement de l'écran
        SDL_SetRenderDrawColor(renderer, 0, 0, 0, 255);
        SDL_RenderClear(renderer);

        // Dessin du joueur
        drawPlayer(angle, pos);


        // Dessin de l'historique (traînée sous forme de trait)
        for (int i = 0; i < history_size - 1; i++) {
            // Calcul des index réels dans le tableau circulaire
            int real_index_current = (history_index - 1 - i + HISTORY_SIZE) % HISTORY_SIZE;
            int real_index_next = (history_index - 1 - (i + 1) + HISTORY_SIZE) % HISTORY_SIZE;

            // Récupération des positions actuelles et suivantes
            Coordinate pos_current = history[real_index_current];
            Coordinate pos_next = history[real_index_next];

            // Calcul de la distance entre les deux positions
            float dx = pos_current.x - pos_next.x;
            float dy = pos_current.y - pos_next.y;
            float distance = sqrt(dx * dx + dy * dy);

            // Si la distance est trop grande, ne pas tracer de ligne (transition entre les bords)
            if (distance > EDGE_THRESHOLD) {
                continue; // Saute cette itération
            }

            // Couleur dégradée basée sur l'ancienneté de la position
            Uint8 color_value = 255 - (i * 255 / HISTORY_SIZE);
            SDL_SetRenderDrawColor(renderer, color_value, color_value, color_value, 255);

            // Dessin d'une ligne entre deux positions consécutives
            SDL_RenderDrawLine(renderer,
                            pos_current.x, pos_current.y,
                            pos_next.x, pos_next.y);
        }

        // Affichage du rendu
        SDL_RenderPresent(renderer);
    }

    return 0;
}