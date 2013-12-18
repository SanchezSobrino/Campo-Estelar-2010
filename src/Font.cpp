#include "Font.h"

Font::Font() {
    font = NULL;
    surface = NULL;

    fg.r = 255;     bg.r = 0;
    fg.g = 255;     bg.g = 0;
    fg.b = 255;     bg.b = 0;
}

void Font::WriteSolid(int x, int y, const char* text, ...) {
    SDL_Rect pos;
    pos.x = x;
    pos.y = y;

    char* buffer = new char[strlen(text)+1];

    va_list args;
	va_start(args, text);
	vsprintf(buffer, text, args);
	va_end(args);

    SDL_Surface* aux = TTF_RenderText_Solid(font, buffer, fg);
    SDL_BlitSurface(aux, NULL, surface, &pos);

    delete buffer;
    SDL_FreeSurface(aux);
}

void Font::WriteShaded(int x, int y, const char* text, ...) {
    SDL_Rect pos;
    pos.x = x;
    pos.y = y;

    char* buffer = new char[strlen(text)+1];

    va_list args;
	va_start(args, text);
	vsprintf(buffer, text, args);
	va_end(args);

    SDL_Surface* aux = TTF_RenderText_Shaded(font, buffer, fg, bg);
    SDL_BlitSurface(aux, NULL, surface, &pos);

    delete buffer;
    SDL_FreeSurface(aux);
}

void Font::WriteBlended(int x, int y, const char* text, ...) {
    SDL_Rect pos;
    pos.x = x;
    pos.y = y;

    char* buffer = new char[strlen(text)+1];

    va_list args;
	va_start(args, text);
	vsprintf(buffer, text, args);
	va_end(args);

    SDL_Surface* aux = TTF_RenderText_Blended(font, buffer, fg);
    SDL_BlitSurface(aux, NULL, surface, &pos);

    delete buffer;
    SDL_FreeSurface(aux);
}

void Font::WriteSolid(int x, int y, int alpha, const char* text, ...) {
    SDL_Rect pos;
    pos.x = x;
    pos.y = y;

    char* buffer = new char[strlen(text)+1];

    va_list args;
	va_start(args, text);
	vsprintf(buffer, text, args);
	va_end(args);

    SDL_Surface* aux = TTF_RenderText_Solid(font, buffer, fg);
    SDL_SetAlpha(aux, SDL_SRCALPHA | SDL_RLEACCEL, alpha);
    SDL_BlitSurface(aux, NULL, surface, &pos);

    delete buffer;
    SDL_FreeSurface(aux);
}

void Font::WriteShaded(int x, int y, int alpha, const char* text, ...) {
    SDL_Rect pos;
    pos.x = x;
    pos.y = y;

    char* buffer = new char[strlen(text)+1];

    va_list args;
	va_start(args, text);
	vsprintf(buffer, text, args);
	va_end(args);

    SDL_Surface* aux = TTF_RenderText_Shaded(font, buffer, fg, bg);
    SDL_SetAlpha(aux, SDL_SRCALPHA | SDL_RLEACCEL, alpha);
    SDL_BlitSurface(aux, NULL, surface, &pos);

    delete buffer;
    SDL_FreeSurface(aux);
}

void Font::WriteBlended(int x, int y, int alpha, const char* text, ...) {
    SDL_Rect pos;
    pos.x = x;
    pos.y = y;

    char* buffer = new char[strlen(text)+1];

    va_list args;
	va_start(args, text);
	vsprintf(buffer, text, args);
	va_end(args);

    SDL_Surface* aux = TTF_RenderText_Blended(font, buffer, fg);
    SDL_SetAlpha(aux, SDL_SRCALPHA | SDL_RLEACCEL, alpha);
    SDL_BlitSurface(aux, NULL, surface, &pos);

    delete buffer;
    SDL_FreeSurface(aux);
}

void Font::WriteDialogue(int fila, int alpha, const char* text, ...) {
    SDL_Rect pos;
    pos.x = 490;
    pos.y = 30 + sz*fila;

    char* buffer = new char[strlen(text)+1];

    va_list args;
	va_start(args, text);
	vsprintf(buffer, text, args);
	va_end(args);

    SDL_Surface* aux = TTF_RenderText_Blended(font, buffer, fg);
    SDL_SetAlpha(aux, SDL_SRCALPHA | SDL_RLEACCEL, alpha);
    SDL_BlitSurface(aux, NULL, surface, &pos);

    delete buffer;
    SDL_FreeSurface(aux);
}

void Font::SetForegroundColor(int r, int g, int b) {
    fg.r = r;
    fg.g = g;
    fg.b = b;
}

void Font::SetBackgroundColor(int r, int g, int b) {
    bg.r = r;
    bg.g = g;
    bg.b = b;
}

void Font::SetStyle(int style) {
    TTF_SetFontStyle(font, style);
}

void Font::SetDestination(SDL_Surface* destination) {
    surface = destination;
}

void Font::Load(const char* ruta, int size) {
    font = TTF_OpenFont(ruta, size);
    sz = size;

    if(font == NULL) {
        fprintf(stderr, "Error al cargar la fuente: %s\n", ruta);
    }
}

void Font::Load(const char* ruta, int size, int index) {
    font = TTF_OpenFontIndex(ruta, size, index);
    sz = size;

    if(font == NULL) {
        fprintf(stderr, "Error al cargar la fuente: %s\n", ruta);
    }
}

TTF_Font* Font::GetFont() {
    return font;
}
