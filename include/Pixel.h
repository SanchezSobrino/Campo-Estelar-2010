#ifndef PIXEL_H
#define PIXEL_H

// SDL
#include <SDL/SDL.h>
#include <SDL/SDL_image.h>
#include <SDL/SDL_ttf.h>
#include <SDL/SDL_mixer.h>

class Pixel {
	private:
		int x, y;
		int ang, rad;
		int speed;
		Uint32 color;

	public:
		Pixel();

		void Draw();

		void SetX(int val) { x = val; }
		void SetY(int val) { y = val; }
		void SetRad(int val) { rad = val; }
		void SetAng(int val) { ang = val; }
		void SetSpeed(int val) { speed = val; }
		void SetColor(int r, int g, int b);

		void AddRad(int val) { rad += val; }

		int GetX() { return x; }
		int GetY() { return y; }
		int GetSpeed() { return speed; }
		int GetAng() { return ang; }
		int GetRad() { return rad; }
};

#endif // PIXEL_H
