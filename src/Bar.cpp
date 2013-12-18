#include "Bar.h"

Bar::Bar() {
    destination = NULL;
    numBars = 0;
}

void Bar::Draw(int val) {
    if(val >= 0) {
        rect.w = ((float)val/(float)maximo) * ancho;
        SDL_Rect position = rect;
        SDL_FillRect(destination, &position, SDL_MapRGB(destination->format, color.r, color.g, color.b));
    }
}

void Bar::Create(int x, int y, int w, int h, int max, SDL_Surface* dest) {
    rect.x = x;
    rect.y = y;
    rect.w = w;
    rect.h = h;

    maximo = max;
    ancho = w;

    destination = dest;
}

void Bar::SetRect(Sint16 x, Sint16 y, Sint16 w, Sint16 h) {
  rect.x = x;
  rect.y = y;
  rect.w = w;
  rect.h = h;
}

void Bar::SetMax(int val) {
	maximo = val;
}

void Bar::SetX(int x) {
    rect.x = x;
}

void Bar::SetY(int y) {
    rect.y = y;
}

void Bar::SetW(int w) {
    rect.w = w;
}

void Bar::SetH(int h) {
    rect.h = h;
}

void Bar::SetColor(Uint8 r, Uint8 g, Uint8 b) {
    color = {r, g, b};
}

void Bar::Increase(int val) {
    return;
}

void Bar::AddW(int w) {
    rect.w += w;
}

void Bar::AddH(int h) {
    rect.h += h;
}

void Bar::IncreaseNumBars(){
    numBars++;
}

void Bar::SetNumBars(int val) {
    numBars = val;
}

SDL_Rect Bar::GetRect() {
    return rect;
}

int Bar::GetX() {
    return rect.x;
}

int Bar::GetY() {
    return rect.y;
}

int Bar::GetW() {
    return rect.w;
}

int Bar::GetH() {
    return rect.h;
}

int Bar::GetNumBars() {
    return numBars;
}

SDL_Color Bar::GetColor() {
    return color;
}

void Bar::SetDestination(SDL_Surface* sur) {
    destination = sur;
}
