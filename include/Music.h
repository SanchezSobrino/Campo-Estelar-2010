#ifndef MUSIC_H
#define MUSIC_H

// SDL
#include <SDL/SDL.h>
#include <SDL/SDL_image.h>
#include <SDL/SDL_ttf.h>
#include <SDL/SDL_mixer.h>

class Music {
    private:
        Mix_Music* temp;
        int repeat;

    public:
        Music();
        ~Music();

        void Load(const char* ruta, int rep);

        void Play();
        void Pause();
        void Resume();
        void Stop();
        void Volume(int val);

        Mix_Music* GetMusic();
};

#endif // MUSIC_H
