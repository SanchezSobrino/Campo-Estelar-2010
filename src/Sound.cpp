#include "Sound.h"

Sound::Sound() {
    temp = NULL;
}

Sound::~Sound() {
    Mix_FreeChunk(temp);
}

void Sound::Load(const char* ruta, int val) {
    temp = Mix_LoadWAV(ruta);
    channel = val;

    if(temp == NULL) {
        fprintf(stderr, "Error al cargar el sonido: %s\n", ruta);
        SDL_Quit();
    }
}

void Sound::Play() {
    Mix_PlayChannel(channel, temp, 0);
}

void Sound::Pause() {
    Mix_Pause(channel);
}

void Sound::Resume() {
    Mix_Resume(channel);
}

void Sound::Stop() {
    Mix_HaltChannel(channel);
}

void Sound::Volume(int val) {
    Mix_VolumeChunk(temp, val);
}

void Sound::VolumeAll(int val) {
    Mix_Volume(-1, val);
}

int Sound::IsPlaying() {
    return Mix_Playing(channel);
}

Mix_Chunk* Sound::GetChunk() {
    return temp;
}
