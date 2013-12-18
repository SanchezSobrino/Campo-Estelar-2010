#ifndef TILE_H
#define TILE_H

// SDL
#include <SDL/SDL.h>
#include <SDL/SDL_image.h>
#include <SDL/SDL_ttf.h>
#include <SDL/SDL_mixer.h>

class Tile {
    private:
        SDL_Rect rect;
        SDL_Surface* surface;
        SDL_Surface* destination;

    public:
        Tile();
        ~Tile();

        void Init(int x, int y, int w, int h, const char* ruta, SDL_Rect region, SDL_Surface* destin);

        int GetX();
        int GetY();
        int GetW();
        int GetH();

        void AddPos(int x, int y);
        void AddX(int x);
        void AddY(int y);
        void SetPos(int x, int y);
        void SetX(int x);
        void SetY(int y);

        void SetAlpha(Uint8 val);
        void SetColorKey(int R, int G, int B);
        void SetDestination(SDL_Surface* destin);

        SDL_Surface* GetSurface();
        void Release();

        void Draw();
};

#endif // TILE_H
