#include "ui.c"

#define MAX_SPEED 4
#define MAX_MOMENTUM 0.02
#define HISTORY_SIZE 50
#define EDGE_THRESHOLD 100

int main() {
    init();


    int running = 1;
    Coordinate pos = {0, HEIGHT/2};
    float angle = 0;
    float vX = -(WIDTH/2 - 7.5)*log(0.99) + 0.01, vY = 0;
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

        if (pos.x < 0) pos.x = WIDTH;
        if (pos.x > WIDTH) pos.x = 0;
        if (pos.y < 0) pos.y = HEIGHT;
        if (pos.y > HEIGHT) pos.y = 0;

        history[history_index] = pos;
        history_index = (history_index + 1) % HISTORY_SIZE;
        if (history_size < HISTORY_SIZE) history_size++;

        SDL_SetRenderDrawColor(renderer, 0, 0, 0, 255);
        SDL_RenderClear(renderer);

        drawPlayer(angle, pos);


        for (int i = 0; i < history_size - 1; i++) {
            int real_index_current = (history_index - 1 - i + HISTORY_SIZE) % HISTORY_SIZE;
            int real_index_next = (history_index - 1 - (i + 1) + HISTORY_SIZE) % HISTORY_SIZE;

            Coordinate pos_current = history[real_index_current];
            Coordinate pos_next = history[real_index_next];

            float dx = pos_current.x - pos_next.x;
            float dy = pos_current.y - pos_next.y;
            float distance = sqrt(dx * dx + dy * dy);

            if (distance > EDGE_THRESHOLD) {
                continue;
            }

            Uint8 color_value = 255 - (i * 255 / HISTORY_SIZE);
            SDL_SetRenderDrawColor(renderer, color_value, color_value, color_value, 255);

            SDL_RenderDrawLine(renderer,
                            pos_current.x, pos_current.y,
                            pos_next.x, pos_next.y);
        }

        SDL_RenderPresent(renderer);
    }

    return 0;
}