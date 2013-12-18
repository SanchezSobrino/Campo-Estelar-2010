#ifndef BAR_H
#define BAR_H

// SDL
#include <SDL/SDL.h>
#include <SDL/SDL_image.h>
#include <SDL/SDL_ttf.h>
#include <SDL/SDL_mixer.h>

class Bar {
    private:
        SDL_Rect rect;
        SDL_Surface* destination;
        SDL_Color color;
        int maximo, ancho;
        int numBars;

    public:
        Bar();

        void Draw(int hp);
        void Create(int x, int y, int w, int h, int max, SDL_Surface* dest);

        void SetRect(Sint16 x, Sint16 y, Sint16 w, Sint16 h);
        void SetMax(int val);
        void SetX(int x);
        void SetY(int y);
        void SetW(int w);
        void SetH(int h);
        void AddW(int w);
        void AddH(int h);
        void IncreaseNumBars();
        void SetNumBars(int val);
        void SetColor(Uint8 r, Uint8 g, Uint8 b);

        void Increase(int val);

        SDL_Rect GetRect();
        int GetX();
        int GetY();
        int GetW();
        int GetH();
        int GetNumBars();
        SDL_Color GetColor();

        void SetDestination(SDL_Surface* surface);
};

#endif // BAR_H
