#include "Music.h"

Music::Music() {
    temp = NULL;
}

Music::~Music() {
    Mix_FreeMusic(temp);
}

void Music::Load(const char* ruta, int rep) {
    temp = Mix_LoadMUS(ruta);

    if(temp == NULL) {
        fprintf(stderr, "Error al cargar la cancion: %s\n", ruta);
        SDL_Quit();
    }

    repeat = rep;
}

void Music::Play() {
    Mix_PlayMusic(temp, repeat);
}

void Music::Pause() {
    Mix_PauseMusic();
}

void Music::Resume() {
    Mix_ResumeMusic();
}

void Music::Stop() {
    Mix_HaltMusic();
}

void Music::Volume(int val) {
    Mix_VolumeMusic(val);
}

Mix_Music* Music::GetMusic() {
    return temp;
}
