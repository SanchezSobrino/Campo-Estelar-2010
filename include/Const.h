#ifndef CONST_H_INCLUDED
#define CONST_H_INCLUDED

// Game
const short SDL_TTF   = 1;
const short SDL_MIXER = 2;

// Sprite
const short DIR_UP         = 0;
const short DIR_UP_RIGHT   = 1;
const short DIR_RIGHT      = 2;
const short DIR_RIGHT_DOWN = 3;
const short DIR_DOWN       = 4;
const short DIR_DOWN_LEFT  = 5;
const short DIR_LEFT       = 6;
const short DIR_LEFT_UP    = 7;

// Constantes de Campo Estelar 2010

/*
** Configuarción interna del motor
*/
const int FRAMES_PER_SECOND = 60;
const int MAX_AUX_VARIABLES = 10;

/*
** Constantes matemáticas
*/
const float PI = 3.1415926f;

/*
** Número de asteroides máximo a generar
** Numero de disparos que puede realizar la nave
** Número de explosiones a la vez
*/
const int MAX_ASTEROIDS  = 14;
const int MAX_SHOTS      = 30;
const int MAX_EXPLOSIONS = 50;

/*
** Máxima puntuación para bonus
** Máxima cantidad de cast para lanzar una magia
*/
int max_exp = 100;
const int MAX_CAST  = 100;
const float MAX_INCREASE_CAST = 0.25f;

/*
** Daños mínimos y máximos que puede realizar nuestra nave
*/
const int SHIP_MIN_DAMAGE = 15;
const int SHIP_MAX_DAMAGE = 30;

int MAX_ENEMY1_HP, ENEMY1_SCORE;
int MAX_ENEMY2_HP, ENEMY2_SCORE;
int MAX_ENEMY3_HP, ENEMY3_SCORE;
int MAX_ENEMY4_HP, ENEMY4_SCORE;
int MAX_ENEMY5_HP, ENEMY5_SCORE;
int MAX_ENEMY6_HP, ENEMY6_SCORE;

/*
** Tipos de objetos
*/
const int MAX_ITEMS   = 30;
const int ITEM_POTION = 0;
const int ITEM_ETHER  = 1;
const int ITEM_SHIELD = 2;

const int POTION_START = 0;
const int ETHER_START  = 10;
const int SHIELD_START = 20;

/*
** Físicas
*/

const float ACELERACION = 1.115;
const float DECELERACION = 0.99;

#endif // CONST_H_INCLUDED
