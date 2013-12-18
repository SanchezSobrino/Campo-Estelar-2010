#include "Sprite.h"

Sprite::Sprite() {
    velX = 1;
    velY = 1;
    enable = true;
    cont = 0;
    shots = 0;
    colision = true;
    ocupado = false;
    hueco = -1;
    damaged = false;

    surface = NULL;
    offset = NULL;
}

Sprite::~Sprite() {
    SDL_FreeSurface(surface);
    delete offset;
}

void Sprite::Init(int x, int y, int w, int h, int fram, int vel, int xVel, int yVel, const char* ruta, SDL_Rect region, SDL_Surface* destin) {
    rect.x = x;
    rect.y = y;
    rect.w = w;
    rect.h = h;
    velX = xVel;
    velY = yVel;
    maxVelX = xVel;
    maxVelY = yVel;
    clip = region;
    enable = true;
    cont = 0;
    shots = 0;
    lvl = 1;

    // Animation
    frame = 0;
    frames = fram;
    speed = vel;
    status = 0;
    offset = new SDL_Rect[fram];

    for(int i = 0; i < fram; i++) {
        offset[i].x = region.w*i;
        offset[i].y = region.y;
        offset[i].w = region.w;
        offset[i].h = region.h;
    }

    SDL_Surface* aux = NULL;
    aux = IMG_Load(ruta);

    destination = destin;

    if(aux != NULL) {
        surface = SDL_DisplayFormat(aux);

        SDL_FreeSurface(aux);

        if(surface != NULL) {
            SDL_SetColorKey(surface, SDL_SRCCOLORKEY | SDL_RLEACCEL, SDL_MapRGB(surface->format, 0xFF, 0x00, 0xFF));
        }
    }
    else {
        fprintf(stderr, "Error al cargar el sprite: %s\n", ruta);
        SDL_Quit();
    }
}

int Sprite::GetX() {
    return pos.x;
}

int Sprite::GetY() {
    return pos.y;
}

int Sprite::GetLvl() {
	return lvl;
}

int Sprite::GetAngleX() {
    return angleX;
}

int Sprite::GetAngleY() {
    return angleY;
}

int Sprite::GetOffsetX() {
    return rect.x;
}

int Sprite::GetOffsetY() {
    return rect.y;
}

int Sprite::GetOffsetW() {
    return rect.w;
}

int Sprite::GetOffsetH() {
    return rect.h;
}

float Sprite::GetAccelX() {
    return accelX;
}

float Sprite::GetAccelY() {
    return accelY;
}

float Sprite::GetVelX() {
    return velX;
}

float Sprite::GetVelY() {
    return velY;
}

int Sprite::GetStatus() {
    return status;
}

int Sprite::GetMaxFrames() {
    return frames;
}

int Sprite::GetFrame() {
    return frame;
}

void Sprite::SetScore(int val) {
	score = val;
}

void Sprite::SetLvl(int val) {
	lvl = val;
}

void Sprite::AddLvl(int val) {
	lvl += val;
}

void Sprite::SetHP(int val) {
    hp = val;
}

void Sprite::SetMP(int val) {
    mp = val;
}

void Sprite::AddHP(int val) {
    hp += val;
}

void Sprite::AddMP(int val) {
    mp += val;
}

void Sprite::SetCast(float val) {
    cast = val;
}

void Sprite::AddCast(float val) {
    cast += val;
}

int Sprite::GetHP() {
    return hp;
}

int Sprite::GetMP() {
    return mp;
}

float Sprite::GetCast() {
    return cast;
}

int Sprite::GetScore() {
	return score;
}

bool Sprite::Enable(bool val) {
    enable = val;

    return enable;
}

bool Sprite::Enable() {
    return enable;
}

bool Sprite::Colision(bool val) {
    colision = val;

    return colision;
}

bool Sprite::Colision() {
    return colision;
}

bool Sprite::Ocupado(bool val) {
	ocupado = val;

	return ocupado;
}

bool Sprite::Ocupado() {
	return ocupado;
}

bool Sprite::Damaged(bool val) {
	damaged = val;

	return damaged;
}

bool Sprite::Damaged() {
	return damaged;
}

void Sprite::SetItem(int val) {
	item = val;
}

int Sprite::GetItem() {
	return item;
}

void Sprite::SetType(int val) {
    type = val;
}

int Sprite::GetType() {
    return type;
}

void Sprite::SetHueco(int val) {
    hueco = val;
}

int Sprite::GetHueco() {
    return hueco;
}

void Sprite::Blink() {
    if(lastBlinkUpdate + 75 < (int)SDL_GetTicks()) {
        SDL_SetAlpha(surface, SDL_SRCALPHA | SDL_RLEACCEL, 64);
        lastBlinkUpdate = SDL_GetTicks();
    }
    else {
        SDL_SetAlpha(surface, SDL_SRCALPHA | SDL_RLEACCEL, 255);
    }

    cont++;
}

int Sprite::IncreaseCont() {
    return cont++;
}

void Sprite::ResetCont() {
    cont = 0;
}

int Sprite::GetCont() {
    return cont;
}

void Sprite::Shot() {
    if(shots < maxShots) {
        shots++;
    }
    else {
        shots = 0;
    }
}

void Sprite::SetMaxBullets(int max) {
    maxShots = max;
}

int Sprite::GetBullets() {
    return shots;
}

void Sprite::SetActionDelay(int val) {
    delay = val;
}

void Sprite::ResetActionDelay() {
    delay = 0;
}

int Sprite::GetActionDelay() {
    return delay;
}

bool Sprite::Stop(bool val) {
	stop = val;

	return stop;
}

bool Sprite::Stop() {
	return stop;
}

void Sprite::AddPos(int x, int y) {
    pos.x += x;
    pos.y += y;
}

void Sprite::AddX(int x) {
    pos.x += x;
}

void Sprite::AddY(int y) {
    pos.y += y;
}

void Sprite::SetPos(float x, float y) {
    pos.x = x;
    pos.y = y;
}

void Sprite::SetAngle(float x, float y) {
	angleX = x;
	angleY = y;
}

void Sprite::SetX(int x) {
    pos.x = x;
}

void Sprite::SetY(int y) {
    pos.y = y;
}

int Sprite::GetMaxVelX() {
	return maxVelX;
}

int Sprite::GetMaxVelY() {
	return maxVelY;
}

void Sprite::SetOffsetX(int x) {
    rect.x = x;
}

void Sprite::SetOffsetY(int y) {
    rect.y = y;
}

void Sprite::SetOffsetW(int w) {
    rect.w = w;
}

void Sprite::SetOffsetH(int h) {
    rect.h = h;
}

void Sprite::SetSize(int w, int h) {
    rect.w = w;
    rect.h = h;
}

void Sprite::SetAccel(float x, float y) {
    accelX = x;
    accelY = y;
}

void Sprite::SetAccelX(float x) {
    accelX = x;
}

void Sprite::SetAccelY(float y) {
    accelY = y;
}

void Sprite::SetVel(float x, float y) {
    velX = x;
    velY = y;
}

void Sprite::SetVelX(float x) {
    velX = x;
}

void Sprite::SetVelY(float y) {
    velY = y;
}

void Sprite::SetAlpha(Uint8 val) {
	alpha = val;
    SDL_SetAlpha(surface, SDL_SRCALPHA | SDL_RLEACCEL, val);
}

Uint8 Sprite::GetAlpha() {
	return alpha;
}

void Sprite::SetColorKey(int R, int G, int B) {
    SDL_SetColorKey(surface, SDL_SRCCOLORKEY | SDL_RLEACCEL, SDL_MapRGB(surface->format, R, G, B));
}

void Sprite::SetDestination(SDL_Surface* destin) {
    destination = destin;
}

void Sprite::Release() {
	SDL_FreeSurface(surface);
}

void Sprite::SetStatus(int stats) {
    status = stats;
}

SDL_Surface* Sprite::GetSurface() {
    return surface;
}

void Sprite::Draw() {
    SDL_Rect position = {pos.x, pos.y, pos.w, pos.h};

    if(lastUpdate + speed < (int)SDL_GetTicks()) {
        frame++;

        if(frame >= frames) {
            frame = 0;
        }

        lastUpdate = SDL_GetTicks();
    }

    SDL_BlitSurface(surface, &offset[frame], destination, &position);
}

void Sprite::Draw(int nFrame) {
    SDL_Rect position = {pos.x, pos.y, pos.w, pos.h};

    SDL_BlitSurface(surface, &offset[nFrame], destination, &position);
}

SDL_Rect Sprite::GetRect() {
	return pos;
}

bool Sprite::CheckCollision(Sprite &spr) {
    if(pos.y+rect.h+rect.y < spr.GetY()+spr.GetOffsetY()) return false;
    if(pos.y+rect.y > spr.GetY()+spr.GetOffsetH()+spr.GetOffsetY()) return false;
    if(pos.x+rect.w+rect.x < spr.GetX()+spr.GetOffsetX()) return false;
    if(pos.x+rect.x > spr.GetX()+spr.GetOffsetW()+spr.GetOffsetX()) return false;

    return true;
}
