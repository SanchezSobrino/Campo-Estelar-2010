#ifndef FONT_H
#define FONT_H

// SDL
#include <SDL/SDL.h>
#include <SDL/SDL_image.h>
#include <SDL/SDL_ttf.h>
#include <SDL/SDL_mixer.h>

class Font {
    private:
        TTF_Font* font;
        SDL_Color fg, bg;
        SDL_Surface* surface;
        int sz;

    public:
        Font();

        void WriteSolid(int x, int y, const char* text, ...);
        void WriteShaded(int x, int y, const char* text, ...);
        void WriteBlended(int x, int y, const char* text, ...);

        void WriteSolid(int x, int y, int alpha, const char* text, ...);
        void WriteShaded(int x, int y, int alpha, const char* text, ...);
        void WriteBlended(int x, int y, int alpha, const char* text, ...);

        void WriteDialogue(int fila, int alpha, const char* text, ...);

        void SetForegroundColor(int r, int g, int b);
        void SetBackgroundColor(int r, int g, int b);
        void SetStyle(int style);
        void SetDestination(SDL_Surface* destination);
        void Load(const char* ruta, int size);
        void Load(const char* ruta, int size, int index);

        TTF_Font* GetFont();
};

#endif // FONT_H
