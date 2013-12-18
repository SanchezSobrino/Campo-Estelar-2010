#ifndef GAME_H
#define GAME_H

// SDL
#include <SDL/SDL.h>
#include <SDL/SDL_image.h>
#include <SDL/SDL_ttf.h>
#include <SDL/SDL_mixer.h>

class Game {
    private:
        int w, h, bpp;
        char* title;
        char* icon;
        int score;
        int difficulty;

    public:
        Game();

        void Init(const char* title1, const char* icon1, Uint32 flagsSDL, Uint16 flagsLibs);
        SDL_Surface* SetVideoMode(int width, int height, int bitPerPixel, Uint32 flags);

        void SetCaption(const char* title1, const char* icon1);
        int ToggleFullWindowedScreen(SDL_Surface* surface);
        void MainFocus(bool var);
        void ShowCursor(bool var);

        void SetDifficulty(int val);
        int GetDifficulty();

        void SetScore(int val);
        void AddScore(int val);
        int GetScore();

        int Render(SDL_Surface* surface);
        int FillRect(SDL_Surface* dst, SDL_Rect* dstrect, Uint32 color);

        void Delay(Uint32 ms);

        char* GetTitle();
        char* GetIcon();
        int GetWidth();
        int GetHeight();
        int GetBPP();

        void Quit();
};

#endif // GAME_H
