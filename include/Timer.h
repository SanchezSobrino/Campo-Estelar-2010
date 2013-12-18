#ifndef TIMER_H
#define TIMER_H

// SDL
#include <SDL/SDL.h>
#include <SDL/SDL_image.h>
#include <SDL/SDL_ttf.h>
#include <SDL/SDL_mixer.h>

class Timer {
    private:
        int startTicks;
        int pausedTicks;
        bool started;
        bool paused;

    public:
        Timer();

        void Start();
        void Stop();
        void Pause();
        void Unpause();

        int GetTicks();
        bool IsStarted();
        bool IsPaused();
};

#endif // TIMER_H
