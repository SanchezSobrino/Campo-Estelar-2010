#ifndef SPRITE_H
#define SPRITE_H

// SDL
#include <SDL/SDL.h>
#include <SDL/SDL_image.h>
#include <SDL/SDL_ttf.h>
#include <SDL/SDL_mixer.h>

class Sprite {
    private:
        SDL_Rect rect, clip, pos;
        SDL_Rect* offset;
        SDL_Surface* surface;
        SDL_Surface* destination;
        float velX, velY, maxVelX, maxVelY, accelX, accelY;
        int alpha;
        int status;
        int speed, frame, frames, lastUpdate, lastBlinkUpdate, cont, delay, shots, maxShots, score;
        int hp, mp;
        float cast;
        bool enable, colision, ocupado, damaged, stop;
        int hueco, type, item;
        float angleX, angleY;
        int lvl;

    public:
        Sprite();
        ~Sprite();

        void Init(int x, int y, int w, int h, int frames, int vel, int xVel, int yVel, const char* ruta, SDL_Rect region, SDL_Surface* destin);

        int GetX();
        int GetY();
        int GetLvl();
        int GetAngleX();
        int GetAngleY();
        int GetOffsetX();
        int GetOffsetY();
        int GetOffsetW();
        int GetOffsetH();
        float GetVelX();
        float GetVelY();
        float GetAccelX();
        float GetAccelY();
        int GetStatus();
        int GetMaxFrames();
        int GetFrame();
        int GetMaxVelX();
        int GetMaxVelY();

        void SetHP(int val);
        void SetMP(int val);
        void AddHP(int val);
        void AddMP(int val);
        void SetLvl(int val);
        void AddLvl(int val);
        void SetScore(int val);
        void SetCast(float val);
        void AddCast(float val);
        int GetHP();
        int GetMP();
        float GetCast();
        int GetScore();

		bool enableShield(bool val);
        bool Enable(bool val);
        bool Enable();
        bool Colision(bool col);
        bool Colision();
        bool Ocupado(bool val);
        bool Ocupado();
        bool Damaged();
        bool Damaged(bool val);

        void SetItem(int val);
        int GetItem();

        void SetType(int val);
        int GetType();
        void SetHueco(int val);
        int GetHueco();

        void Blink();
        int IncreaseCont();
        void ResetCont();
        int GetCont();

        void Shot();
        void SetMaxBullets(int max);
        int GetBullets();

        void SetActionDelay(int val);
        void ResetActionDelay();
        int GetActionDelay();

        bool Stop(bool val);
        bool Stop();

        void AddPos(int x, int y);
        void AddX(int x);
        void AddY(int y);
        void SetPos(float x, float y);
        void SetAngle(float x, float y);
        void SetX(int x);
        void SetY(int y);
        void SetOffsetX(int x);
        void SetOffsetY(int y);
        void SetOffsetW(int w);
        void SetOffsetH(int h);
        void SetSize(int w, int h);
        void SetAccel(float x, float y);
        void SetAccelX(float x);
        void SetAccelY(float y);
        void SetVel(float x, float y);
        void SetVelX(float x);
        void SetVelY(float y);

        void SetAlpha(Uint8 val);
        Uint8 GetAlpha();

        void SetColorKey(int R, int G, int B);
        void SetDestination(SDL_Surface* destin);
        void SetStatus(int stats);

		void Release();
        SDL_Surface* GetSurface();
        SDL_Rect GetRect();

        void Draw();
        void Draw(int nFrame);
        void ShowParticles();

        bool CheckCollision(Sprite &spr);
};

#endif // SPRITE_H
