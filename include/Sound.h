#ifndef SOUND_H
#define SOUND_H

// SDL
#include <SDL/SDL.h>
#include <SDL/SDL_image.h>
#include <SDL/SDL_ttf.h>
#include <SDL/SDL_mixer.h>

class Sound {
    private:
        Mix_Chunk* temp;
        int channel;

    public:
        Sound();
        ~Sound();

        void Load(const char* ruta, int val);

        void Play();
        void Pause();
        void Resume();
        void Stop();
        void Volume(int val);
        void VolumeAll(int val);

        int IsPlaying();

        Mix_Chunk* GetChunk();
};

#endif // SOUND_H
