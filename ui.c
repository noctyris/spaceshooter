#include "shared.c"

int drawPlayer(float angle, Coordinate pos) {
    // SDL_RenderDrawLine(renderer, pos.x, pos.y, pos.x + cos(angle) * 20, pos.y + sin(angle) * 20);
    // SDL_RenderDrawLine(renderer, pos.x, pos.y, pos.x + cos(angle + PI / 2) * 10, pos.y + sin(angle + PI / 2) * 10);
    // SDL_RenderDrawLine(renderer, pos.x, pos.y, pos.x + cos(angle - PI / 2) * 10, pos.y + sin(angle - PI / 2) * 10);
    Sint16 vx[] = {
        pos.x + 15 * cos(angle),
        pos.x + 11.25 * cos(angle + 3*PI/4),
        pos.x,
        pos.x + 11.25 * cos(angle + 5*PI/4)
    };
    Sint16 vy[] = {
        pos.y + 15 * sin(angle),
        pos.y + 11.25 * sin(angle + 3*PI/4),
        pos.y,
        pos.y + 11.25 * sin(angle + 5*PI/4)
    };
    filledPolygonRGBA(renderer, vx, vy, 4, 255, 255, 255, 255);
    return 0;
}

int drawBullet(float angle, Coordinate pos) {
    SDL_RenderDrawLine(renderer, pos.x, pos.y, pos.x + cos(angle) * 20, pos.y + sin(angle) * 20);
    return 0;
}