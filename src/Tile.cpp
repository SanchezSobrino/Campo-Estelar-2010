#include "Tile.h"

Tile::Tile() {
    surface = NULL;
    destination = NULL;
}

Tile::~Tile() {
    SDL_FreeSurface(surface);
}

void Tile::Init(int x, int y, int w, int h, const char* ruta, SDL_Rect region, SDL_Surface* destin) {
    rect.x = x;
    rect.y = y;
    rect.w = w;
    rect.h = h;

    SDL_Surface* aux = NULL;
    aux = IMG_Load(ruta);

    destination = destin;

    if(aux != NULL) {
        surface = SDL_DisplayFormat(aux);

        SDL_FreeSurface(aux);
    }
    else {
        fprintf(stderr, "Error al cargar el tile: %s\n", ruta);
    }
}

int Tile::GetX() {
    return rect.x;
}

int Tile::GetY() {
    return rect.y;
}

int Tile::GetW() {
    return rect.w;
}

int Tile::GetH() {
    return rect.h;
}

void Tile::AddPos(int x, int y) {
    rect.x += x;
    rect.y += y;
}

void Tile::AddX(int x) {
    rect.x += x;
}

void Tile::AddY(int y) {
    rect.y += y;
}

void Tile::SetPos(int x, int y) {
    rect.x = x;
    rect.y = y;
}

void Tile::SetX(int x) {
    rect.x = x;
}

void Tile::SetY(int y) {
    rect.y = y;
}

void Tile::SetAlpha(Uint8 val) {
    SDL_SetAlpha(surface, SDL_SRCALPHA | SDL_RLEACCEL, val);
}

void Tile::SetColorKey(int R, int G, int B) {
    SDL_SetColorKey(surface, SDL_SRCCOLORKEY | SDL_RLEACCEL, SDL_MapRGB(surface->format, R, G, B));
}

void Tile::SetDestination(SDL_Surface* destin) {
    destination = destin;
}

SDL_Surface* Tile::GetSurface() {
    return surface;
}

void Tile::Release() {
	SDL_FreeSurface(surface);
}

void Tile::Draw() {
    SDL_Rect position = {rect.x, rect.y, rect.w, rect.h};

    SDL_BlitSurface(surface, NULL, destination, &position);
}
