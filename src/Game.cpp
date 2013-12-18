#include "Game.h"

Game::Game() {
    title = NULL;
    icon = NULL;
}

void Game::Init(const char* title1, const char* icon1, Uint32 flagsSDL, Uint16 flagsLibs) {
    SDL_Init(flagsSDL);
    SDL_WM_SetCaption(title1, icon1);

    title = new char[strlen(title1)];
    sprintf(title, "%s", title1);

    if(icon1 != NULL) {
        icon = new char[strlen(icon1)];
        sprintf(icon, "%c", icon1[1]);
    }

    difficulty = 1;

    switch(flagsLibs) {
        case 1:
            TTF_Init();
            break;
        case 2:
            Mix_OpenAudio(44100, AUDIO_S16SYS, 2, 4096);
            break;
        default:
            TTF_Init();
            Mix_OpenAudio(44100, AUDIO_S16SYS, 2, 4096);
    }
}

SDL_Surface* Game::SetVideoMode(int width, int height, int bitPerPixel, Uint32 flags) {
    w = width;
    h = height;
    bpp = bitPerPixel;
    return SDL_SetVideoMode(width, height, bitPerPixel, flags);
}

int Game::ToggleFullWindowedScreen(SDL_Surface* surface) {
    Uint32 flags = surface->flags;
    surface = SDL_SetVideoMode(0, 0, 0, surface->flags ^ SDL_FULLSCREEN);

    if(surface == NULL) {
        surface = SDL_SetVideoMode(0, 0, 0, flags);
        return -1;
    }
    else {
        return 0;
    }
}

void Game::MainFocus(bool var) {
    SDL_WM_GrabInput(var?SDL_GRAB_ON:SDL_GRAB_OFF);
}

void Game::ShowCursor(bool var) {
    SDL_ShowCursor(var?SDL_ENABLE:SDL_DISABLE);
}

void Game::SetDifficulty(int val) {
	difficulty = val;
}

int Game::GetDifficulty() {
	return difficulty;
}

void Game::SetScore(int val) {
    score = val;
}

void Game::AddScore(int val) {
    score += val;
}

int Game::GetScore() {
    return score;
}

int Game::Render(SDL_Surface* surface) {
    return SDL_Flip(surface);
}

int Game::FillRect(SDL_Surface* dst, SDL_Rect* dstrect, Uint32 color) {
    return SDL_FillRect(dst, dstrect, color);
}

void Game::Delay(Uint32 ms) {
    SDL_Delay(ms);
}

char* Game::GetTitle() {
    return title;
}

char* Game::GetIcon() {
    return icon;
}

int Game::GetWidth() {
    return w;
}

int Game::GetHeight() {
    return h;
}

int Game::GetBPP() {
    return bpp;
}

void Game::Quit() {
    TTF_Quit();
    SDL_Quit();
    printf("### Todo ha salido correctamente ###");
}
