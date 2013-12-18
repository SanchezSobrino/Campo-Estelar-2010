#ifndef MAP_H
#define MAP_H

// SDL
#include <SDL/SDL.h>
#include <SDL/SDL_image.h>
#include <SDL/SDL_ttf.h>
#include <SDL/SDL_mixer.h>

class Map {
    private:
        SDL_Rect rect, clip, pos;
        SDL_Surface* surface;
        SDL_Surface* destination;
        int velX, velY;

    public:
        Map(int x, int y, int w, int h, int xVel, int yVel, const char* ruta, SDL_Rect region, SDL_Surface* destin);
        Map();
        ~Map();

        void Init(int x, int y, int w, int h, int xVel, int yVel, const char* ruta, SDL_Rect region, SDL_Surface* destin);
};

#endif // MAP_H
