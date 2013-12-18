#include "Pixel.h"

extern SDL_Surface* screen;

Pixel::Pixel() {
	x = 1; y = 1;
	ang = 1; rad = 1;
	speed = 1;
	color = SDL_MapRGB(screen->format, 0xFF, 0xFF, 0xFF);
}

void Pixel::Draw() {
	int bpp = screen->format->BytesPerPixel;

	 Uint8* p = (Uint8*)screen->pixels + y * screen->pitch + x * bpp;

	 switch(bpp) {
		case 1:
			*p = color;
			break;
		case 2:
			*(Uint16*)p = color;
			break;
		case 3:
			if(SDL_BYTEORDER == SDL_BIG_ENDIAN) {
				p[0] = (color >> 16) & 0xff;
				p[1] = (color >> 8) & 0xff;
				p[2] = color & 0xff;
			}
			else {
				p[0] = color & 0xff;
				p[1] = (color >> 8) & 0xff;
				p[2] = (color >> 16) & 0xff;
			}
			break;
		case 4:
			*(Uint32*)p = color;
			break;
	}
}

void Pixel::SetColor(int r, int g, int b) {
	color = SDL_MapRGB(screen->format, r, g, b);
}
