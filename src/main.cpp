/****************************/
/** Campo Estelar 2010     **/
/** Estándar C++0x         **/
/****************************/

// C++
#include <sstream>
#include <math.h>

#include <SDL/SDL.h>

// Librería principal
#include "EXILib.h"

//#define _DEBUG_

const int MAX_ACCEL = 10;
const float INC_ACCEL = 0.2;

// Variables globales varias
int offset1 = 0, offset2 = 0;   // Controla el desplazamiento del fondo
int numExp = 1;                 // Identifica la explosión activa
int numTotalItem = 0;           // Numero de items en pantalla
int relX[MAX_AUX_VARIABLES];    // Posicion relativa X auxiliar
int relY[MAX_AUX_VARIABLES];    // Posicion relativa Y auxiliar
int hueco[6];                   // Huecos del inventario [nº de hueco]
int itemAnim = 0;				// Controla si la animación de los items está activa
int numItem[3] = {0, 10, 20};	// 3 tipos de items, ocupando las posiciones dadas
int mouseX, mouseY;				// Posición del ratón en pantalla
float accelX = 1, accelY = 1;	// Aceleración de la nave
SDL_Surface* barraBossSprite = NULL;
SDL_Surface* blackFade = NULL;
SDL_Surface* whiteFade = NULL;
int status = 0;
int bossX, bossY;
int contAst2[] = {0, 0, 0, 0};
int cont2Ast2[] = {255, 255, 255, 255};

int contBoss = 255;
int contBoss2 = 255;
int contBoss3 = 0;
int contSegundosBoss = 0;
int estadoBoss1 = 0;
int estadoBoss2 = 0;
int estadoBoss3 = 0;

SDL_Rect rectBossLife = {25, 600, 750, 45};

int flag = 100;
int controlFade = 0;
int muertes = 0;
int muertes2 = 0;
int muertes3 = 0;
int estado = 0;
int numBoss = -1;
int numeroJefe = 0;
int minionsMuertos = 0;
int stage = 0;
int stageReal = 0;
int numCiclo = 0;
int estadoAsteroides[] = { 0, 0, 0, 0};
int flagRara = 1;
bool activarBoss2 = true;
bool activarBoss3 = false;
bool creditosActivados = false;
bool disparableAsteroides[] = { false, false, false, false };
bool disparoA = false;
bool disparoB = false;
bool disparoC = false;
bool disparoD = false;
bool disparoMinion[] = { false, false, false };
bool disparableMinions[] = { false, false, false };
bool absorbeNave = false;
bool controlNaveFade = false;
bool naveMuerta = false;

// Objetos generales
Game game;                      // Inicializador del juego en si
Font texto1, texto2;            // Controlador de escritura de texto en pantalla
Timer fps, update, limit;       // Algunos temporizadores
Font dialogo;

// Sprites
Sprite cursor, ship, info;
Sprite asteroide[MAX_ASTEROIDS];    // Enemigos
Sprite asteroide2[MAX_ASTEROIDS];
Sprite explosion[MAX_EXPLOSIONS];   // Explosiones
Sprite shot[MAX_SHOTS];             // Disparos
Sprite shotA[8];
Sprite shotB[8];
Sprite shotC[8];
Sprite shotD[8];
Sprite bar1[MAX_ASTEROIDS];         // Barras de energía
Bar bar2[MAX_ASTEROIDS];			//    "	  "    "
Bar bar[4];                         // Barras de vida, mana y casteo
Bar barraBoss[3];
Sprite shotBoss[MAX_SHOTS];
Sprite blastBoss;
Sprite item[MAX_ITEMS];
Sprite potionAnim, etherAnim, shieldAnim, shield, getItem;
Sprite precast;
Sprite blast;						// Magia Blast del juego
Sprite NUM;

Sprite boss[3];

Sprite boss0Minion[12];
Sprite boss0Shots[12];
Sprite boss1Minion[3];
Sprite boss1Protegido;
bool boss1Protegido1 = false;
Sprite gravedad0, gravedad1[3];
Sprite cristal;

// Tiles
Tile tile1, tile2;                  // Los tiles del fondo

// Audio
Music back, creditos, menu1, menu2, jefe;    // Las canciones de fondo
Sound disparoGravitatorioSnd,
explosionSnd, potionSnd, shotSnd;

// Prototipos de funciones
void initSprites();                         	// Inicia todos los gráficos
void initAudio();                           	// Inicia las canciones/sonidos
void moveAsteroids();                       	// Mueve/Dibuja los enemigos
void moveAsteroids2();
void shipControl(Uint8* key, Uint8 button); 	// Controlador del jugador
void drawMap(int vel1, int vel2);  // Dibuja el mapa con un desplazamiento y una velocidad dada
void updateExpl();                          	// Actualiza las explosiones
void updateBullets();                       	// Actualiza la posicion de los disparos
void updateBars();                         		// Actualiza las barras de energia de los enemigos
void updateInfo();                          	// Actualiza la información de la nave
void updateItemsMenu();                     	// Actualiza los items en pantalla
void updateItemsUse(SDL_Event &event);      	// Actualiza el uso de los items
void updateItemUseControl(int num);         	// "		"	"	"	"	"
void deleteItems();
void createItem(int x, int y, int num);			// "		"	"	"	"	"
void destroyAll();								// Destruye todos los enemigos en pantalla
void enableShield(bool val);					// Activa el escudo a peticion
int aleatorio(int m, int n);                	// Genera numeros entre m y n
SDL_Surface* loadImage(const char* ruta);		// Carga una imagen a una surface
void putPixel(int x, int y, Uint32 color, SDL_Surface* surface);	// Dibuja un píxel en pantalla
int menuControl();
void inTransmission(int num);
void start();
void logros();
void updateEnemyBullet();
void muerto();

void bossLife(int num);
void drawBoss(int num);
void updateBossBullet();

void fade();
void dificultad();
void tutorial();
int creditosFinales();

void reset();
void unloadSprites();

// Logros y puntuaciones
double maxScore = 0;
bool facilPasado = false;
bool normalPasado = false;
bool dificilPasado = false;
bool locuraPasado = false;
bool medallaBronce = false;
bool medallaPlata = false;
bool medallaOro = false;
bool medallaPlatino = false;
bool destructor = false;
bool taumaturgo = false;
bool campeon = false;

int enemigosDestruidos = 0;
int danio = 0;
bool artesArcanas = false;

SDL_Surface* logro0 = NULL;
SDL_Surface* logro1 = NULL;
SDL_Surface* logro2 = NULL;
SDL_Surface* logro3 = NULL;
SDL_Surface* logro4 = NULL;
SDL_Surface* logro5 = NULL;
SDL_Surface* logro6 = NULL;
SDL_Surface* logro7 = NULL;
SDL_Surface* logro8 = NULL;
SDL_Surface* logro9 = NULL;
SDL_Surface* logro10 = NULL;
SDL_Surface* logro11 = NULL;

//////////////////////////////////////////////////////////////

int main(int argc, char* args[]) {
    bool loop = true;
    bool loop2 = true;
	bool showLife = false;

    game.Init("Campo Estelar 2010 | v1.0", NULL, SDL_INIT_EVERYTHING, SDL_TTF | SDL_MIXER);
    screen = game.SetVideoMode(800, 600, 32, SDL_ANYFORMAT);

    SDL_Event event;
    srand(SDL_GetTicks());

    initAudio();

    texto1.Load("Recursos/visitor.ttf", 16);
    texto1.SetForegroundColor(255, 255, 255);
    texto1.SetDestination(screen);

    texto2.Load("Recursos/visitor.ttf", 18);
    texto2.SetForegroundColor(255, 255, 255);
    texto2.SetDestination(screen);

    dialogo.Load("Recursos/visitor.ttf", 14);
    dialogo.SetForegroundColor(255, 255, 255);
    dialogo.SetDestination(screen);

#ifdef _DEBUG_
    int frame = 0;
#endif

    update.Start();
    fps.Start();
    game.ShowCursor(false);

	menu1.Play();

    logro0 = loadImage("Recursos/GFX/Backgrounds/Logros/Logro0.png");
	logro1 = loadImage("Recursos/GFX/Backgrounds/Logros/Logro1.png");
	logro2 = loadImage("Recursos/GFX/Backgrounds/Logros/Logro2.png");
	logro3 = loadImage("Recursos/GFX/Backgrounds/Logros/Logro3.png");
	logro4 = loadImage("Recursos/GFX/Backgrounds/Logros/Logro4.png");
	logro5 = loadImage("Recursos/GFX/Backgrounds/Logros/Logro5.png");
	logro6 = loadImage("Recursos/GFX/Backgrounds/Logros/Logro6.png");
	logro7 = loadImage("Recursos/GFX/Backgrounds/Logros/Logro7.png");
	logro8 = loadImage("Recursos/GFX/Backgrounds/Logros/Logro8.png");
	logro9 = loadImage("Recursos/GFX/Backgrounds/Logros/Logro9.png");
	logro10 = loadImage("Recursos/GFX/Backgrounds/Logros/Logro10.png");
	logro11 = loadImage("Recursos/GFX/Backgrounds/Logros/Logro11.png");

	barraBossSprite = loadImage("Recursos/GFX/Sprites/Boss/BossLife.png");
    blackFade = loadImage("Recursos/GFX/Backgrounds/Negro.png");
    whiteFade = loadImage("Recursos/GFX/Backgrounds/Blanco.png");

    // Diana
    SDL_Rect dianaClip = {0, 0, 34, 34};
    cursor.Init(11, 11, 12, 12, 1, 75, 0, 0, "Recursos/GFX/Sprites/Diana.png", dianaClip, screen);
    cursor.SetPos(400, 300);

    // 2010
    dianaClip = {0, 0, 246, 130};
    NUM.Init(0, 0, 246, 130, 6, 37, 0, 0, "Recursos/GFX/Backgrounds/2010.png", dianaClip, screen);
    NUM.SetPos(552, 40);
    NUM.SetAlpha(255);

    // Leemos la puntuacion y los logros de los archivos
    FILE* f1;
    f1 = fopen ("save", "r");
	if(f1 == NULL) {
		return -1;
	}
	else {
		int valor[11];
		double resultado;

		fscanf(f1, "%d:%d:%d:%d:%d:%d:%d:%d:%d:%d:%d:%lf",
				&valor[0], &valor[1], &valor[2], &valor[3], &valor[4], &valor[5],
				&valor[6], &valor[7], &valor[8], &valor[9], &valor[10], &resultado);

		if(valor[0] == 1) facilPasado = true;
		if(valor[1] == 1) normalPasado = true;
		if(valor[2] == 1) dificilPasado = true;
		if(valor[3] == 1) locuraPasado = true;
		if(valor[4] == 1) medallaBronce = true;
		if(valor[5] == 1) medallaPlata = true;
		if(valor[6] == 1) medallaOro = true;
		if(valor[7] == 1) medallaPlatino = true;
		if(valor[8] == 1) destructor = true;
		if(valor[9] == 1) taumaturgo = true;
		if(valor[10] == 1) campeon = true;
		maxScore = resultado;
		fclose(f1);
	}

    // Estrellitas :D
    Pixel Estrella[200];
    for(int i = 0; i < 200; i++) {
    	int random = ((rand() % 255) + 50);
		Estrella[i].SetRad((rand() % 180));
		Estrella[i].SetAng(rand() % 65535);
  		Estrella[i].SetSpeed((rand() % 5) + 1);
  		Estrella[i].SetColor(random, random, random);
	}

	while(loop2) {
		// Menú
		menu2.Play();
		switch(menuControl()) {
			case 0:			// Nuevo Juego
				loop = true;
				dificultad();
				tutorial();
				menu2.Stop();
				menu2.Volume(128);
				back.Play();
				game.SetScore(0);
				break;
			case 1:			// Continuar
				break;
			case 2:			// Opciones
				break;
			case 3:			// Salir
				loop = false;
				loop2 = false;
				break;
		}

		reset();
		start();
		initSprites();

		while(loop) {
			// Inicio del contador de FPS
			limit.Start();
			numCiclo = 1;

			// Entrada por teclado / ratón
			Uint8* key = SDL_GetKeyState(NULL);
			Uint8 button = SDL_GetMouseState(&mouseX, &mouseY);

			while(SDL_PollEvent(&event)) {
				if(event.type == SDL_QUIT) {
					loop = false;
					loop2 = false;
				}
				else if(event.type == SDL_KEYDOWN) {
					if(event.key.keysym.sym == SDLK_ESCAPE) {
						loop = false;
					}
					if(event.key.keysym.sym == SDLK_v) {
						(showLife)?showLife=false:showLife=true;
					}
					if(event.key.keysym.sym == SDLK_F1) {
						game.ToggleFullWindowedScreen(screen);
					}

					updateItemsUse(event);
		#ifdef _DEBUG_
					if(event.key.keysym.sym == SDLK_SPACE) {
						destroyAll();
					}
					if(event.key.keysym.sym == SDLK_k) {
						boss[0].SetHP(0);
					}

					if(event.key.keysym.sym == SDLK_m) {
						for(int i = 0; i < 4; i++) {
							asteroide2[i].SetHP(0);
						}
					}
					if(event.key.keysym.sym == SDLK_n) {
						for(int i = 0; i < 4; i++) {
							boss[1].SetHP(0);
						}
					}
					if(event.key.keysym.sym == SDLK_b) {
						boss[2].SetHP(0);
					}
		#endif
				}
			}

			// Lógica del juego
			cursor.SetPos(mouseX - (cursor.GetOffsetW() >> 1), mouseY - (cursor.GetOffsetH() >> 1));

			// Dibujado de la escena
			if(estado < 4) {
				drawMap(4, 2);
			}
			else {
				game.FillRect(screen, &screen->clip_rect, SDL_MapRGB(screen->format, 0, 0, 0));

				for(int i = 0; i < 200; i++) {
					if(boss[2].GetHP() <= 5000) Estrella[i].SetColor(0, 255, 0);
					if(boss[2].GetHP() < 3000) Estrella[i].SetColor(255, 255, 0);
					if(boss[2].GetHP() < 1000) Estrella[i].SetColor(255, 0, 0);

					Estrella[i].SetX((800/2) + sin(((2*Estrella[i].GetAng()) * 3.14159265) / 360) * Estrella[i].GetRad());
					Estrella[i].SetY((600/2) + cos(((2*Estrella[i].GetAng()) * 3.14159265) / 360) * Estrella[i].GetRad());
					if((Estrella[i].GetX() < 6) || (Estrella[i].GetX() > 794) || (Estrella[i].GetY() < 6) || (Estrella[i].GetY() > 594)) {
						Estrella[i].SetRad((rand() % 40));
						Estrella[i].SetAng(rand() % 65535);
						Estrella[i].SetSpeed((rand() % 5) + 1);
					}
					Estrella[i].AddRad(Estrella[i].GetSpeed());
					Estrella[i].Draw();
				}
			}

			if((muertes >= MAX_ASTEROIDS) && (numeroJefe == 0)) {
				numBoss = 0;
				drawBoss(numeroJefe);
			}
			if((muertes2 >= 4) && (numeroJefe == 1)) {
				if(flagRara == 1) {
					for(int i = 0; i < 3; i++) {
						bar2[i].Create(384, 0, 40, 3, boss1Minion[i].GetHP(), screen);
					}
				}
				flagRara = -1;
				estado = 3;
				numBoss = 1;
				drawBoss(numeroJefe);
			}

			enableShield(shield.Enable());
			if(precast.Enable()) precast.Draw();
			ship.Draw(ship.GetStatus());
			if(absorbeNave) boss1Protegido.Draw();

			switch(stageReal) {
				case 0:
					moveAsteroids();
					break;
				case 1:
					moveAsteroids2();
					break;
			}

			updateBars();
			shipControl(key, button);
			if(showLife) {
				if(stageReal == 0) {
					for(int i = 0; i < MAX_ASTEROIDS; i++) {
						texto1.WriteBlended(asteroide[i].GetX()+9, asteroide[i].GetY()-20, "HP: %d  ", asteroide[i].GetHP());
					}
				}
				else if(stageReal == 1) {
					for(int i = 0; i < 3; i++) {
						texto1.WriteBlended(boss1Minion[i].GetX()+8, boss1Minion[i].GetY()-30, "HP: %d  ", boss1Minion[i].GetHP());
					}
					for(int i = 0; i < 4; i++) {
						if(asteroide2[i].Enable()) {
							texto1.WriteBlended(asteroide2[i].GetX()+8, asteroide2[i].GetY()-30, "HP: %d  ", asteroide2[i].GetHP());
						}
					}
				}
			}

			if((muertes >= MAX_ASTEROIDS) && (numeroJefe == 0)) {
				bossLife(numeroJefe);
			}
			if((muertes2 >= 4) && (numeroJefe == 1)) {
				bossLife(numeroJefe);
			}
			if((muertes3 >= 1) && (numeroJefe == 2)) {
				bossLife(numeroJefe);
			}

			updateExpl();
			updateBullets();

			cursor.Draw();
			updateInfo();
			updateItemsMenu();

			if(game.GetScore() >= 100000) medallaBronce = true;
			if(game.GetScore() >= 200000) medallaPlata = true;
			if(game.GetScore() >= 300000) medallaOro = true;
			if(game.GetScore() >= 1000000) medallaPlatino = true;

			if(controlFade == 1) {
				fade();
			}

			if(numeroJefe == 2) {
				drawBoss(numeroJefe);
			}

			if(naveMuerta) {
				muerto();
				naveMuerta = false;
			}

			if(ship.GetHP() < 150) danio = 1;

			if(creditosActivados) {
				switch(creditosFinales()) {
					case 0:
						loop = false;
						break;
					case 1:
						break;
				}
			}

			if(game.Render(screen) == -1) {
				return 1;
			}

			if(numCiclo == 1) {
				switch(flag) {
					case 100:
						inTransmission(0);
						flag = 0;
						break;
					case 0:
						if(muertes >= MAX_ASTEROIDS) {
							inTransmission(1);
							estado = 1;
							numBoss = 0;
							flag = -1;
						}
						break;
					case 1:
						inTransmission(2);
						break;
					case 2:
						inTransmission(3);
						break;
					case 3:
						inTransmission(4);
						break;
					case 4:
						inTransmission(5);
						flag = -1;
						break;
					case 5:
						inTransmission(6);
						flag = -1;
						break;
					case 6:
						inTransmission(7);
						flag = -1;
						break;
					case 7:
						inTransmission(8);
						flag = -1;
						break;
					case 8:
						inTransmission(9);
						flag = -1;
						break;
					case 9:
						inTransmission(10);
						flag = -1;
						break;
				}
			}

			// Comprobación de los fotogramas por segundo
			if(limit.GetTicks() < 1000/FRAMES_PER_SECOND) {
				game.Delay((1000/FRAMES_PER_SECOND) - limit.GetTicks());
			}
	#ifdef _DEBUG_
			std::stringstream caption;
			frame++;
			caption << "Campo Estelar 2010 | FPS: " << frame/(fps.GetTicks()/1000.f);
			SDL_WM_SetCaption(caption.str().c_str(), NULL);
			update.Start();
	#endif
		}
	}

    TTF_CloseFont(texto1.GetFont());
    TTF_CloseFont(texto2.GetFont());
    game.Quit();

    return 0;
}

// Inicializa los sprites del juego
void initSprites() {
    SDL_Rect clip;
    int i;

    // Inicio de las posiciones relativas auxiliares
    for(i = 0; i < MAX_AUX_VARIABLES; i++) {
        relX[i] = 0;
        relY[i] = 0;
    }

    // Inicio de los huecos de la mochila
    for(i = 0; i < 6; i++) {
        hueco[i] = -1;
    }

    // Asteroides
    clip = {0, 0, 64, 64};
    for(i = 0; i < MAX_ASTEROIDS; i++) {
        asteroide[i].Init(15, 11, 34, 42, 8, 75, rand() % 5 + 1, rand() % 5 + 1, "Recursos/GFX/Sprites/Asteroides.png", clip, screen);
        asteroide[i].SetStatus(rand() % 4);
        asteroide[i].SetPos(rand() % 800, 0);
        asteroide[i].SetHP(MAX_ENEMY1_HP);
        asteroide[i].SetItem(-1);
        asteroide[i].SetScore(ENEMY1_SCORE);
    }
    asteroide[0].SetItem(ITEM_POTION);
    asteroide[1].SetItem(ITEM_ETHER);
    asteroide[2].SetItem(ITEM_SHIELD);

    clip = {0, 0, 61, 61};
	for(i = 0; i < 2; i++) {
		asteroide2[i].Init(17, 17, 27, 27, 8, 75, 3, 3, "Recursos/GFX/Sprites/Asteroides2a.png", clip, screen);
		asteroide2[i].SetHP(MAX_ENEMY3_HP);
		asteroide2[i].SetItem(-1);
		asteroide2[i].SetItem(ITEM_POTION);
		asteroide2[i].SetScore(ENEMY3_SCORE);
		asteroide2[i].SetAlpha(0);
		asteroide2[i].SetPos(-100, -100);
	}
	for(i = 2; i < 4; i++) {
		asteroide2[i].Init(17, 17, 27, 27, 8, 75, 3, 3, "Recursos/GFX/Sprites/Asteroides2b.png", clip, screen);
		asteroide2[i].SetHP(MAX_ENEMY3_HP);
		asteroide2[i].SetItem(-1);
		asteroide2[i].SetItem(ITEM_ETHER);
		asteroide2[i].SetScore(ENEMY3_SCORE);
		asteroide2[i].SetAlpha(0);
		asteroide2[i].SetPos(-100, -100);
	}
	asteroide2[0].Enable(false);
	asteroide2[1].Enable(false);
	asteroide2[2].Enable(false);
	asteroide2[3].Enable(false);

	asteroide2[0].SetPos(232, 201);		// ROJO
	asteroide2[1].SetPos(232, 402);		// ROJO
	asteroide2[2].SetPos(507, 201);		// AZUL
	asteroide2[3].SetPos(507, 402);		// AZUL

    // Disparos enemigos
    clip = {0, 0, 61, 61};
    for(i = 0; i < 8; i++) {
        shotA[i].Init(26, 26, 8, 8, 1, 1, 5, 5, "Recursos/GFX/Sprites/ShotAstA.png", clip, screen);
        shotA[i].SetPos(-100, 0);
        shotB[i].Init(26, 26, 8, 8, 1, 1, 5, 5, "Recursos/GFX/Sprites/ShotAstA.png", clip, screen);
        shotB[i].SetPos(-100, 0);
    }
    for(i = 0; i < 8; i++) {
        shotC[i].Init(26, 26, 8, 8, 1, 1, 5, 5, "Recursos/GFX/Sprites/ShotAstB.png", clip, screen);
        shotC[i].SetPos(-100, 0);
        shotD[i].Init(26, 26, 8, 8, 1, 1, 5, 5, "Recursos/GFX/Sprites/ShotAstB.png", clip, screen);
        shotD[i].SetPos(-100, 0);
    }

    // Jugador
    clip = {0, 0, 38, 38};
    ship.Init(5, 5, 33, 33, 16, 1, 1, 1, "Recursos/GFX/Sprites/Ship.png", clip, screen);
    ship.SetPos(400, 300);
    ship.SetMaxBullets(MAX_SHOTS);
    ship.SetHP(150);
    ship.SetMP(100);
    ship.SetCast(0);

    // Explosiones
    clip = {0, 0, 64, 64};
    for(i = 0; i < MAX_EXPLOSIONS; i++) {
        explosion[i].Init(0, 0, 64, 64, 6, 75, 0, 0, "Recursos/GFX/Sprites/Explosion.png", clip, screen);
        explosion[i].Enable(false);
        explosion[i].SetAlpha(128);
    }

    // Disparos
    clip = {0, 0, 38, 38};
    for(i = 0; i < MAX_SHOTS; i++) {
        shot[i].Init(16, 16, 5, 5, 1, 1, 10, 10, "Recursos/GFX/Sprites/Bala.png", clip, screen);
        shot[i].SetPos(-100, 0);
    }

    // Tiles
    clip = {0, 0, 208, 208};
    tile1.Init(0, 0, 208, 208, "Recursos/GFX/Backgrounds/Stars1.png", clip, screen);
    tile2.Init(0, 0, 208, 208, "Recursos/GFX/Backgrounds/Stars2.png", clip, screen);
    tile2.SetColorKey(255, 0, 255);

    // Barras
    clip = {0, 0, 46, 9};
    for(i = 0; i < MAX_ASTEROIDS; i++) {
        bar1[i].Init(0, 0, 46, 9, 20, 0, 0, 0, "Recursos/GFX/Sprites/Barra.png", clip, screen);
        bar2[i].Create(384, 0, 40, 3, asteroide[i].GetHP(), screen);
        bar2[i].SetColor(218, 2, 5);
    }

    // Info panel y barras
    clip = {0, 0, 800, 100};
    info.Init(0, 0, 800, 100, 1, 0, 0, 0, "Recursos/GFX/Backgrounds/Info.png", clip, screen);
    bar[0].Create(76, 11, 173, 13, ship.GetHP(), screen);
    bar[0].SetColor(218, 2, 5);
    bar[1].Create(76, 33, 173, 13, ship.GetMP(), screen);
    bar[1].SetColor(154, 0, 255);
    bar[2].Create(76, 55, 173, 13, MAX_CAST, screen);
    bar[2].SetColor(77, 122, 253);
    bar[3].Create(76, 77, 173, 13, max_exp, screen);
    bar[3].SetColor(255, 121, 0);

    // Objetos
    clip = {0, 0, 40, 32};
    for(i = 0; i < 10; i++) {
        item[i].Init(0, 0, 40, 32, 2, 75, 0, 0, "Recursos/GFX/Sprites/Potion.png", clip, screen);
        item[i].SetType(ITEM_POTION);
        item[i].Enable(false);
    }
    for(i = 10; i < 20; i++) {
        item[i].Init(0, 0, 40, 32, 2, 75, 0, 0, "Recursos/GFX/Sprites/Ether.png", clip, screen);
        item[i].SetType(ITEM_ETHER);
        item[i].Enable(false);
    }
    for(i = 20; i < MAX_ITEMS; i++) {
        item[i].Init(0, 0, 40, 32, 2, 75, 0, 0, "Recursos/GFX/Sprites/Shield.png", clip, screen);
        item[i].SetType(ITEM_SHIELD);
        item[i].Enable(false);
    }

    // Animaciones de los objetos
    clip = {0, 0, 64, 64};
    potionAnim.Init(0, 0, 64, 64, 17, 75, 0, 0, "Recursos/GFX/Sprites/PotionAnim.png", clip, screen);
    potionAnim.Enable(false);
    etherAnim.Init(0, 0, 64, 64, 17, 75, 0, 0, "Recursos/GFX/Sprites/EtherAnim.png", clip, screen);
    etherAnim.Enable(false);
    shieldAnim.Init(0, 0, 64, 64, 17, 75, 0, 0, "Recursos/GFX/Sprites/ShieldAnim.png", clip, screen);
    shieldAnim.Enable(false);

    // Animación al obtener un item
    clip = {0, 0, 32, 32};
    getItem.Init(0, 0, 32, 32, 9, 75, 0, 0, "Recursos/GFX/Sprites/GetItem.png", clip, screen);
    getItem.Enable(false);

    // Escudo
    clip = {0, 0, 64, 64};
    shield.Init(0, 0, 64, 64, 13, 75, 0, 0, "Recursos/GFX/Sprites/ShieldAnim2.png", clip, screen);
    shield.Enable(false);

    // Blast
    clip = {0, 0, 32, 32};
    blast.Init(2, 2, 28, 28, 1, 1, 10, 10, "Recursos/GFX/Sprites/Magia.png", clip, screen);
    blast.Enable(false);

    // Bosses
    barraBoss[0].Create(36, 581, 728, 12, MAX_ENEMY2_HP, screen);
    barraBoss[0].SetColor(255, 0, 0);
    barraBoss[1].Create(36, 581, 728, 12, MAX_ENEMY4_HP, screen);
    barraBoss[1].SetColor(255, 0, 0);
    barraBoss[2].Create(36, 581, 728, 12, MAX_ENEMY6_HP, screen);
    barraBoss[2].SetColor(255, 0, 0);

    // Boss 0
    clip = {0, 0, 555, 555};
    boss[0].Init(74, 77, 397, 388, 4, 75, 0, 0, "Recursos/GFX/Sprites/Boss/Boss1.png", clip, screen);
    boss[0].SetPos(122, -480);
    boss[0].SetHP(MAX_ENEMY2_HP);
    boss[0].SetScore(ENEMY2_SCORE);
    boss[0].Enable(true);
    boss[0].SetAlpha(255);

    clip = {0, 0, 27, 27};
    for(i = 0; i < 12; i++) {
		boss0Shots[i].Init(2, 2, 23, 21, 8, 75, 0, 0, "Recursos/GFX/Sprites/Boss/Boss1Shots.png", clip, screen);
		boss0Shots[i].SetPos(rand() % 800, 0);
    }

    clip = {0, 0, 28, 27};
    for(i = 0; i < 12; i++) {
        boss0Minion[i].Init(2, 3, 25, 24, 8, 75, 0, 0, "Recursos/GFX/Sprites/Boss/Boss1Minions.png", clip, screen);
        boss0Minion[i].SetPos(rand() % 800, rand() % 600);
        boss0Minion[i].SetHP(100);
    }
    for(i = 0; i < 6; i++) {
		boss0Minion[i].SetPos(20*i, (rand() % 100) + (boss[0].GetY()+253));
    }
    for(i = 6; i < 12; i++) {
		boss0Minion[i].SetPos(650+(20*(i-5)), (rand() % 100) + (boss[0].GetY()+253));
    }

    // Boss 1
    clip = {0, 0, 61, 61};
    boss[1].Init(17, 17, 27, 27, 8, 75, 3, 3, "Recursos/GFX/Sprites/Boss/Boss2.png", clip, screen);
    boss[1].SetPos(370, 135);
    boss[1].SetHP(MAX_ENEMY4_HP);
    boss[1].SetScore(ENEMY4_SCORE);
    boss[1].Enable(true);
    boss[1].SetAlpha(0);

    clip = {0, 0, 400, 400};
    gravedad0.Init(0, 0, 400, 400, 8, 75, 3, 3, "Recursos/GFX/Sprites/Boss/Gravedad1.png", clip, screen);
    gravedad0.SetPos(204, -106);
    gravedad0.SetAlpha(0);

    clip = {0, 0, 96, 98};
    for(i = 0; i < 3; i++) {
		gravedad1[i].Init(0, 0, 96, 98, 8, 75, 3, 3, "Recursos/GFX/Sprites/Boss/Gravedad2.png", clip, screen);
		gravedad1[i].SetPos(371, 100);
		gravedad1[i].SetAlpha(180);
    }

    clip = {0, 0, 61, 61};
    boss1Protegido.Init(0, 0, 61, 61, 6, 75, 3, 3, "Recursos/GFX/Sprites/Boss/Boss2Protected.png", clip, screen);
    boss1Protegido.SetPos(370, 135);
    boss1Protegido.SetAlpha(0);
    boss1Protegido1 = true;

    clip = {0, 0, 61, 61};
    boss1Minion[0].Init(17, 17, 27, 27, 8, 75, 3, 3, "Recursos/GFX/Sprites/Boss/Boss1Minions1.png", clip, screen);
    boss1Minion[1].Init(17, 17, 27, 27, 8, 75, 3, 3, "Recursos/GFX/Sprites/Boss/Boss1Minions2.png", clip, screen);
    boss1Minion[2].Init(17, 17, 27, 27, 8, 75, 3, 3, "Recursos/GFX/Sprites/Boss/Boss1Minions3.png", clip, screen);
    for(i = 0; i < 3; i++) {
		boss1Minion[i].Enable(false);
		boss1Minion[i].SetPos(-100, -100);
		boss1Minion[i].SetAlpha(0);
		boss1Minion[i].SetHP(MAX_ENEMY5_HP);
    }

	// Boss 2
    clip = {0, 0, 128, 128};
    cristal.Init(33, 20, 60, 96, 6, 75, 3, 3, "Recursos/GFX/Sprites/Boss/cristal.png", clip, screen);
    cristal.Enable(false);
    cristal.SetPos(336, 236);
    cristal.SetAlpha(160);
    cristal.SetHP(4000);

    clip = {0, 0, 38, 38};
    boss[2].Init(5, 5, 33, 33, 16, 1, 1, 1, "Recursos/GFX/Sprites/Boss/Boss3.png", clip, screen);
    boss[2].SetPos(-100, -100);
    boss[2].SetHP(MAX_ENEMY6_HP);
    boss[2].Enable(false);
    boss[2].SetMaxBullets(MAX_SHOTS);

    clip = {0, 0, 38, 38};
    for(i = 0; i < MAX_SHOTS; i++) {
		shotBoss[i].Init(15, 15, 7, 7, 1, 1, 5, 5, "Recursos/GFX/Sprites/Boss/BalaBoss3.png", clip, screen);
        shotBoss[i].SetPos(-100, 0);
    }

    clip = {0, 0, 32, 32};
    blastBoss.Init(2, 2, 28, 28, 1, 1, 10, 10, "Recursos/GFX/Sprites/Boss/MagiaBoss3.png", clip, screen);
    blastBoss.SetPos(-100, -100);
    blastBoss.Enable(false);
}

void unloadSprites() {
	ship.Release();
	info.Release();
	for(int i = 0; i < MAX_ASTEROIDS; i++) {
		asteroide[i].Release();
		asteroide2[i].Release();
		bar1[i].Release();
	}
	for(int i = 0; i < MAX_EXPLOSIONS; i++) {
		explosion[i].Release();
	}
	for(int i = 0; i < MAX_SHOTS; i++) {
		shot[i].Release();
		shotBoss[i].Release();
	}
	for(int i = 0; i < 8; i++) {
		shotA[i].Release();
		shotB[i].Release();
		shotC[i].Release();
		shotD[i].Release();
	}
	for(int i = 0; i < 3; i++) {
		boss[i].Release();
		boss1Minion[i].Release();
		gravedad1[i].Release();
	}
	blastBoss.Release();
	for(int i = 0; i < MAX_ITEMS; i++) {
		item[i].Release();
	}
	potionAnim.Release();
	etherAnim.Release();
	shieldAnim.Release();
	shield.Release();
	getItem.Release();
	precast.Release();
	blast.Release();
	for(int i = 0; i < 12; i++) {
		boss0Minion[i].Release();
		boss0Shots[i].Release();
	}
	boss1Protegido.Release();
	gravedad0.Release();
	cristal.Release();
	tile1.Release();
	tile2.Release();
}

// Inicializa la musica
void initAudio() {
    Mix_AllocateChannels(16);

    // Músicas
    back.Load("Recursos/Music/background.mp3", -1);
    creditos.Load("Recursos/Music/creditos.mp3", -1);
    menu1.Load("Recursos/Music/menu1.mp3", 1);
    menu2.Load("Recursos/Music/menu2.mp3", -1);
    jefe.Load("Recursos/Music/boss.mp3", -1);
    jefe.Volume(0);

    // Sonidos
    disparoGravitatorioSnd.Load("Recursos/Sound/DisparoGravitatorio.wav", 0);
    potionSnd.Load("Recursos/Sound/Potion.wav", 1);
    explosionSnd.Load("Recursos/Sound/Explosion.wav", 2);
    shotSnd.Load("Recursos/Sound/Shot.wav", 4);

    // Volumen general de los sonidos. Máximo: 128
    Mix_Volume(-1, 32);
    Mix_VolumeMusic(128);
    shotSnd.Volume(32);
    explosionSnd.Volume(16);
    potionSnd.Volume(16);
}

// Mueve los asteroides
void moveAsteroids() {
    int i;

	for(i = 0; i < MAX_ASTEROIDS; i++) {
		if(asteroide[i].GetX() != -200) {
			switch(asteroide[i].GetStatus()) {
				case 0:
					asteroide[i].AddPos(asteroide[i].GetVelX(), asteroide[i].GetVelY());
					break;
				case 1:
					asteroide[i].AddPos(asteroide[i].GetVelX(), -asteroide[i].GetVelY());
					break;
				case 2:
					asteroide[i].AddPos(-asteroide[i].GetVelX(), asteroide[i].GetVelY());
					break;
				case 3:
					asteroide[i].AddPos(-asteroide[i].GetVelX(), -asteroide[i].GetVelY());
					break;
			}

			asteroide[i].SetVel(asteroide[i].GetVelX()*1.05, asteroide[i].GetVelY()*1.05);

			if(asteroide[i].GetVelX() < -asteroide[i].GetMaxVelX()) {
				asteroide[i].SetVel(-asteroide[i].GetMaxVelX(), asteroide[i].GetVelY());
			}
			if(asteroide[i].GetVelY() < -asteroide[i].GetMaxVelY()){
				asteroide[i].SetVel(asteroide[i].GetVelX(), -asteroide[i].GetMaxVelY());
			}
			if(asteroide[i].GetVelX() > asteroide[i].GetMaxVelX()) {
				asteroide[i].SetVelX(asteroide[i].GetMaxVelX());
			}
			if(asteroide[i].GetVelY() > asteroide[i].GetMaxVelY()) {
				asteroide[i].SetVelY(asteroide[i].GetMaxVelY());
			}

			if(asteroide[i].GetX() > 800) {
				asteroide[i].SetX(-50);
			}
			else if(asteroide[i].GetX() < -50) {
				asteroide[i].SetX(800);
			}
			if(asteroide[i].GetY() > 600) {
				asteroide[i].SetY(-50);
			}
			else if(asteroide[i].GetY() < -50) {
					asteroide[i].SetY(600);
			}

			if(asteroide[i].CheckCollision(ship) && ship.Enable()) {
				if(shield.Enable()) {
					asteroide[i].AddHP(-aleatorio(15, 30));
					explosion[0].Enable(true);
					explosion[0].SetPos(asteroide[i].GetX(), asteroide[i].GetY());
				}
				else {
					ship.AddHP(-aleatorio(15, 30));
					explosion[0].Enable(true);
					explosion[0].SetPos(ship.GetX()-10, ship.GetY()-10);
					ship.Enable(false);
				}

				explosionSnd.Play();
				asteroide[i].SetVel(-asteroide[i].GetVelX(), -asteroide[i].GetVelY());
			}

			if(asteroide[i].GetHP() <= 0) {
				enemigosDestruidos++;
				muertes++;
				game.AddScore(asteroide[i].GetScore());
				asteroide[i].SetHP(0);
				if(asteroide[i].GetItem() != -1)
					createItem(asteroide[i].GetX(), asteroide[i].GetY(), asteroide[i].GetItem());
				asteroide[i].SetX(-200);
			}

			asteroide[i].Draw();
		}
	}
}

void moveAsteroids2() {				// Máquina de estados: 4 estados con una profundidad de 5 funciones
	if((asteroide2[0].Enable()) && (asteroide2[0].GetHP() > 0)) {
		switch(estadoAsteroides[0])  {
			case 0:									// Fade In
				contAst2[0] += 3;
				asteroide2[0].SetAlpha(contAst2[0]);
				asteroide2[0].Draw();
				if(contAst2[0] >= 255) { contAst2[0] = 0; disparableAsteroides[0] = true; estadoAsteroides[0] = 1; }
				break;
			case 1:									// Moverse 100 píxeles en dirección a la nave
				if(asteroide2[0].GetX() < ship.GetX()) asteroide2[0].AddX(1);
				if(asteroide2[0].GetX() > ship.GetX()) asteroide2[0].AddX(-2);
				if(asteroide2[0].GetY() < ship.GetY()) asteroide2[0].AddY(2);
				if(asteroide2[0].GetY() > ship.GetY()) asteroide2[0].AddY(-1);
				contAst2[0]++;
				if(contAst2[0] >= 100) { contAst2[0] = 255; disparableAsteroides[0] = false; estadoAsteroides[0] = 2;}
				asteroide2[0].Draw();
				break;
			case 2:									// Fade Out
				disparoA = false;
				contAst2[0] -= 3;
				asteroide2[0].SetAlpha(contAst2[0]);
				asteroide2[0].Draw();
				if(contAst2[0] <= 0) { asteroide2[0].SetPos(ship.GetX() - 16, ship.GetY() - 15-64); contAst2[0] = 0; estadoAsteroides[0] = 3; }
				break;
			case 3:									// Fade In encima de la nave
				contAst2[0] += 3;
				asteroide2[0].SetAlpha(contAst2[0]);
				asteroide2[0].Draw();
				if(contAst2[0] >= 255) { for(int i = 0; i < 8; i++) { shotA[i].SetPos(asteroide2[0].GetX(), asteroide2[0].GetY()); } contAst2[0] = 255; disparableAsteroides[0] = true; estadoAsteroides[0] = 4; }
				break;
			case 4:									// Disparar en 8 direcciones y Fade Out
				disparoA = true;
				contAst2[0] -= 3;
				asteroide2[0].SetAlpha(contAst2[0]);
				asteroide2[0].Draw();
				if(contAst2[0] <= 0) { asteroide2[0].SetPos(rand() % 750, (rand()%450) + 100); contAst2[0] = 0; disparableAsteroides[0] = false; estadoAsteroides[0] = 0; }
				break;
		}
	}

	if((asteroide2[1].Enable()) && (asteroide2[1].GetHP() > 0)) {
		switch(estadoAsteroides[1]) {
			case 0:									// Fade In
				contAst2[1] += 3;
				asteroide2[1].SetAlpha(contAst2[1]);
				asteroide2[1].Draw();
				if(contAst2[1] >= 255) { contAst2[1] = 0; disparableAsteroides[1] = true; estadoAsteroides[1] = 1; }
				break;
			case 1:									// Moverse 100 píxeles en dirección a la nave
				if(asteroide2[1].GetX() < ship.GetX()) asteroide2[1].AddX(1);
				if(asteroide2[1].GetX() > ship.GetX()) asteroide2[1].AddX(-2);
				if(asteroide2[1].GetY() < ship.GetY()) asteroide2[1].AddY(1);
				if(asteroide2[1].GetY() > ship.GetY()) asteroide2[1].AddY(-2);
				contAst2[1]++;
				if(contAst2[1] >= 100) { contAst2[1] = 255; disparableAsteroides[1] = false; estadoAsteroides[1] = 2;}
				asteroide2[1].Draw();
				break;
			case 2:									// Fade Out
				disparoB = false;
				contAst2[1] -= 3;
				asteroide2[1].SetAlpha(contAst2[1]);
				asteroide2[1].Draw();
				if(contAst2[1] <= 0) { asteroide2[1].SetPos(ship.GetX() - 16, ship.GetY() - 15+64); contAst2[1] = 0; estadoAsteroides[1] = 3; }
				break;
			case 3:									// Fade In encima de la nave
				contAst2[1] += 3;
				asteroide2[1].SetAlpha(contAst2[1]);
				asteroide2[1].Draw();
				if(contAst2[1] >= 255) { for(int i = 0; i < 8; i++) { shotB[i].SetPos(asteroide2[1].GetX(), asteroide2[1].GetY()); } contAst2[1] = 255; disparableAsteroides[1] = true; estadoAsteroides[1] = 4; }
				break;
			case 4:									// Disparar en 8 direcciones y Fade Out
				disparoB = true;
				contAst2[1] -= 3;
				asteroide2[1].SetAlpha(contAst2[1]);
				asteroide2[1].Draw();
				if(contAst2[1] <= 0) { asteroide2[1].SetPos(rand() % 750, (rand()%450) + 100); contAst2[1] = 0; disparableAsteroides[1] = false; estadoAsteroides[1] = 0; }
				break;
		}
	}

	if((asteroide2[2].Enable()) && (asteroide2[2].GetHP() > 0)) {
		switch(estadoAsteroides[2]) {
			case 0:									// Fade In
				contAst2[2] += 3;
				asteroide2[2].SetAlpha(contAst2[2]);
				asteroide2[2].Draw();
				if(contAst2[2] >= 255) { contAst2[2] = 0; disparableAsteroides[2] = true; estadoAsteroides[2] = 1; }
				break;
			case 1:									// Moverse 100 píxeles en dirección a la nave
				if(asteroide2[2].GetX() < ship.GetX()) asteroide2[2].AddX(2);
				if(asteroide2[2].GetX() > ship.GetX()) asteroide2[2].AddX(-1);
				if(asteroide2[2].GetY() < ship.GetY()) asteroide2[2].AddY(1);
				if(asteroide2[2].GetY() > ship.GetY()) asteroide2[2].AddY(-2);
				contAst2[2]++;
				if(contAst2[2] >= 100) { contAst2[2] = 255; disparableAsteroides[2] = false; estadoAsteroides[2] = 2;}
				asteroide2[2].Draw();
				break;
			case 2:									// Fade Out
				disparoC = false;
				contAst2[2] -= 3;
				asteroide2[2].SetAlpha(contAst2[2]);
				asteroide2[2].Draw();
				if(contAst2[2] <= 0) { asteroide2[2].SetPos(ship.GetX() - 16-64, ship.GetY() - 15); contAst2[2] = 0; estadoAsteroides[2] = 3; }
				break;
			case 3:									// Fade In encima de la nave
				contAst2[2] += 3;
				asteroide2[2].SetAlpha(contAst2[2]);
				asteroide2[2].Draw();
				if(contAst2[2] >= 255) { for(int i = 0; i < 8; i++) { shotC[i].SetPos(asteroide2[2].GetX(), asteroide2[2].GetY()); } contAst2[2] = 255; disparableAsteroides[2] = true; estadoAsteroides[2] = 4; }
				break;
			case 4:									// Disparar en 8 direcciones y Fade Out
				disparoC = true;
				contAst2[2] -= 3;
				asteroide2[2].SetAlpha(contAst2[2]);
				asteroide2[2].Draw();
				if(contAst2[2] <= 0) { asteroide2[2].SetPos(rand() % 750, (rand()%450) + 100); contAst2[2] = 0; disparableAsteroides[2] = false; estadoAsteroides[2] = 0; }
				break;
		}
	}

	if((asteroide2[3].Enable()) && (asteroide2[3].GetHP() > 0)) {
		switch(estadoAsteroides[3]) {
			case 0:									// Fade In
				contAst2[3] += 3;
				asteroide2[3].SetAlpha(contAst2[3]);
				asteroide2[3].Draw();
				if(contAst2[3] >= 255) { contAst2[3] = 0; disparableAsteroides[3] = true; estadoAsteroides[3] = 1; }
				break;
			case 1:									// Moverse 100 píxeles en dirección a la nave
				if(asteroide2[3].GetX() < ship.GetX()) asteroide2[3].AddX(2);
				if(asteroide2[3].GetX() > ship.GetX()) asteroide2[3].AddX(-2);
				if(asteroide2[3].GetY() < ship.GetY()) asteroide2[3].AddY(2);
				if(asteroide2[3].GetY() > ship.GetY()) asteroide2[3].AddY(-2);
				contAst2[3]++;
				if(contAst2[3] >= 100) { contAst2[3] = 255; disparableAsteroides[3] = false; estadoAsteroides[3] = 2;}
				asteroide2[3].Draw();
				break;
			case 2:									// Fade Out
				disparoD = false;
				contAst2[3] -= 3;
				asteroide2[3].SetAlpha(contAst2[3]);
				asteroide2[3].Draw();
				if(contAst2[3] <= 0) { asteroide2[3].SetPos(ship.GetX() - 16+64, ship.GetY() - 15); contAst2[3] = 0; estadoAsteroides[3] = 3; }
				break;
			case 3:									// Fade In encima de la nave
				contAst2[3] += 3;
				asteroide2[3].SetAlpha(contAst2[3]);
				asteroide2[3].Draw();
				if(contAst2[3] >= 255) { for(int i = 0; i < 8; i++) { shotD[i].SetPos(asteroide2[3].GetX(), asteroide2[3].GetY()); } contAst2[3] = 255; disparableAsteroides[3] = true; estadoAsteroides[3] = 4; }
				break;
			case 4:									// Disparar en 8 direcciones y Fade Out
				disparoD = true;
				contAst2[3] -= 3;
				asteroide2[3].SetAlpha(contAst2[3]);
				asteroide2[3].Draw();
				if(contAst2[3] <= 0) { asteroide2[3].SetPos(rand() % 750, (rand()%450) + 100); contAst2[3] = 0; disparableAsteroides[3] = true; estadoAsteroides[3] = 0; }
				break;
		}
	}

	for(int i = 0; i < 4; i++) {
		if((asteroide2[i].Enable()) && (asteroide2[i].CheckCollision(ship))  && (ship.Enable())) {
			if(disparableAsteroides[i]) {
				ship.AddHP(-aleatorio(15, 30));
				explosion[0].Enable(true);
				explosion[0].SetPos(ship.GetX()-10, ship.GetY()-10);
				ship.Enable(false);

				explosionSnd.Play();
			}
		}
	}


	for(int i = 0; i < 4; i++) {
		if((asteroide2[i].GetHP() <= 0) && (asteroide2[i].GetX() != -300)) {
			explosionSnd.Play();
			game.AddScore(ENEMY3_SCORE);

			numExp++;
			explosion[numExp].SetPos(asteroide2[i].GetX() + ((rand() % 61) - 30), asteroide2[i].GetY() + ((rand() % 61) - 30));
			explosion[numExp].Enable(true);

			if(numExp == MAX_EXPLOSIONS-1) {
				numExp = 1;
			}

			cont2Ast2[i]--;
			asteroide2[i].SetAlpha(cont2Ast2[i]);

			asteroide2[i].Draw();

			if(cont2Ast2[i] <= 0) {
				muertes2 += 1;
				enemigosDestruidos++;
				if(asteroide2[i].GetItem() != -1)
					createItem(asteroide2[i].GetX(), asteroide2[i].GetY(), asteroide2[i].GetItem());
				asteroide2[i].SetX(-300);
				asteroide2[i].Enable(false);
			}
		}
	}

	updateEnemyBullet();
}

void updateEnemyBullet() {
	if(disparoA) {
		shotA[0].AddX(5); shotA[1].AddPos(4, 4); shotA[2].AddY(5); shotA[7].AddY(-5);
		shotA[3].AddPos(-4, 4); shotA[4].AddX(-5); shotA[5].AddPos(4, -4); shotA[6].AddPos(-4, -4);
		for(int i = 0; i < 8; i++) {
			shotA[i].Draw(0);
		}
	}
	if(disparoB) {
		shotB[0].AddX(5); shotB[1].AddPos(4, 4); shotB[2].AddY(5); shotB[7].AddY(-5);
		shotB[3].AddPos(-4, 4); shotB[4].AddX(-5); shotB[5].AddPos(4, -4); shotB[6].AddPos(-4, -4);
		for(int i = 0; i < 8; i++) {
			shotB[i].Draw(0);
		}
	}
	if(disparoC) {
		shotC[0].AddX(5); shotC[1].AddPos(4, 4); shotC[2].AddY(5); shotC[7].AddY(-5);
		shotC[3].AddPos(-4, 4); shotC[4].AddX(-5); shotC[5].AddPos(4, -4); shotC[6].AddPos(-4, -4);
		for(int i = 0; i < 8; i++) {
			shotC[i].Draw(0);
		}
	}
	if(disparoD) {
		shotD[0].AddX(5); shotD[1].AddPos(4, 4); shotD[2].AddY(5); shotD[7].AddY(-5);
		shotD[3].AddPos(-4, 4); shotD[4].AddX(-5); shotD[5].AddPos(4, -4); shotD[6].AddPos(-4, -4);
		for(int i = 0; i < 8; i++) {
			shotD[i].Draw(0);
		}
	}

	for(int i = 0; i < 8; i++) {
		if((shotA[i].CheckCollision(ship))  && (ship.Enable())) {
			if(shield.Enable()) {
				explosion[0].Enable(true);
				explosion[0].SetPos(shotA[i].GetX(), shotA[i].GetY());
			}
			else {
				ship.AddHP(-aleatorio(15, 30));
				explosion[0].Enable(true);
				explosion[0].SetPos(ship.GetX()-10, ship.GetY()-10);
				ship.Enable(false);
			}
			explosionSnd.Play();
		}
		if((shotB[i].CheckCollision(ship))  && (ship.Enable())) {
			if(shield.Enable()) {
				explosion[0].Enable(true);
				explosion[0].SetPos(shotB[i].GetX(), shotB[i].GetY());
			}
			else {
				ship.AddHP(-aleatorio(15, 30));
				explosion[0].Enable(true);
				explosion[0].SetPos(ship.GetX()-10, ship.GetY()-10);
				ship.Enable(false);
			}
			explosionSnd.Play();
		}
		if((shotC[i].CheckCollision(ship))  && (ship.Enable())) {
			if(shield.Enable()) {
				explosion[0].Enable(true);
				explosion[0].SetPos(shotC[i].GetX(), shotC[i].GetY());
			}
			else {
				ship.AddHP(-aleatorio(15, 30));
				explosion[0].Enable(true);
				explosion[0].SetPos(ship.GetX()-10, ship.GetY()-10);
				ship.Enable(false);
			}
			explosionSnd.Play();
		}
		if((shotD[i].CheckCollision(ship))  && (ship.Enable())) {
			if(shield.Enable()) {
				explosion[0].Enable(true);
				explosion[0].SetPos(shotD[i].GetX(), shotD[i].GetY());
			}
			else {
				ship.AddHP(-aleatorio(15, 30));
				explosion[0].Enable(true);
				explosion[0].SetPos(ship.GetX()-10, ship.GetY()-10);
				ship.Enable(false);
			}
			explosionSnd.Play();
		}
	}
}

void updateEnemyBullet2() {
	if(disparoMinion[0]) {
		shotA[0].AddX(5); shotA[1].AddPos(4, 4); shotA[2].AddY(5); shotA[7].AddY(-5);
		shotA[3].AddPos(-4, 4); shotA[4].AddX(-5); shotA[5].AddPos(4, -4); shotA[6].AddPos(-4, -4);
		for(int i = 0; i < 8; i++) {
			shotA[i].Draw(0);
		}
	}
	if(disparoMinion[1]) {
		shotB[0].AddX(5); shotB[1].AddPos(4, 4); shotB[2].AddY(5); shotB[7].AddY(-5);
		shotB[3].AddPos(-4, 4); shotB[4].AddX(-5); shotB[5].AddPos(4, -4); shotB[6].AddPos(-4, -4);
		for(int i = 0; i < 8; i++) {
			shotB[i].Draw(0);
		}
	}
	if(disparoMinion[2]) {
		shotC[0].AddX(5); shotC[1].AddPos(4, 4); shotC[2].AddY(5); shotC[7].AddY(-5);
		shotC[3].AddPos(-4, 4); shotC[4].AddX(-5); shotC[5].AddPos(4, -4); shotC[6].AddPos(-4, -4);
		for(int i = 0; i < 8; i++) {
			shotC[i].Draw(0);
		}
	}

	for(int i = 0; i < 8; i++) {
		if((shotA[i].CheckCollision(ship))  && (ship.Enable())) {
			if(shield.Enable()) {
				explosion[0].Enable(true);
				explosion[0].SetPos(shotA[i].GetX(), shotA[i].GetY());
			}
			else {
				ship.AddHP(-aleatorio(15, 30));
				explosion[0].Enable(true);
				explosion[0].SetPos(ship.GetX()-10, ship.GetY()-10);
				ship.Enable(false);
			}
			explosionSnd.Play();
		}
		if((shotB[i].CheckCollision(ship))  && (ship.Enable())) {
			if(shield.Enable()) {
				explosion[0].Enable(true);
				explosion[0].SetPos(shotB[i].GetX(), shotB[i].GetY());
			}
			else {
				ship.AddHP(-aleatorio(15, 30));
				explosion[0].Enable(true);
				explosion[0].SetPos(ship.GetX()-10, ship.GetY()-10);
				ship.Enable(false);
			}
			explosionSnd.Play();
		}
		if((shotC[i].CheckCollision(ship))  && (ship.Enable())) {
			if(shield.Enable()) {
				explosion[0].Enable(true);
				explosion[0].SetPos(shotC[i].GetX(), shotC[i].GetY());
			}
			else {
				ship.AddHP(-aleatorio(15, 30));
				explosion[0].Enable(true);
				explosion[0].SetPos(ship.GetX()-10, ship.GetY()-10);
				ship.Enable(false);
			}
			explosionSnd.Play();
		}
	}
}

// Control de la nave
void shipControl(Uint8* key, Uint8 mouse) {
    int i;
    int libre = -1;
    float angle = atan2f(cursor.GetY() - (ship.GetY()+19), cursor.GetX() - (ship.GetX()+19));
	float grad = (angle * 180)/PI;

    if(!ship.Stop()) {
    	/*
		** Control de la nave con el teclado
		*/
		if(ship.GetVelY() < 10) {
			if(key[SDLK_w] && key[SDLK_d]) {
				accelX *= ACELERACION; accelY *= ACELERACION;
				ship.SetVel(accelX, -accelY);
			}
			else if(key[SDLK_a] && key[SDLK_w]) {
				accelX *= ACELERACION; accelY *= ACELERACION;
				ship.SetVel(-accelX, -accelY);
			}
			else if(key[SDLK_d] && key[SDLK_s]) {
				accelX *= ACELERACION; accelY *= ACELERACION;
				ship.SetVel(accelX, accelY);
			}
			else if(key[SDLK_s] && key[SDLK_a]) {
				accelX *= ACELERACION; accelY *= ACELERACION;
				ship.SetVel(-accelX, accelY);
			}
			else if(key[SDLK_w]) {
				accelY *= ACELERACION;
				ship.SetVelY(-accelY);
			}
			else if(key[SDLK_a]) {
				accelX *= ACELERACION;
				ship.SetVelX(-accelX);
			}
			else if(key[SDLK_s]) {
				accelY *= ACELERACION;
				ship.SetVelY(accelY);
			}
			else if(key[SDLK_d]) {
				accelX *= ACELERACION;
				ship.SetVelX(accelX);
			}
			else {
				accelX /= ACELERACION; accelY /= ACELERACION;
				ship.SetVel(ship.GetVelX()*DECELERACION, ship.GetVelY()*DECELERACION);
			}
		}

		if(ship.GetVelY() > 10) {
			accelX /= ACELERACION; accelY /= ACELERACION;
			ship.SetVel(ship.GetVelX()*DECELERACION, ship.GetVelY()*DECELERACION);
		}

		if(accelX < 1) accelX = 1;
		if(accelY < 1) accelY = 1;
		if(accelX > 3) accelX = 3;
		if(accelY > 3) accelY = 3;

		ship.AddPos(ship.GetVelX(), ship.GetVelY());

		/*
		** Control del ángulo de la nave con el ratón
		*/
		if(grad >= -101.25 && grad < -11.25) {
			if(grad >= -101.25 && grad < -78.75) ship.SetStatus(0);
			else if(grad >= -78.75 && grad < -56.25) ship.SetStatus(1);
			else if(grad >= -56.25 && grad < -33.75) ship.SetStatus(2);
			else if(grad >= -33.75 && grad < -11.25) ship.SetStatus(3);
		}
		else if(grad >= -11.25 && grad < 78.75) {
			if(grad >= -11.25 && grad < 11.25) ship.SetStatus(4);
			else if(grad >= 11.25 && grad < 33.75) ship.SetStatus(5);
			else if(grad >= 33.75 && grad < 56.25) ship.SetStatus(6);
			else if(grad >= 56.25 && grad < 78.75) ship.SetStatus(7);
		}
		else if(grad >= 78.75 && grad < 168.75) {
			if(grad >= 78.75 && grad < 101.25) ship.SetStatus(8);
			else if(grad >= 101.25 && grad < 123.75) ship.SetStatus(9);
			else if(grad >= 123.75 && grad < 146.25) ship.SetStatus(10);
			else if(grad >= 146.25 && grad < 168.75) ship.SetStatus(11);
		}
		else if(grad >= -168.75 && grad < -101.25) {
			if(grad >= -168.75 && grad < -146.25) ship.SetStatus(13);
			else if(grad >= -146.25 && grad < -123.75) ship.SetStatus(14);
			else if(grad >= -123.75 && grad < -101.25) ship.SetStatus(15);
		}
		if (grad >= 168.75 || grad <= -168.75) ship.SetStatus(12);

		/*
		** Disparos
		*/
		if((mouse & SDL_BUTTON(1)) && (ship.GetActionDelay() + 125 < (int)SDL_GetTicks())) {
			for(i = 0; i < MAX_SHOTS; i++) {
				if(shot[i].GetX() == -100) {
					libre = i;
				}
			}

			if(libre >= 0) {
				ship.Shot();
				shotSnd.Play();
				shot[libre].SetPos(ship.GetX(), ship.GetY());
				shot[libre].SetAngle(cos(angle)*shot[libre].GetVelX(), sin(angle)*shot[libre].GetVelY());
			}

			ship.SetActionDelay(SDL_GetTicks());
		}

		/*
		** Blast
		*/
		if((mouse & SDL_BUTTON(3)) && (ship.GetCast() >= 50) && (!blast.Enable()) && (ship.GetMP() >= 33)) {
			artesArcanas = true;
			ship.AddCast(-50);
			ship.AddMP(-33);
			shotSnd.Play();
			blast.SetPos(ship.GetX(), ship.GetY());
			blast.SetAngle(cos(angle)*blast.GetVelX(), sin(angle)*blast.GetVelY());
			blast.Enable(true);
		}
    }

    /*
    ** Dañada
    */
    if(!ship.Enable()) {
        if(ship.GetCont() < 100) {
            ship.Blink();
        }
        else {
            ship.Enable(true);
            ship.ResetCont();
        }
    }
    else {
    	if(!controlNaveFade) ship.SetAlpha(255);
    }

    if(ship.GetHP() <= 0) naveMuerta = true;

    /*
    ** Límites de la pantalla
    */
    if(ship.GetX() > 762) {
        ship.SetX(762);
    }
    else if(ship.GetX() < 0) {
        ship.SetX(0);
    }
    if(ship.GetY() > 562) {
        ship.SetY(562);
    }
    else if(ship.GetY() < 100) {
        ship.SetY(100);
    }
}

// Dibujado / Scroll del mapa
void drawMap(int vel1, int vel2) {
    int i, j;

    (offset1 >= tile1.GetH())?offset1 = 0:offset1 += vel1;
    (offset2 >= tile2.GetH())?offset2 = 0:offset2 += vel2;

    for(i = 0; i < 4; i++) {
        for(j = 0; j < 4; j++) {
            tile1.SetPos(tile1.GetW()*j, tile1.GetH()*i + offset1 - tile1.GetH());
            tile1.Draw();
        }
    }

    for(i = 0; i < 4; i++) {
        for(j = 0; j < 5; j++) {
            tile2.SetPos(tile2.GetW()*j-123, tile2.GetH()*i + offset2 - tile2.GetH());
            tile2.Draw();
        }
    }
}

// Actualizar Explosiones
void updateExpl() {
    int i;

    // La explosión 0 se reserva para la nave
    if(explosion[0].Enable()) {
    	switch(rand() % 2) {
			case 0: explosion[0].AddPos(+1, -2); break;
			case 1: explosion[0].AddPos(-1, -2); break;
    	}
        explosion[0].Draw();
        if(explosion[0].GetFrame() == 5) {
            explosion[0].Enable(false);
        }
    }

    // El resto de explosiones se reservan para los enemigos
    for(i = 1; i < MAX_EXPLOSIONS; i++) {
        if(explosion[i].Enable()) {
        	switch(rand() % 2) {
				case 0: explosion[i].AddPos(+1, -2); break;
				case 1: explosion[i].AddPos(-1, -2); break;
        	}
            explosion[i].Draw();
            if(explosion[i].GetFrame() == 5) {
                explosion[i].Enable(false);
            }
        }
    }
}

// Actualiza el movimiento de las balas
void updateBullets() {
    int i, j;

    ship.AddCast(0.25);

	if(blast.Enable()) {
		blast.AddX(blast.GetAngleX());
		blast.AddY(blast.GetAngleY());

		if(estado == 0) {
			for(i = 0; i < MAX_ASTEROIDS; i++) {
				if(blast.CheckCollision(asteroide[i])) {
					asteroide[i].AddHP(-(aleatorio(50, 80)));
					explosionSnd.Play();
					numExp++;
					explosion[numExp].SetPos(asteroide[i].GetX(), asteroide[i].GetY());
					explosion[numExp].Enable(true);
					if(numExp == MAX_EXPLOSIONS-1) {
						numExp = 1;
					}
				}
			}
		}
		else if(estado == 1) {
			if(numBoss == 0) {
				if(boss[0].Enable()) {
					if(blast.CheckCollision(boss[0])) {
						boss[0].AddHP(-(aleatorio(50, 80)));
						explosionSnd.Play();
						numExp++;
						explosion[numExp].SetPos(blast.GetX(), blast.GetY());
						explosion[numExp].Enable(true);
						if(numExp == MAX_EXPLOSIONS-1) {
							numExp = 1;
						}
					}

					for(j = 0; j < 12; j++) {
						if(blast.CheckCollision(boss0Minion[j])) {
							boss[0].AddHP(-(aleatorio(100, 150)));
							explosionSnd.Play();
							numExp++;
							explosion[numExp].SetPos(blast.GetX(), blast.GetY());
							explosion[numExp].Enable(true);
							if(numExp == MAX_EXPLOSIONS-1) {
								numExp = 1;
							}
						}
					}
				}
			}
		}
		else if(estado == 2) {
			for(j = 0; j < 4; j++) {
				if((asteroide2[j].Enable()) && (disparableAsteroides[j]) && (asteroide2[j].GetHP() > 0)) {
					if(blast.CheckCollision(asteroide2[j])) {
						asteroide2[j].AddHP(-(aleatorio(20, 30)));
						explosionSnd.Play();
						numExp++;
						explosion[numExp].SetPos(asteroide2[j].GetX(), asteroide2[j].GetY());
						explosion[numExp].Enable(true);
						if(numExp == MAX_EXPLOSIONS-1) {
							numExp = 1;
						}
					}
				}
			}
		}
		else if(estado == 3) {
			for(j = 0; j < 3; j++) {
				if(disparableMinions[j]) {
					if(blast.CheckCollision(boss1Minion[j])) {
						boss1Minion[j].AddHP(-(aleatorio(20, 30)));
						explosionSnd.Play();
						numExp++;
						explosion[numExp].SetPos(boss1Minion[j].GetX(), boss1Minion[j].GetY());
						explosion[numExp].Enable(true);
						if(numExp == MAX_EXPLOSIONS-1) {
							numExp = 1;
						}
					}
				}
			}
			if(!boss1Protegido1) {
				if(blast.CheckCollision(boss[1])) {
					boss[1].AddHP(-(aleatorio(20, 30)));
					explosionSnd.Play();
					numExp++;
					explosion[numExp].SetPos(boss[1].GetX(), boss[1].GetY());
					explosion[numExp].Enable(true);
					if(numExp == MAX_EXPLOSIONS-1) {
						numExp = 1;
					}
				}
			}
		}
		else if(estado == 4) {
			if(blast.CheckCollision(cristal)) {
				cristal.AddHP(-(aleatorio(20, 30)));
				explosionSnd.Play();
				numExp++;
				explosion[numExp].SetPos(blast.GetX(), blast.GetY());
				explosion[numExp].Enable(true);
				if(numExp == MAX_EXPLOSIONS-1) {
					numExp = 1;
				}
			}
		}
		else if(estado == 5) {
			if(blast.CheckCollision(boss[2])) {
				boss[2].AddHP(-(aleatorio(20, 30)));
				explosionSnd.Play();
				numExp++;
				explosion[numExp].SetPos(blast.GetX(), blast.GetY());
				explosion[numExp].Enable(true);
				if(numExp == MAX_EXPLOSIONS-1) {
					numExp = 1;
				}
			}
		}

		if((blast.GetX() > 800) || (blast.GetX() < -18) || (blast.GetY() > 590) || (blast.GetY() < 82)) {
			blast.Enable(false);
		}
		else {
			blast.Draw(0);
		}
	}

    for(i = 0; i < MAX_SHOTS; i++) {
        if(shot[i].GetX() != -100) {
            shot[i].AddX(shot[i].GetAngleX());
            shot[i].AddY(shot[i].GetAngleY());

            if(estado == 0) {
				for(j = 0; j < MAX_ASTEROIDS; j++) {
					if(shot[i].CheckCollision(asteroide[j])) {
						asteroide[j].SetVel(asteroide[j].GetVelX()/1.4, asteroide[j].GetVelY()/1.4);
						asteroide[j].AddHP(-(aleatorio(SHIP_MIN_DAMAGE, SHIP_MAX_DAMAGE)));

						shot[i].SetPos(-100, 0);
						explosionSnd.Play();

						numExp++;
						explosion[numExp].SetPos(asteroide[j].GetX(), asteroide[j].GetY());
						explosion[numExp].Enable(true);

						if(numExp == MAX_EXPLOSIONS-1) {
							numExp = 1;
						}
					}
				}
            }
            else if(estado == 1) {
				if(numBoss == 0) {
					if(boss[0].Enable()) {
						if(shot[i].CheckCollision(boss[0])) {
							boss[0].AddHP(-(aleatorio(2, 5)));

							explosionSnd.Play();

							numExp++;
							explosion[numExp].SetPos(shot[i].GetX(), shot[i].GetY());
							explosion[numExp].Enable(true);

							shot[i].SetPos(-100, 0);

							if(numExp == MAX_EXPLOSIONS-1) {
								numExp = 1;
							}
						}

						for(j = 0; j < 12; j++) {
							if(shot[i].CheckCollision(boss0Minion[j])) {
								boss[0].AddHP(-(aleatorio(50, 100)));

								explosionSnd.Play();

								numExp++;
								explosion[numExp].SetPos(shot[i].GetX(), shot[i].GetY());
								explosion[numExp].Enable(true);

								shot[i].SetPos(-100, 0);

								if(numExp == MAX_EXPLOSIONS-1) {
									numExp = 1;
								}
							}
						}
					}
				}
            }
            else if(estado == 2) {
				for(j = 0; j < 4; j++) {
					if((asteroide2[j].Enable()) && (disparableAsteroides[j]) && (asteroide2[j].GetHP() > 0)) {
						if(shot[i].CheckCollision(asteroide2[j])) {
							asteroide2[j].SetVel(asteroide2[j].GetVelX()/1.4, asteroide2[j].GetVelY()/1.4);
							asteroide2[j].AddHP(-(aleatorio(SHIP_MIN_DAMAGE, SHIP_MAX_DAMAGE)));

							shot[i].SetPos(-100, 0);
							explosionSnd.Play();

							numExp++;
							explosion[numExp].SetPos(asteroide2[j].GetX(), asteroide2[j].GetY());
							explosion[numExp].Enable(true);

							if(numExp == MAX_EXPLOSIONS-1) {
								numExp = 1;
							}
						}
					}
				}
            }
            else if(estado == 3) {
				for(j = 0; j < 3; j++) {
					if(disparableMinions[j]) {
						if(shot[i].CheckCollision(boss1Minion[j])) {
							boss1Minion[j].AddHP(-(aleatorio(20, 30)));
							explosionSnd.Play();
							shot[i].SetPos(-100, 0);
							numExp++;
							explosion[numExp].SetPos(boss1Minion[j].GetX(), boss1Minion[j].GetY());
							explosion[numExp].Enable(true);
							if(numExp == MAX_EXPLOSIONS-1) {
								numExp = 1;
							}
						}
					}
            	}
            	if(!boss1Protegido1) {
					if(shot[i].CheckCollision(boss[1])) {
						boss[1].AddHP(-(aleatorio(20, 30)));
						explosionSnd.Play();
						shot[i].SetPos(-100, 0);
						numExp++;
						explosion[numExp].SetPos(boss[1].GetX(), boss[1].GetY());
						explosion[numExp].Enable(true);
						if(numExp == MAX_EXPLOSIONS-1) {
							numExp = 1;
						}
					}
				}
			}
			else if(estado == 4) {
				if(shot[i].CheckCollision(cristal)) {
					cristal.AddHP(-(aleatorio(20, 30)));
					explosionSnd.Play();
					numExp++;
					explosion[numExp].SetPos(shot[i].GetX(), shot[i].GetY());
					explosion[numExp].Enable(true);
					if(numExp == MAX_EXPLOSIONS-1) {
						numExp = 1;
					}
				}
			}
			else if(estado == 5) {
				if(shot[i].CheckCollision(boss[2])) {
					boss[2].AddHP(-(aleatorio(20, 30)));
					explosionSnd.Play();
					numExp++;
					explosion[numExp].SetPos(shot[i].GetX(), shot[i].GetY());
					explosion[numExp].Enable(true);
					shot[i].SetPos(-100, 0);
					if(numExp == MAX_EXPLOSIONS-1) {
						numExp = 1;
					}
				}
			}


            if((shot[i].GetX() > 800) || (shot[i].GetX() < -18) || (shot[i].GetY() > 590) || (shot[i].GetY() < 82)) {
                shot[i].SetPos(-100, 0);
            }
            else {
                shot[i].Draw(0);
            }
        }
    }
}

// Actualiza la energia de los enemigos
void updateBars() {
    int i;

	if(stageReal == 0) {
		for(i = 0; i < MAX_ASTEROIDS; i++) {
			bar1[i].SetX(asteroide[i].GetX() + 9);
			bar1[i].SetY(asteroide[i].GetY() - 2);
			bar2[i].SetX(bar1[i].GetX() + 3);
			bar2[i].SetY(bar1[i].GetY() + 3);
			bar1[i].Draw(0);
			bar2[i].Draw(asteroide[i].GetHP());
		}
	}
	else if(stageReal == 1) {
		if(estado == 3) {
			for(i = 0; i < 3; i++) {
				bar1[i].SetX(boss1Minion[i].GetX() + 7);
				bar1[i].SetY(boss1Minion[i].GetY() - 13);
				bar2[i].SetX(bar1[i].GetX() + 3);
				bar2[i].SetY(bar1[i].GetY() + 3);
				bar1[i].Draw(0);
				bar2[i].Draw(boss1Minion[i].GetHP());
			}
		}
		else {
			for(i = 0; i < 4; i++) {
				if(asteroide2[i].Enable()) {
					bar1[i].SetX(asteroide2[i].GetX() + 7);
					bar1[i].SetY(asteroide2[i].GetY() - 13);
					bar2[i].SetX(bar1[i].GetX() + 3);
					bar2[i].SetY(bar1[i].GetY() + 3);
					bar1[i].Draw(0);
					bar2[i].Draw(asteroide2[i].GetHP());
				}
			}
		}
	}
}

// Actualiza TODA la info del juego
void updateInfo() {
    int hp = ship.GetHP();
    int mp = ship.GetMP();
    int cast = ship.GetCast();

    info.Draw(0);

    if(hp < 0) {
        hp = 0;
        ship.SetHP(0);
    }
    else if(hp > 150) {
        hp = 150;
        ship.SetHP(150);
    }

    if(mp < 0) {
        mp = 0;
        ship.SetMP(0);
    }
    else if(mp > 100) {
        mp = 100;
        ship.SetMP(100);
    }

    if(cast > 100) {
        cast = 100;
        ship.SetCast(100);
    }

    bar[0].Draw(hp);
    texto2.WriteBlended(140, 9, "%d%%", hp);
    bar[1].Draw(mp);
    texto2.WriteBlended(140, 31, "%d%%", mp);
    bar[2].Draw(cast);
    texto2.WriteBlended(140, 53, "%d%%", cast);
    texto2.WriteBlended(150, 75, "%d", game.GetScore());
}

// Destruye todos los enemigos
void destroyAll() {
	int i;

	for(i = 0; i < MAX_ASTEROIDS; i++) {
		asteroide[i].SetHP(0);
	}
}

// Activa el escudo a peticion
void enableShield(bool val) {
	static int contador = 0;
	static int lastUpdate = 0;

	if(val) {
		shield.SetPos(ship.GetX()-13, ship.GetY()-14);
		shield.Draw();
		if(lastUpdate + 75 < (int)SDL_GetTicks()) {
			if(contador == 129) {
				shield.Enable(false);
				contador = 0;
			}
			lastUpdate = SDL_GetTicks();
			contador++;
		}
    }
}

// Transmision entrante
void inTransmission(int num) {
	SDL_Event event;
	Sprite margen, communicator;
	bool loop = true;

    SDL_Rect clip = {0, 0, 800, 600};
    margen.Init(0, 0, 800, 600, 1, 0, 0, 0, "Recursos/GFX/Backgrounds/Margen.png", clip, screen);
    margen.SetAlpha(152);
    margen.SetPos(0, 0);
    clip = {0, 0, 325, 100};
    communicator.Init(0, 0, 325, 100, 1, 0, 0, 0, "Recursos/GFX/Backgrounds/Communicator.png", clip, screen);
    communicator.SetPos(475, 0);
    margen.Draw(0);

	while(loop) {
		limit.Start();
		while(SDL_PollEvent(&event)) {
			if(event.type == SDL_QUIT) {
                SDL_Quit();
            }
            if(event.type == SDL_KEYDOWN) {
                if(event.key.keysym.sym == SDLK_ESCAPE) {
                	return;
                }
                if(event.key.keysym.sym == SDLK_RETURN) {
					return;
                }
                if(event.key.keysym.sym == SDLK_SPACE) {
                	return;
                }
            }
            if(event.type == SDL_MOUSEBUTTONDOWN) {
                if(event.button.button == SDL_BUTTON(1)) {
                	return;
                }
            }
		}

		communicator.Draw(0);

		switch(num) {
			case 0:
				dialogo.WriteDialogue(0, 100, "¡¿Nave Al..BZZZ..a?!");
				dialogo.WriteDialogue(1, 100, "Debes vol...BZZZ..cuant..BZZZ");
				dialogo.WriteDialogue(2, 100, "..BZZZ...");
				break;
			case 1:
				dialogo.WriteDialogue(0, 255, "¡Alerta! Elemento desconocido");
				dialogo.WriteDialogue(1, 255, "aproximandose. Parece bloquear");
				dialogo.WriteDialogue(2, 255, "las comunicaciones de la nave");
				dialogo.WriteDialogue(3, 255, "con el exterior.");
				break;
			case 2:
				dialogo.WriteDialogue(0, 255, "Nave Alpha, al fin. Debes volver");
				dialogo.WriteDialogue(1, 255, "cuanto antes a La Tierra. Un");
				dialogo.WriteDialogue(2, 255, "extraño ser nos está atacando.");
				dialogo.WriteDialogue(3, 255, "¡Date prisa!");
				stage = 1;
				flag = -1;
				controlFade = 1;
				break;
			case 3:
				dialogo.WriteDialogue(0, 255, "Ten mucho cuidado; hemos");
				dialogo.WriteDialogue(1, 255, "avistado unas extrañas");
				dialogo.WriteDialogue(2, 255, "criaturas volando sobre el mar.");
				dialogo.WriteDialogue(3, 255, "No sabemos si son hostiles...");
				asteroide2[0].Enable(true);
				asteroide2[1].Enable(true);
				asteroide2[2].Enable(true);
				asteroide2[3].Enable(true);
				stageReal = 1;
				estado = 2;
				flag = -1;
				break;
			case 4:
				dialogo.WriteDialogue(0, 255, "¿¡Nave Alpha?!");
				dialogo.WriteDialogue(1, 255, "¡Destruye ese totem y todo");
				dialogo.WriteDialogue(2, 255, "esto habrá terminado!");
				flag = -1;
				ship.Stop(false);
				stageReal = 2;
				break;
			case 5:
				dialogo.WriteDialogue(0, 255, "Vaya, vaya.");
				dialogo.WriteDialogue(1, 255, "Así que por fin libre...");
				dialogo.WriteDialogue(2, 255, "Has sido de mucha ayuda...");
				flag = -1;
				break;
			case 6:
				dialogo.WriteDialogue(0, 255, "Pero ya no eres necesario...");
				dialogo.WriteDialogue(1, 255, "¡Me desharé de ti y La Tierra");
				dialogo.WriteDialogue(2, 255, "al fin será mía!");
				flag = -1;
				break;
			case 7:
				dialogo.WriteDialogue(0, 255, "¡¿No... te das cuenta?!");
				dialogo.WriteDialogue(1, 255, "¡Si yo muero tu también morirás!");
				dialogo.WriteDialogue(2, 255, "Soy una proyección de tu AI");
				flag = -1;
				break;
			case 8:
				dialogo.WriteDialogue(0, 255, "que se desarrolló en secreto");
				dialogo.WriteDialogue(1, 255, "durante todo este tiempo.");
				flag = -1;
				break;
			case 9:
				dialogo.WriteDialogue(0, 255, "¡Gracias a mi has llegado hasta");
				dialogo.WriteDialogue(1, 255, "aquí! ¡Y gracias a mi hoy");
				dialogo.WriteDialogue(2, 255, "La Tierra será destruida!");
				flag = -1;
				break;
			case 10:
				dialogo.WriteDialogue(0, 255, "¡Y tu, perecerás conmigo!");
				flag = -1;
				break;
		}

		if(game.Render(screen) == -1) {
            return;
        }
        if(limit.GetTicks() < 1000/FRAMES_PER_SECOND) {
            game.Delay((1000/FRAMES_PER_SECOND) - limit.GetTicks());
        }
	}
}

// ********************************* MENU ********************************** //
int menuControl() {
	SDL_Event event;
	Sprite CE, black, opcion1, opcion2, opcion3, opcion4;
	Pixel Estrella[200];

	SDL_Rect clip;
	float cont1 = 255;
	int cont2 = 0;
	bool loop = true;
	bool fade = false;
	int retorno = 0;

	// Sprites menu principal
    clip = {0, 0, 529, 50};
    CE.Init(0, 0, 529, 50, 1, 0, 0, 0, "Recursos/GFX/Backgrounds/Campo Estelar.png", clip, screen);
    CE.SetPos(140, 300);
    clip = {0, 0, 800, 600};
    black.Init(0, 0, 800, 600, 1, 0, 0, 0, "Recursos/GFX/Backgrounds/Negro.png", clip, screen);
    black.SetPos(0, 0);
    black.SetAlpha(255);

    // 4 Opciones
    clip = {0, 0, 90, 28};
    opcion1.Init(0, 0, 90, 28, 2, 0, 0, 0, "Recursos/GFX/Backgrounds/Texts/Opcion1.png", clip, screen);
    opcion1.SetPos(355, 444);

    clip = {0, 0, 108, 28};
    opcion2.Init(0, 0, 108, 28, 2, 0, 0, 0, "Recursos/GFX/Backgrounds/Texts/Opcion2.png", clip, screen);
    opcion2.SetPos(346, 488);

    clip = {0, 0, 76, 22};
    opcion3.Init(0, 0, 76, 22, 2, 0, 0, 0, "Recursos/GFX/Backgrounds/Texts/Opcion3.png", clip, screen);
    opcion3.SetPos(362, 532);

    // Estrellitas :D
    for(int i = 0; i < 200; i++) {
    	int random = ((rand() % 255) + 50);
		Estrella[i].SetRad((rand() % 180));
		Estrella[i].SetAng(rand() % 65535);
  		Estrella[i].SetSpeed((rand() % 5) + 1);
  		Estrella[i].SetColor(random, random, random);
	}

	/*
	** Secuencia y movimiento de los títulos
	*/
	while(loop) {
		limit.Start();
		Uint8 mouse = SDL_GetMouseState(&mouseX, &mouseY);
		while(SDL_PollEvent(&event)) {
			if(event.type == SDL_QUIT) {
                return 3;
            }
            if(event.type == SDL_KEYDOWN) {
                if(event.key.keysym.sym == SDLK_RETURN) {
                    loop = false;
                }
            }
		}

		if(mouse & SDL_BUTTON(1)) {
			loop = false;
		}

		if(CE.GetY() > 90) CE.AddY(-1);
		else {
			if(CE.GetX() > 20) CE.AddX(-1);
			else {
				if(CE.GetX() <= 20) {
					if(cont2 < 150) NUM.SetAlpha(cont2++);
					else {
						NUM.SetAlpha(255);
						loop = false;
					}
					NUM.Draw();
				}
			}
		}

		CE.Draw(0);
		black.Draw(0);

		if(cont1 > 0) black.SetAlpha(cont1--);
		else black.SetAlpha(0);

		if(game.Render(screen) == -1) {
            return 3;
        }
        if(limit.GetTicks() < 1000/FRAMES_PER_SECOND) {
            game.Delay((1000/FRAMES_PER_SECOND) - limit.GetTicks());
        }
    }

	/*
	** Pantalla de menú final
    */
    CE.SetPos(20, 90);
    loop = true;
	while(loop) {
		limit.Start();
		Uint8 mouse = SDL_GetMouseState(&mouseX, &mouseY);
		while(SDL_PollEvent(&event)) {
			if(event.type == SDL_QUIT) {
				retorno = 3;
                loop = false;
            }
            if(event.type == SDL_KEYDOWN) {
                if(event.key.keysym.sym == SDLK_ESCAPE) {
                    retorno = 3;
					loop = false;
                }
            }
		}

		game.FillRect(screen, &screen->clip_rect, SDL_MapRGB(screen->format, 0, 0, 0));

		CE.Draw(0);
		NUM.Draw();

		for(int i = 0; i < 200; i++) {
			Estrella[i].SetX((800/2) + sin(((2*Estrella[i].GetAng()) * 3.14159265) / 360) * Estrella[i].GetRad());
			Estrella[i].SetY((600/2) + cos(((2*Estrella[i].GetAng()) * 3.14159265) / 360) * Estrella[i].GetRad());
			if((Estrella[i].GetX() < 6) || (Estrella[i].GetX() > 794) || (Estrella[i].GetY() < 6) || (Estrella[i].GetY() > 594)) {
				Estrella[i].SetRad((rand() % 40));
				Estrella[i].SetAng(rand() % 65535);
				Estrella[i].SetSpeed((rand() % 5) + 1);
			}
			Estrella[i].AddRad(Estrella[i].GetSpeed());
			Estrella[i].Draw();
		}

		(cursor.CheckCollision(opcion1))?opcion1.Draw(1):opcion1.Draw(0);
		(cursor.CheckCollision(opcion2))?opcion2.Draw(1):opcion2.Draw(0);
		(cursor.CheckCollision(opcion3))?opcion3.Draw(1):opcion3.Draw(0);

		if((cursor.CheckCollision(opcion1)) && (mouse & SDL_BUTTON(1))) {
			retorno = 0;
			fade = true;
			cont1 = 0;
			loop = false;
		}
		else if((cursor.CheckCollision(opcion2)) && (mouse & SDL_BUTTON(1))) {
			logros();
		}
		else if((cursor.CheckCollision(opcion3)) && (mouse & SDL_BUTTON(1))) {
			retorno = 3;
			loop = false;
		}

		texto2.WriteBlended(5, 580, "Max Score: %.0f ", maxScore);

		cursor.SetPos(mouseX - (cursor.GetOffsetW() >> 1), mouseY - (cursor.GetOffsetH() >> 1));
		cursor.Draw(0);

		if(game.Render(screen) == -1) {
            return 0;
        }
        if(limit.GetTicks() < 1000/FRAMES_PER_SECOND) {
            game.Delay((1000/FRAMES_PER_SECOND) - limit.GetTicks());
        }
    }

    return retorno;
}

void dificultad() {
	SDL_Event event;
	SDL_Rect clip;

	Sprite facil, normal, dificil, locura;
	Pixel Estrella[200];

	bool loop = true;

	clip = {0, 0, 76, 24};
	facil.Init(0, 0, 76, 24, 2, 0, 0, 0, "Recursos/GFX/Backgrounds/Texts/Op11.png", clip, screen);
    facil.SetPos(354, 232);

    clip = {0, 0, 112, 22};
	normal.Init(0, 0, 112, 22, 2, 0, 0, 0, "Recursos/GFX/Backgrounds/Texts/Op12.png", clip, screen);
    normal.SetPos(338, 289);

    clip = {0, 0, 96, 24};
	dificil.Init(0, 0, 96, 24, 2, 0, 0, 0, "Recursos/GFX/Backgrounds/Texts/Op13.png", clip, screen);
    dificil.SetPos(345, 344);

    clip = {0, 0, 106, 22};
	locura.Init(0, 0, 106, 22, 2, 0, 0, 0, "Recursos/GFX/Backgrounds/Texts/Op14.png", clip, screen);
    locura.SetPos(341, 398);

	// Estrellitas :D
    for(int i = 0; i < 200; i++) {
    	int random = ((rand() % 255) + 50);
		Estrella[i].SetRad((rand() % 180));
		Estrella[i].SetAng(rand() % 65535);
  		Estrella[i].SetSpeed((rand() % 5) + 1);
  		Estrella[i].SetColor(random, random, random);
	}

	while(loop) {
		limit.Start();
		Uint8 mouse = SDL_GetMouseState(&mouseX, &mouseY);
		while(SDL_PollEvent(&event)) {
			if(event.type == SDL_QUIT) {
				TTF_CloseFont(texto1.GetFont());
				TTF_CloseFont(texto2.GetFont());
				game.Quit();
            }
		}

		game.FillRect(screen, &screen->clip_rect, SDL_MapRGB(screen->format, 0, 0, 0));

		for(int i = 0; i < 200; i++) {
			Estrella[i].SetX((800/2) + sin(((2*Estrella[i].GetAng()) * 3.14159265) / 360) * Estrella[i].GetRad());
			Estrella[i].SetY((600/2) + cos(((2*Estrella[i].GetAng()) * 3.14159265) / 360) * Estrella[i].GetRad());
			if((Estrella[i].GetX() < 6) || (Estrella[i].GetX() > 794) || (Estrella[i].GetY() < 6) || (Estrella[i].GetY() > 594)) {
				Estrella[i].SetRad((rand() % 40));
				Estrella[i].SetAng(rand() % 65535);
				Estrella[i].SetSpeed((rand() % 5) + 1);
			}
			Estrella[i].AddRad(Estrella[i].GetSpeed());
			Estrella[i].Draw();
		}

		(cursor.CheckCollision(facil))?facil.Draw(1):facil.Draw(0);
		(cursor.CheckCollision(normal))?normal.Draw(1):normal.Draw(0);
		(cursor.CheckCollision(dificil))?dificil.Draw(1):dificil.Draw(0);
		(cursor.CheckCollision(locura))?locura.Draw(1):locura.Draw(0);

		if((cursor.CheckCollision(facil)) && (mouse & SDL_BUTTON(1))) {
			game.SetDifficulty(0);
			loop = false;
		}
		else if((cursor.CheckCollision(normal)) && (mouse & SDL_BUTTON(1))) {
			game.SetDifficulty(1);
			loop = false;
		}
		else if((cursor.CheckCollision(dificil)) && (mouse & SDL_BUTTON(1))) {
			game.SetDifficulty(2);
			loop = false;
		}
		else if((cursor.CheckCollision(locura)) && (mouse & SDL_BUTTON(1))) {
			game.SetDifficulty(3);
			loop = false;
		}

		cursor.SetPos(mouseX - (cursor.GetOffsetW() >> 1), mouseY - (cursor.GetOffsetH() >> 1));
		cursor.Draw(0);

		game.Render(screen);
        if(limit.GetTicks() < 1000/FRAMES_PER_SECOND) {
            game.Delay((1000/FRAMES_PER_SECOND) - limit.GetTicks());
        }
    }
}

void tutorial() {
	Sprite black, tuto;
	SDL_Rect clip = {0, 0, 800, 600};
	SDL_Event event;
	float cont1 = 0;
	int volumen = 128;

	black.Init(0, 0, 800, 600, 1, 0, 0, 0, "Recursos/GFX/Backgrounds/Negro.png", clip, screen);
    black.SetPos(0, 0);
	black.SetAlpha(0);

	tuto.Init(0, 0, 800, 600, 1, 0, 0, 0, "Recursos/GFX/Backgrounds/Tutorial.png", clip, screen);
    tuto.SetPos(0, 0);

	Pixel Estrella[200];

	bool loop = true;
	bool fade = true;

	// Estrellitas :D
    for(int i = 0; i < 200; i++) {
    	int random = ((rand() % 255) + 50);
		Estrella[i].SetRad((rand() % 180));
		Estrella[i].SetAng(rand() % 65535);
  		Estrella[i].SetSpeed((rand() % 5) + 1);
  		Estrella[i].SetColor(random, random, random);
	}

	while(loop) {
		limit.Start();
		while(SDL_PollEvent(&event)) {
			if(event.type == SDL_QUIT) {
                loop = false;
            }
            if(event.type == SDL_KEYDOWN) {
                if(event.key.keysym.sym == SDLK_RETURN) {
					loop = false;
                }
            }
            if(event.type == SDL_MOUSEBUTTONDOWN) {
                if(event.button.button == SDL_BUTTON(1)) {
					loop = false;
                }
            }
		}

		game.FillRect(screen, &screen->clip_rect, SDL_MapRGB(screen->format, 0, 0, 0));

		for(int i = 0; i < 200; i++) {
			Estrella[i].SetX((800/2) + sin(((2*Estrella[i].GetAng()) * 3.14159265) / 360) * Estrella[i].GetRad());
			Estrella[i].SetY((600/2) + cos(((2*Estrella[i].GetAng()) * 3.14159265) / 360) * Estrella[i].GetRad());
			if((Estrella[i].GetX() < 6) || (Estrella[i].GetX() > 794) || (Estrella[i].GetY() < 6) || (Estrella[i].GetY() > 594)) {
				Estrella[i].SetRad((rand() % 40));
				Estrella[i].SetAng(rand() % 65535);
				Estrella[i].SetSpeed((rand() % 5) + 1);
			}
			Estrella[i].AddRad(Estrella[i].GetSpeed());
			Estrella[i].Draw();
		}

		tuto.Draw(0);

		game.Render(screen);
        if(limit.GetTicks() < 1000/FRAMES_PER_SECOND) {
            game.Delay((1000/FRAMES_PER_SECOND) - limit.GetTicks());
        }
	}

    while(fade) {
		limit.Start();
		while(SDL_PollEvent(&event)) {
			if(event.type == SDL_QUIT) {
				fade = false;
			}
		}

		menu2.Volume(volumen--);

		black.Draw(0);
		cont1 += 0.25;
		if(cont1 < 35) black.SetAlpha(cont1);
		else {
			fade = false;
		}

		game.Render(screen);
        if(limit.GetTicks() < 1000/FRAMES_PER_SECOND) {
            game.Delay((1000/FRAMES_PER_SECOND) - limit.GetTicks());
        }
    }
}

void logros() {
	SDL_Event event;
	bool loop = true;
	SDL_Rect rect = {0, 0, 800, 600};
	SDL_Rect rectLogro[12];
	SDL_Surface* logro = loadImage("Recursos/GFX/Backgrounds/Logros/LogrosFinal.png");

	rectLogro[0] = {16, 16, 365, 90};
	rectLogro[1] = {16, 112, 365, 90};
	rectLogro[2] = {16, 208, 365, 90};
	rectLogro[3] = {16, 304, 365, 90};
	rectLogro[4] = {16, 400, 365, 90};
	rectLogro[5] = {16, 496, 365, 90};
	rectLogro[6] = {416, 16, 365, 90};
	rectLogro[7] = {416, 112, 365, 90};
	rectLogro[8] = {416, 208, 365, 90};
	rectLogro[9] = {416, 304, 365, 90};
	rectLogro[10] = {416, 400, 365, 90};
	rectLogro[11] = {416, 496, 365, 90};

	Pixel Estrella[200];

	// Estrellitas :D
    for(int i = 0; i < 200; i++) {
    	int random = ((rand() % 255) + 50);
		Estrella[i].SetRad((rand() % 180));
		Estrella[i].SetAng(rand() % 65535);
  		Estrella[i].SetSpeed((rand() % 5) + 1);
  		Estrella[i].SetColor(random, random, random);
	}

	while(loop) {
		limit.Start();
		Uint8 mouse = SDL_GetMouseState(&mouseX, &mouseY);
		while(SDL_PollEvent(&event)) {
			if(event.type == SDL_QUIT) {
				SDL_Quit();
			}
			if(event.key.keysym.sym == SDLK_ESCAPE) {
				loop = false;
			}
		}

		if(mouse & SDL_BUTTON(3)) {
			loop = false;
		}

		game.FillRect(screen, &screen->clip_rect, SDL_MapRGB(screen->format, 0, 0, 0));

		for(int i = 0; i < 200; i++) {
			Estrella[i].SetX((800/2) + sin(((2*Estrella[i].GetAng()) * 3.14159265) / 360) * Estrella[i].GetRad());
			Estrella[i].SetY((600/2) + cos(((2*Estrella[i].GetAng()) * 3.14159265) / 360) * Estrella[i].GetRad());
			if((Estrella[i].GetX() < 6) || (Estrella[i].GetX() > 794) || (Estrella[i].GetY() < 6) || (Estrella[i].GetY() > 594)) {
				Estrella[i].SetRad((rand() % 40));
				Estrella[i].SetAng(rand() % 65535);
				Estrella[i].SetSpeed((rand() % 5) + 1);
			}
			Estrella[i].AddRad(Estrella[i].GetSpeed());
			Estrella[i].Draw();
		}

		SDL_BlitSurface(logro, NULL, screen, &rect);

		if(facilPasado) SDL_BlitSurface(logro0, NULL, screen, &rectLogro[0]);
		if(normalPasado) SDL_BlitSurface(logro1, NULL, screen, &rectLogro[1]);
		if(dificilPasado) SDL_BlitSurface(logro2, NULL, screen, &rectLogro[2]);
		if(locuraPasado) SDL_BlitSurface(logro3, NULL, screen, &rectLogro[3]);
		if(medallaBronce) SDL_BlitSurface(logro4, NULL, screen, &rectLogro[4]);
		if(medallaPlata) SDL_BlitSurface(logro5, NULL, screen, &rectLogro[5]);
		if(medallaOro) SDL_BlitSurface(logro6, NULL, screen, &rectLogro[6]);
		if(medallaPlatino) SDL_BlitSurface(logro7, NULL, screen, &rectLogro[7]);
		if(destructor) SDL_BlitSurface(logro9, NULL, screen, &rectLogro[9]);
		if(taumaturgo) SDL_BlitSurface(logro10, NULL, screen, &rectLogro[10]);
		if(campeon) SDL_BlitSurface(logro11, NULL, screen, &rectLogro[11]);

		SDL_BlitSurface(logro8, NULL, screen, &rectLogro[8]);

		game.Render(screen);
		if(limit.GetTicks() < 1000/FRAMES_PER_SECOND) {
			game.Delay((1000/FRAMES_PER_SECOND) - limit.GetTicks());
		}
	}

	SDL_FreeSurface(logro);
}

int creditosFinales() {
	SDL_Event event;
	bool loop = true;
	SDL_Rect rect = {0, 600, 800, 600};
	SDL_Rect pos = {0, 600, 800, 600};

	Pixel Estrella[200];

	// Estrellitas :D
    for(int i = 0; i < 200; i++) {
    	int random = ((rand() % 255) + 50);
		Estrella[i].SetRad((rand() % 180));
		Estrella[i].SetAng(rand() % 65535);
  		Estrella[i].SetSpeed((rand() % 5) + 1);
  		Estrella[i].SetColor(random, random, random);
	}

	SDL_Surface* credits = loadImage("Recursos/GFX/Backgrounds/Creditos.png");

	creditos.Play();

	if(artesArcanas == false) taumaturgo = true;
	if(danio == 0) campeon = true;

	if(game.GetScore() > maxScore) maxScore = game.GetScore();

	// Escribimos los resultados en un archivo
	FILE* f1;
    f1 = fopen ("save", "w");
    int valor[11];

	(facilPasado)?(valor[0] = 1):(valor[0] = 0);
	(normalPasado)?(valor[1] = 1):(valor[1] = 0);
	(dificilPasado)?(valor[2] = 1):(valor[2] = 0);
	(locuraPasado)?(valor[3] = 1):(valor[3] = 0);
	(medallaBronce)?(valor[4] = 1):(valor[4] = 0);
	(medallaPlata)?(valor[5] = 1):(valor[5] = 0);
	(medallaOro)?(valor[6] = 1):(valor[6] = 0);
	(medallaPlatino)?(valor[7] = 1):(valor[7] = 0);
	(destructor)?(valor[8] = 1):(valor[8] = 0);
	(taumaturgo)?(valor[9] = 1):(valor[9] = 0);
	(campeon)?(valor[10] = 1):(valor[10] = 0);

	fprintf(f1, "%d:%d:%d:%d:%d:%d:%d:%d:%d:%d:%d:%.0f",
				valor[0], valor[1], valor[2], valor[3], valor[4], valor[5],
				valor[6], valor[7], valor[8], valor[9], valor[10], maxScore);

	fclose(f1);
	//////////////////////////////////////////

	while(loop) {
		limit.Start();
		while(SDL_PollEvent(&event)) {
			if(event.type == SDL_QUIT) {
				SDL_Quit();
			}
			if(event.type == SDL_MOUSEBUTTONDOWN) {
                if(event.button.button == SDL_BUTTON(1)) {		// Boton izquierdo; seguir jugando
                	creditos.Stop();
                	back.Play();
                	reset();
                	initSprites();
                	creditosActivados = false;
                	SDL_FreeSurface(credits);
                	return 1;
                }
            }
            if(event.key.keysym.sym == SDLK_ESCAPE) {	// Boton derecho; volver al menu
				creditos.Stop();
				creditosActivados = false;
				SDL_FreeSurface(credits);
				return 0;
			}
		}

		if(pos.y > -5100) {
			pos.y -= 1;
		}
		rect.y = pos.y;

		game.FillRect(screen, &screen->clip_rect, SDL_MapRGB(screen->format, 0, 0, 0));

		for(int i = 0; i < 200; i++) {
			Estrella[i].SetColor(aleatorio(0, 255), aleatorio(0, 255), aleatorio(0, 255));
			Estrella[i].SetX((800/2) + sin(((2*Estrella[i].GetAng()) * 3.14159265) / 360) * Estrella[i].GetRad());
			Estrella[i].SetY((600/2) + cos(((2*Estrella[i].GetAng()) * 3.14159265) / 360) * Estrella[i].GetRad());
			if((Estrella[i].GetX() < 6) || (Estrella[i].GetX() > 794) || (Estrella[i].GetY() < 6) || (Estrella[i].GetY() > 594)) {
				Estrella[i].SetRad((rand() % 40));
				Estrella[i].SetAng(rand() % 65535);
				Estrella[i].SetSpeed((rand() % 5) + 1);
			}
			Estrella[i].AddRad(Estrella[i].GetSpeed());
			Estrella[i].Draw();
		}

		SDL_BlitSurface(credits, NULL, screen, &rect);

		game.Render(screen);
		if(limit.GetTicks() < 1000/FRAMES_PER_SECOND) {
			game.Delay((1000/FRAMES_PER_SECOND) - limit.GetTicks());
		}
	}
	return -1;
}

void muerto() {
	SDL_Event event;
	int contFade = 0;

	bool loop = true;

	SDL_Rect rect = {0, 0, 800, 600};
	SDL_Surface* red = loadImage("Recursos/GFX/Backgrounds/Rojo.png");
	SDL_SetAlpha(red, SDL_SRCALPHA | SDL_RLEACCEL, 0);

	while(loop) {
		limit.Start();
		while(SDL_PollEvent(&event)) {
			if(event.type == SDL_QUIT) {
				TTF_CloseFont(texto1.GetFont());
				TTF_CloseFont(texto2.GetFont());
				game.Quit();
            }
            if(event.button.button == SDL_BUTTON(1)) {		// Boton izquierdo; seguir jugando
				loop = false;
			}
		}

		SDL_BlitSurface(red, NULL, screen, &rect);
		SDL_SetAlpha(red, SDL_SRCALPHA | SDL_RLEACCEL, contFade);

		if(contFade < 5) contFade++;

		game.Render(screen);
        if(limit.GetTicks() < 1000/FRAMES_PER_SECOND) {
            game.Delay((1000/FRAMES_PER_SECOND) - limit.GetTicks());
        }
    }

	jefe.Stop();
    back.Play();

	reset();
	initSprites();

    SDL_FreeSurface(red);
}

// ******************************** MOCHILA ******************************** //
void updateItemsMenu() {
    int i;

    for(i = 0; i < MAX_ITEMS; i++) {                                        // Recorremos todo el array de objetos
        if((ship.CheckCollision(item[i])) && (item[i].Colision())) {        // Si la nave colisiona con uno de ellos y ese mismo está activado...
            if(hueco[0] == -1) {
            	getItem.Enable(true);
            	item[i].SetPos(286, 28);
            	item[i].SetHueco(0);
            	item[i].Ocupado(true);
            	item[i].Colision(false);
            	hueco[0] = 1;
            }
            else if(hueco[1] == -1) {
            	getItem.Enable(true);
            	item[i].SetPos(349, 28);
            	item[i].SetHueco(1);
            	item[i].Ocupado(true);
            	item[i].Colision(false);
            	hueco[1] = 1;
            }
            else if(hueco[2] == -1) {
            	getItem.Enable(true);
            	item[i].SetPos(412, 28);
            	item[i].SetHueco(2);
            	item[i].Ocupado(true);
            	item[i].Colision(false);
            	hueco[2] = 1;
            }
            else if(hueco[3] == -1) {
            	getItem.Enable(true);
            	item[i].SetPos(286, 61);
            	item[i].SetHueco(3);
            	item[i].Ocupado(true);
            	item[i].Colision(false);
            	hueco[3] = 1;
            }
            else if(hueco[4] == -1) {
            	getItem.Enable(true);
            	item[i].SetPos(349, 61);
            	item[i].SetHueco(4);
            	item[i].Ocupado(true);
            	item[i].Colision(false);
            	hueco[4] = 1;
            }
            else if(hueco[5] == -1) {
            	getItem.Enable(true);
            	item[i].SetPos(412, 61);
            	item[i].SetHueco(5);
            	item[i].Ocupado(true);
            	item[i].Colision(false);
            	hueco[5] = 1;
            }
        }
    }

    for(i = 0; i < MAX_ITEMS; i++) {                                        // Recorremos todos los objetos
        if(item[i].Enable())                                                // Si hay alguno activado...
            item[i].Draw();                                                 // ...lo dibujamos
    }

    if(getItem.Enable()) {
		getItem.SetPos(ship.GetX()+2, ship.GetY()+1);
		getItem.Draw();
		if(getItem.GetFrame() == 8) {
            getItem.Enable(false);
        }
    }

    if(potionAnim.Enable() && itemAnim == 1) {
        potionAnim.SetPos(ship.GetX()-10, ship.GetY()-10);
        potionAnim.Draw();
        if(potionAnim.GetFrame() == 16) {
        	itemAnim = 0;
            potionAnim.Enable(false);
        }
    }

    if(etherAnim.Enable() && itemAnim == 1) {
        etherAnim.SetPos(ship.GetX()-10, ship.GetY()-10);
        etherAnim.Draw();
        if(etherAnim.GetFrame() == 16) {
        	itemAnim = 0;
            etherAnim.Enable(false);
        }
    }

    if(shieldAnim.Enable() && itemAnim == 1) {
        shieldAnim.SetPos(ship.GetX()-10, ship.GetY()-10);
        shieldAnim.Draw();
        if(shieldAnim.GetFrame() == 16) {
        	itemAnim = 0;
            shieldAnim.Enable(false);
        }
    }
}

void updateItemsUse(SDL_Event &event) {
    if(event.key.keysym.sym == SDLK_1) {			// Hueco 0
        updateItemUseControl(0);
    }
    else if(event.key.keysym.sym == SDLK_2) {		// Hueco 1
        updateItemUseControl(1);
    }
    else if(event.key.keysym.sym == SDLK_3) {		// Hueco 2
        updateItemUseControl(2);
    }
    else if(event.key.keysym.sym == SDLK_4) {		// Hueco 3
        updateItemUseControl(3);
    }
    else if(event.key.keysym.sym == SDLK_5) {		// Hueco 4
        updateItemUseControl(4);
    }
    else if(event.key.keysym.sym == SDLK_6) {		// Hueco 5
        updateItemUseControl(5);
    }
}

void updateItemUseControl(int num) {
    if(hueco[num] == 1) {
        for(int i = 0; i < MAX_ITEMS; i++) {
            if(item[i].GetHueco() == num) {
                if(item[i].GetType() == ITEM_POTION) {
					numItem[ITEM_POTION]--;
					potionSnd.Play();
					ship.AddHP(aleatorio(25, 50));
					potionAnim.SetPos(ship.GetX(), ship.GetY());
					potionAnim.Enable(true);
					item[i].SetX(-200);
					item[i].Enable(false);
					item[i].Colision(true);
					item[i].SetHueco(-1);
					itemAnim = 1;
					numTotalItem--;
					hueco[num] = -1;
                }
				else if(item[i].GetType() == ITEM_ETHER) {
					numItem[ITEM_ETHER]--;
					potionSnd.Play();
					ship.AddMP(aleatorio(25, 50));
					etherAnim.SetPos(ship.GetX(), ship.GetY());
					etherAnim.Enable(true);
					item[i].SetX(-200);
					item[i].Enable(false);
					item[i].Colision(true);
					item[i].SetHueco(-1);
					itemAnim = 1;
					numTotalItem--;
					hueco[num] = -1;
				}
				else if((item[i].GetType() == ITEM_SHIELD) && (!shield.Enable())) {
					numItem[ITEM_SHIELD]--;
					potionSnd.Play();
					shieldAnim.Enable(true);
					shield.Enable(true);
					item[i].SetX(-200);
					item[i].Enable(false);
					item[i].Colision(true);
					item[i].SetHueco(-1);
					itemAnim = 1;
					numTotalItem--;
					hueco[num] = -1;
                }
            }
        }
    }
}

void createItem(int x, int y, int num) {
	if(num == ITEM_POTION) {
		item[numItem[ITEM_POTION]].Enable(true);
		item[numItem[ITEM_POTION]].SetType(ITEM_POTION);
		item[numItem[ITEM_POTION]].Ocupado(true);
		if(y < 100) item[numItem[ITEM_POTION]].SetPos(x, 100);
		else item[numItem[ITEM_POTION]].SetPos(x, y);
		if(numItem[ITEM_POTION] == 9) numItem[ITEM_POTION] = 0;
		else numItem[ITEM_POTION]++;
	}
	else if(num == ITEM_ETHER) {
		item[numItem[ITEM_ETHER]].Enable(true);
		item[numItem[ITEM_ETHER]].SetType(ITEM_ETHER);
		item[numItem[ITEM_ETHER]].Ocupado(true);
		if(y < 100) item[numItem[ITEM_ETHER]].SetPos(x, 100);
		else item[numItem[ITEM_ETHER]].SetPos(x, y);
		if(numItem[ITEM_ETHER] == 19) numItem[ITEM_ETHER] = 10;
		else numItem[ITEM_ETHER]++;
	}
	else if(num == ITEM_SHIELD) {
		item[numItem[ITEM_SHIELD]].Enable(true);
		item[numItem[ITEM_SHIELD]].SetType(ITEM_SHIELD);
		item[numItem[ITEM_SHIELD]].Ocupado(true);
		if(y < 100) item[numItem[ITEM_SHIELD]].SetPos(x, 100);
		else item[numItem[ITEM_SHIELD]].SetPos(x, y);
		if(numItem[ITEM_SHIELD] == 29) numItem[ITEM_SHIELD] = 20;
		else numItem[ITEM_SHIELD]++;
	}
	numTotalItem++;
}

void deleteItems() {
	for(int i = 0; i < MAX_ITEMS; i++) {
		item[i].SetX(-200);
		item[i].Enable(false);
		item[i].Colision(true);
		item[i].SetHueco(-1);
	}
}

// ******************************** BOSS ********************************** //
void bossLife(int num) {
	switch(status) {
		case 0:
			rectBossLife.y--;
			if(rectBossLife.y <= 555) status = 1;
			SDL_BlitSurface(barraBossSprite, NULL, screen, &rectBossLife);
			break;

		case 1:
			SDL_BlitSurface(barraBossSprite, NULL, screen, &rectBossLife);
			barraBoss[num].Draw(boss[num].GetHP());
			texto1.WriteBlended(380, 579, "HP: %d   ", boss[num].GetHP());
			if(boss[num].GetHP() <= 0) status = 3;
			break;

		case 2:
			rectBossLife = {25, 600, 750, 45};
			enemigosDestruidos++;
			status = -1;
			break;

		case 3:
			rectBossLife.y++;
			if(rectBossLife.y >= 600) status = 2;
			SDL_BlitSurface(barraBossSprite, NULL, screen, &rectBossLife);
			break;
	}
}

void drawBoss(int num) {
	int libre = -1;

	switch(num) {
		case 0:
			for(int i = 0; i < 12; i++) {
				boss0Minion[i].Draw();
			}

			boss[0].Draw();

			if(boss[0].Enable()) {
				for(int i = 0; i < 12; i++) {
					boss0Shots[i].AddY((rand()% 5) + 1);

					if(boss0Shots[i].CheckCollision(ship) && ship.Enable()) {
						if(shield.Enable()) {
							explosion[0].Enable(true);
							explosion[0].SetPos(ship.GetX()-10, ship.GetY()-10);
						}
						else {
							danio = 10;
							ship.AddHP(-aleatorio(15, 30));
							explosion[0].Enable(true);
							explosion[0].SetPos(ship.GetX()-10, ship.GetY()-10);
							ship.Enable(false);
						}
						explosionSnd.Play();
					}

					if(boss0Shots[i].GetY() > 600) {
						boss0Shots[i].SetPos(rand() % 800, 0);
					}

					boss0Shots[i].Draw();
				}

				if(rand() % 5 == 3) {
					for(int i = 0; i < 12; i++) {
						boss0Minion[i].AddY(1);
					}
					boss[0].AddY(1);
				}

				if(boss[0].CheckCollision(ship) && ship.Enable()) {
					danio = 10;
					ship.AddHP(-aleatorio(15, 30));
					explosion[0].Enable(true);
					explosion[0].SetPos(ship.GetX()-10, ship.GetY()-10);
					explosionSnd.Play();
					ship.SetVelY(17);
					ship.Enable(false);
				}

				for(int i = 0; i < 12; i++) {
					if(boss0Minion[i].CheckCollision(ship) && ship.Enable()) {
						if(shield.Enable()) {
							boss[0].AddHP(-aleatorio(50, 100));
							explosion[0].Enable(true);
							explosion[0].SetPos(boss[0].GetX(), boss[0].GetY());
						}
						else {
							danio = 10;
							ship.AddHP(-aleatorio(15, 30));
							explosion[0].Enable(true);
							explosion[0].SetPos(ship.GetX()-10, ship.GetY()-10);
							ship.Enable(false);
						}

						explosionSnd.Play();
						ship.SetVelY(17);
					}
				}

				if(boss[0].GetHP() <= 0) {
					boss[0].Enable(false);
				}
			}
			else {
				explosionSnd.Play();

				numExp++;
				explosion[numExp].SetPos(boss[0].GetX() + (rand() % 555), boss[0].GetY() + (rand() % 555));
				explosion[numExp].Enable(true);
				if(numExp == MAX_EXPLOSIONS-1) {
					numExp = 1;
				}
				contBoss--;
				boss[0].SetAlpha(contBoss);
				for(int i = 0; i < 12; i++) {
					boss0Minion[i].SetAlpha(contBoss);
				}
				if(contBoss <= 0) {
					flag = 1;
					numeroJefe = 1;
					contBoss = 0;
				}
			}
			break;

		case 1:
			gravedad0.Draw();
			boss[1].Draw();
			if(boss1Protegido1) boss1Protegido.Draw();

			if(boss[1].Enable()) {
				switch(estadoBoss1) {
					case 0:							// Aparece el circulo gravitatorio gigante
						contBoss += 1;
						gravedad0.SetAlpha(contBoss);
						if(contBoss >= 180) { contBoss = 0; estadoBoss1 = 1; }
						break;
					case 1:							// Aparece el boss con un fade in
						contBoss += 1;
						boss[1].SetAlpha(contBoss);
						if(contBoss >= 255) { contBoss = 0; estadoBoss1 = 2; }
						break;
					case 2:							// Aparece el huevo con un fade in
						contBoss += 1;
						boss1Protegido.SetAlpha(contBoss);
						if(contBoss >= 255) {
							contBoss = 0;
							for(int i = 0; i < 3; i++) {
								gravedad1[i].SetPos(371, 100);
								disparableMinions[i] = false;
							}
							boss1Protegido1 = true;
							estadoBoss1 = 3;
						}
						break;
					case 3:							// Lanza los 3 circulos gravitatorios
						gravedad1[0].AddX(3); gravedad1[0].AddY(3); gravedad1[0].Draw();
						gravedad1[1].AddX(-3); gravedad1[1].AddY(3); gravedad1[1].Draw();
						gravedad1[2].AddY(3); gravedad1[2].Draw();
						for(int i = 0; i < 3; i++) {
							if(gravedad1[i].GetX() > 800) gravedad1[i].SetX(-50);
							else if(gravedad1[i].GetX() < -50) gravedad1[i].SetX(800);
							if(gravedad1[i].GetY() > 600) gravedad1[i].SetY(-50);
							else if(gravedad1[i].GetY() < -50) gravedad1[i].SetY(600);
						}
						contBoss++;
						if(contBoss > 100) {
							contBoss = 0;
							for(int i = 0; i < 3; i++) {
								boss1Minion[i].SetHP(MAX_ENEMY5_HP);
							}
							estadoBoss1 = 4; }
						break;
					case 4:							// Aparecen los 3 minions con un fade in
						contBoss += 1;
						for(int i = 0; i < 3; i++) {
							boss1Minion[i].SetPos(gravedad1[i].GetX()+16, gravedad1[i].GetY()+18);
							gravedad1[i].Draw();
							boss1Minion[i].Draw();
							boss1Minion[i].SetAlpha(contBoss);
						}
						if(contBoss >= 255) { contBoss = 255; estadoBoss1 = 5; }
						break;
					case 5:							// Desaparecen los 3 circulos gravitatorios
						contBoss -= 1;
						for(int i = 0; i < 3; i++) {
							gravedad1[i].Draw();
							boss1Minion[i].Draw();
							gravedad1[i].SetAlpha(contBoss);
						}
						if(contBoss <= 0) {
							contBoss = 0;
							for(int i = 0; i < 3; i++) {
								disparableMinions[i] = true;
							}
							estadoBoss1 = 6;
						}
					case 6:							// Mover los minions 100 píxeles en dirección a la nave
						for(int i = 0; i < 3; i++) {
							if(boss1Minion[i].GetX() != -300) {
								disparableMinions[i] = true;
								if(boss1Minion[i].GetX() < ship.GetX()) boss1Minion[i].AddX((rand()%3)+1);
								if(boss1Minion[i].GetX() > ship.GetX()) boss1Minion[i].AddX(-((rand()%3)+1));
								if(boss1Minion[i].GetY() < ship.GetY()) boss1Minion[i].AddY((rand()%3)+1);
								if(boss1Minion[i].GetY() > ship.GetY()) boss1Minion[i].AddY(-((rand()%3)+1));
								boss1Minion[i].Draw();
							}
						}
						contBoss++;
						if(contBoss >= 100) { contBoss = 255;
						for(int i = 0; i < 3; i++) {
							if(boss1Minion[i].GetX() != -300) {
								disparableMinions[i] = false;
							}
							estadoBoss1 = 7;
						}
						break;
					case 7:							// Fade Out de los minion
						for(int i = 0; i < 3; i++) {
							if(boss1Minion[i].GetX() != -300) {
								disparoMinion[i] = false;
								boss1Minion[i].SetAlpha(contBoss);
								boss1Minion[i].Draw();
							}
						}
						contBoss -= 3;
						if(contBoss <= 0) {
								if(boss1Minion[0].GetX() != -300) boss1Minion[0].SetPos(ship.GetX()-16, ship.GetY()-80);
								if(boss1Minion[1].GetX() != -300) boss1Minion[1].SetPos(ship.GetX()+42, ship.GetY()+31);
								if(boss1Minion[2].GetX() != -300) {boss1Minion[2].SetPos(ship.GetX()-72, ship.GetY()+31);
							}
							contBoss = 0; estadoBoss1 = 8;
						}
						break;
					case 8:							// Fade In de los minions en forma de triangulo en la nave
						contBoss += 3;
						for(int i = 0; i < 3; i++) {
							if(boss1Minion[i].GetX() != -300) {
								boss1Minion[i].SetAlpha(contBoss);
								boss1Minion[i].Draw();
							}
						}
						if(contBoss >= 255) {
							if(boss1Minion[0].GetX() != -300) {
								for(int i = 0; i < 8; i++) {
									shotA[i].SetPos(boss1Minion[0].GetX(), boss1Minion[0].GetY());
								}
							}
							if(boss1Minion[1].GetX() != -300) {
								for(int i = 0; i < 8; i++) {
									shotB[i].SetPos(boss1Minion[1].GetX(), boss1Minion[1].GetY());
								}
							}
							if(boss1Minion[2].GetX() != -300) {
								for(int i = 0; i < 8; i++) {
									shotC[i].SetPos(boss1Minion[2].GetX(), boss1Minion[2].GetY());
								}
							}
							contBoss = 255;
							for(int i = 0; i < 3; i++) {
								if(boss1Minion[i].GetX() != -300) {
									disparableMinions[i] = true;
								}
							}
							estadoBoss1 = 9;
						}
						break;
					case 9:							// Minions disparan en 8 direcciones y Fade Out
						for(int i = 0; i < 3; i++) {
							if(boss1Minion[i].GetX() != -300) {
								disparoMinion[i] = true;
							}
						}

						contBoss -= 3;
						for(int i = 0; i < 3; i++) {
							if(boss1Minion[i].GetX() != -300) {
								boss1Minion[i].SetAlpha(contBoss);
								boss1Minion[i].Draw();
							}
						}
						if(contBoss <= 0) {
							for(int i = 0; i < 3; i++) {
								if(boss1Minion[i].GetX() != -300) {
									boss1Minion[i].SetPos(rand() % 750, (rand()%450) + 100);
								}
							}
							contBoss = 0;
							for(int i = 0; i < 3; i++) {
								if(boss1Minion[i].GetX() != -300) {
									disparableMinions[i] = false;
								}
							}
							estadoBoss1 = 10;
						}
						break;
					case 10:						// Fade In de los minions
						contBoss += 3;
						for(int i = 0; i < 3; i++) {
							if(boss1Minion[i].GetX() != -300) {
								boss1Minion[i].SetAlpha(contBoss);
								boss1Minion[i].Draw();
							}
						}
						if(contBoss >= 255) { contBoss = 0; estadoBoss1 = 6; }
						break;
					case 11:						// Quitar protección boss
						contBoss -= 3;
						boss1Protegido.SetAlpha(contBoss);
						if(contBoss <= 0) { contBoss = 0; boss1Protegido1 = false; estadoBoss1 = 12; }
						break;
					case 12:						// Esperamos unos segundos... y repetimos desde 2
						contSegundosBoss++;
						if(contSegundosBoss >= 300) { contSegundosBoss = 0; boss1Protegido1 = true; contBoss = 0; estadoBoss1 = 2; }
						break;
				}
			}

			for(int i = 0; i < 3; i++) {
				if((boss1Minion[i].GetHP() <= 0) && (boss1Minion[i].GetX() != -300)) {
					enemigosDestruidos++;
					minionsMuertos++;
					boss1Minion[i].SetX(-300);
				}
			}

			if(minionsMuertos == 3) {
				contBoss = 255;
				estadoBoss1 = 11;
				minionsMuertos = 0;
			}

			if(boss[1].CheckCollision(ship) && ship.Enable()) {
				danio = 10;
				ship.AddHP(-aleatorio(15, 30));
				explosion[0].Enable(true);
				explosion[0].SetPos(ship.GetX()-10, ship.GetY()-10);
				explosionSnd.Play();
				ship.Enable(false);
			}

			for(int i = 0; i < 3; i++) {
				if(disparableMinions[i]) {
					if((boss1Minion[i].CheckCollision(ship)) && (ship.Enable())) {
						danio = 10;
						ship.AddHP(-aleatorio(15, 30));
						explosion[0].Enable(true);
						explosion[0].SetPos(ship.GetX()-10, ship.GetY()-10);
						ship.Enable(false);
						explosionSnd.Play();
					}
				}
			}

			if(boss[1].GetHP() <= 0) {
				contBoss = 255;
				boss[1].Enable(false);
			}

			updateEnemyBullet2();
		}
		else {
			controlNaveFade = true;
			ship.Stop(true);
			gravedad0.Draw();

			if(contBoss > 0) {
				explosionSnd.Play();
				game.AddScore(ENEMY4_SCORE);
				numExp++;
				explosion[numExp].SetPos(boss[1].GetX() + ((rand() % 61) - 30), boss[1].GetY() + ((rand() % 61) - 30));
				explosion[numExp].Enable(true);
				if(numExp == MAX_EXPLOSIONS-1) {
					numExp = 1;
				}
				boss[1].SetAlpha(contBoss);
				boss[1].Draw();
				contBoss--;
			}
			else {
				switch(estadoBoss2) {
					case 0:
						contBoss2--;
						gravedad0.SetAlpha(contBoss2);
						if(contBoss2 <= 0) {
							contBoss2 = 0;
							gravedad0.SetPos(ship.GetX() - 185, ship.GetY() - 170);
							estadoBoss2 = 1;
						}
						break;
					case 1:
						contBoss2++;
						gravedad0.SetAlpha(contBoss2);
						if(contBoss2 >= 255) {
							contBoss2 = 0;
							boss1Protegido.SetPos(ship.GetX()-14, ship.GetY()-11);
							absorbeNave = true;
							estadoBoss2 = 2;
						}
						break;
					case 2:
						contBoss2++;
						boss1Protegido.SetAlpha(contBoss2);
						if(contBoss2 >= 255) {
							contBoss2 = 255;
							estadoBoss2 = 3;
						}
						break;
					case 3:
						if(contBoss2 <= 0) {
							stage = 2;
							controlFade = 1;
						}
						else {
							contBoss2--;
							ship.SetAlpha(contBoss2);
							boss1Protegido.SetAlpha(contBoss2);
							gravedad0.SetAlpha(contBoss2);
						}
						break;
				}
			}
		}

		case 2:
			if(cristal.Enable()) {
				if(cristal.GetHP() <= 0) {
					boss[2].SetPos(ship.GetX(), ship.GetY());
					ship.Stop(true);
					cristal.SetPos(-100, -100);
					muertes3 = 1;
					cristal.Enable(false);
				}
				else {
					cristal.Draw();
				}
			}

			if((boss[2].Enable()) && (!cristal.Enable())) {
				float angle = atan2f(boss[2].GetY() - (ship.GetY()+19), boss[2].GetX() - (ship.GetX()+19));
				float grad = (angle * 180)/PI;

				if(grad >= -101.25 && grad < -11.25) {
					if(grad >= -101.25 && grad < -78.75) boss[2].SetStatus(8);
					else if(grad >= -78.75 && grad < -56.25) boss[2].SetStatus(9);
					else if(grad >= -56.25 && grad < -33.75) boss[2].SetStatus(10);
					else if(grad >= -33.75 && grad < -11.25) boss[2].SetStatus(11);
				}
				else if(grad >= -11.25 && grad < 78.75) {
					if(grad >= -11.25 && grad < 11.25) boss[2].SetStatus(12);
					else if(grad >= 11.25 && grad < 33.75) boss[2].SetStatus(13);
					else if(grad >= 33.75 && grad < 56.25) boss[2].SetStatus(14);
					else if(grad >= 56.25 && grad < 78.75) boss[2].SetStatus(15);
				}
				else if(grad >= 78.75 && grad < 168.75) {
					if(grad >= 78.75 && grad < 101.25) boss[2].SetStatus(0);
					else if(grad >= 101.25 && grad < 123.75) boss[2].SetStatus(1);
					else if(grad >= 123.75 && grad < 146.25) boss[2].SetStatus(2);
					else if(grad >= 146.25 && grad < 168.75) boss[2].SetStatus(3);
				}
				else if(grad >= -168.75 && grad < -101.25) {
					if(grad >= -168.75 && grad < -146.25) boss[2].SetStatus(5);
					else if(grad >= -146.25 && grad < -123.75) boss[2].SetStatus(6);
					else if(grad >= -123.75 && grad < -101.25) boss[2].SetStatus(7);
				}
				if (grad >= 168.75 || grad <= -168.75) boss[2].SetStatus(4);

				switch(estadoBoss3) {
					case 0:
						boss[2].Draw(8);
						ship.Stop(false);
						flag = 4;
						estadoBoss3 = 1;
						break;
					case 1:
						jefe.Play();
						if(contBoss3 < 128) {
							contBoss3 += 3;
							jefe.Volume(contBoss3);
						}
						boss[2].Draw(8);
						if(boss[2].GetX() < 381) boss[2].AddX(2);
						if(boss[2].GetX() > 381) boss[2].AddX(-2);
						if(boss[2].GetY() < 189) boss[2].AddY(2);
						if(boss[2].GetY() > 189) boss[2].AddY(-2);
						if((boss[2].GetX() >= 378) && (boss[2].GetY() >= 186) &&
						   (boss[2].GetX() <= 384) && (boss[2].GetY() <= 192)) {
						   	jefe.Volume(80);
							contBoss3 = 255;
							estadoBoss3 = 2;
						}
						break;
					case 2:
						boss[2].Draw(8);
						estado = 5;
						flag = 5;
						estadoBoss3 = 3;
						break;
					case 3:					// Marcamos un punto aleatorio en la pantalla
						boss[2].Draw(boss[2].GetStatus());
						bossX = aleatorio(0, 762);
						bossY = aleatorio(100, 555);
						estadoBoss3 = 4;
						break;
					case 4:					// Movemos el boss hacia ese punto y volvemos a 3
						boss[2].SetStatus(boss[2].GetStatus());
						boss[2].Draw(boss[2].GetStatus());

						if(aleatorio(0, 5) == 3) {
							for(int i = 0; i < MAX_SHOTS; i++) {
								if(shotBoss[i].GetX() == -100) {
									libre = i;
								}
							}

							if(libre >= 0) {
								boss[2].Shot();
								shotBoss[libre].SetPos(boss[2].GetX(), boss[2].GetY());
								shotBoss[libre].SetAngle(-cos(angle)*shotBoss[libre].GetVelX(), -sin(angle)*shotBoss[libre].GetVelY());
							}
						}
						if((aleatorio(0, 10) == 5) && (!blastBoss.Enable())) {
							blastBoss.SetPos(boss[2].GetX(), boss[2].GetY());
							blastBoss.SetAngle(-cos(angle)*blastBoss.GetVelX(), -sin(angle)*blastBoss.GetVelY());
							blastBoss.Enable(true);
						}

						if(boss[2].GetX() < bossX) boss[2].AddX(2);
						if(boss[2].GetX() > bossX) boss[2].AddX(-2);
						if(boss[2].GetY() < bossY) boss[2].AddY(2);
						if(boss[2].GetY() > bossY) boss[2].AddY(-2);

						if((boss[2].GetX() >= bossX-3) && (boss[2].GetY() >= bossY-3) &&
						   (boss[2].GetX() <= bossX+3) && (boss[2].GetY() <= bossY+3)) {
							estadoBoss3 = 3;
						}
						break;
					case 5:
						ship.Stop(true);
						contBoss3 -= 3;
						boss[2].SetAlpha(contBoss3);
						boss[2].Draw(8);
						if(contBoss3 <= 0) {
							contBoss3 = 0;
							boss[2].SetPos(381, 189);
							estadoBoss3 = 6;
						}
						break;
					case 6:
						contBoss3 += 3;
						boss[2].SetAlpha(contBoss3);
						boss[2].Draw(8);
						if(contBoss3 >= 255) {
							contBoss3 = 0;
							estadoBoss3 = 7;
						}
						break;
					case 7:
						boss[2].Draw(8);
						flag = 6;
						estadoBoss3 = 8;
						break;
					case 8:
						boss[2].Draw(8);
						flag = 7;
						estadoBoss3 = 9;
						break;
					case 9:
						boss[2].Draw(8);
						flag = 8;
						estadoBoss3 = 10;
						break;
					case 10:
						boss[2].Draw(8);
						flag = 9;
						estadoBoss3 = 11;
						break;
					case 11:
						boss[2].Draw(8);
						activarBoss3 = true;
						SDL_SetAlpha(blackFade, SDL_SRCALPHA | SDL_RLEACCEL, 0);
						SDL_SetAlpha(whiteFade, SDL_SRCALPHA | SDL_RLEACCEL, 0);
						estadoBoss3 = 12;
						break;
					case 12:
						boss[2].Draw(8);
						if(contBoss3 < 255) {
							SDL_Rect rect = {0, 0, 800, 600};
							SDL_SetAlpha(whiteFade, SDL_SRCALPHA | SDL_RLEACCEL, contBoss3++);
							SDL_BlitSurface(whiteFade, NULL, screen, &rect);

							explosionSnd.Play();
							game.AddScore(ENEMY6_SCORE);
							numExp++;
							explosion[numExp].SetPos(aleatorio(0, 750), aleatorio(0, 550));
							explosion[numExp].Enable(true);
							if(numExp == MAX_EXPLOSIONS-1) {
								numExp = 1;
							}
						}
						else {
							contBoss3 = 0;
							estadoBoss3 = 13;
						}
						break;
					case 13:
						SDL_Rect rect = {0, 0, 800, 600};
						SDL_SetAlpha(blackFade, SDL_SRCALPHA | SDL_RLEACCEL, contBoss3++);
						SDL_BlitSurface(whiteFade, NULL, screen, &rect);
						SDL_BlitSurface(blackFade, NULL, screen, &rect);
						if(contBoss3 >= 255) {
							contBoss = 255;
							contBoss2 = 255;
							contBoss3 = 0;
							contSegundosBoss = 0;
							estadoBoss1 = 0;
							estadoBoss2 = 0;
							estadoBoss3 = 0;
							creditosActivados = true;
							boss[2].Enable(false);
						}
						break;
				}

				if((boss[2].GetHP() <= 0) && (activarBoss2)) {
					if(game.GetDifficulty() == 0) facilPasado = true;
					else if(game.GetDifficulty() == 1) normalPasado = true;
					else if(game.GetDifficulty() == 2) dificilPasado = true;
					else if(game.GetDifficulty() == 3) locuraPasado = true;
					jefe.Stop();
					estadoBoss3 = 5;
					activarBoss2 = false;
				}

				for(int i = 0; i < MAX_SHOTS; i++) {
					if((shotBoss[i].CheckCollision(ship)) && (ship.Enable()) && (boss[2].GetHP() > 0)) {
						if(shield.Enable()) {
							shotBoss[i].SetX(-100);
							explosion[0].Enable(true);
							explosion[0].SetPos(ship.GetX()-10, ship.GetY()-10);
						}
						else {
							shotBoss[i].SetX(-100);
							danio = 10;
							ship.AddHP(-aleatorio(15, 30));
							explosion[0].Enable(true);
							explosion[0].SetPos(ship.GetX()-10, ship.GetY()-10);
							ship.Enable(false);
						}

						explosionSnd.Play();
					}
				}

				if((blastBoss.CheckCollision(ship)) && (ship.Enable()) && (boss[2].GetHP() > 0)) {
					if(shield.Enable()) {
						explosion[0].Enable(true);
						explosion[0].SetPos(ship.GetX()-10, ship.GetY()-10);
					}
					else {
						danio = 10;
						ship.AddHP(-aleatorio(30, 50));
						explosion[0].Enable(true);
						explosion[0].SetPos(ship.GetX()-10, ship.GetY()-10);
						ship.Enable(false);
					}

					explosionSnd.Play();
				}
				updateBossBullet();
			}
		break;
	}
}

void updateBossBullet() {
	for(int i = 0; i < MAX_SHOTS; i++) {
        if(shotBoss[i].GetX() != -100) {
            shotBoss[i].AddX(shotBoss[i].GetAngleX());
            shotBoss[i].AddY(shotBoss[i].GetAngleY());
		}
	}

	if(blastBoss.Enable()) {
		blastBoss.AddX(blastBoss.GetAngleX());
		blastBoss.AddY(blastBoss.GetAngleY());
	}

	if((blastBoss.GetX() > 800) || (blastBoss.GetX() < -18) || (blastBoss.GetY() > 590) || (blastBoss.GetY() < 82)) {
		blastBoss.Enable(false);
	}
	else {
		blastBoss.Draw(0);
	}

	for(int i = 0; i < MAX_SHOTS; i++) {
		if((shotBoss[i].GetX() > 800) || (shotBoss[i].GetX() < -18) || (shotBoss[i].GetY() > 590) || (shotBoss[i].GetY() < 82)) {
			shotBoss[i].SetPos(-100, 0);
		}
		else {
			shotBoss[i].Draw(0);
		}
	}
}

// Genera números aleatorios entre m y n
int aleatorio(int m, int n) {
    return rand()%(n-m+1) + m;
}

// Carga una imagen en una surface
SDL_Surface* loadImage(const char* ruta) {
    SDL_Surface* loadedImage = NULL;
    SDL_Surface* optimizedImage = NULL;

    loadedImage = IMG_Load(ruta);

    if(loadedImage != NULL) {
        optimizedImage = SDL_DisplayFormat(loadedImage);

        SDL_FreeSurface(loadedImage);

        if(optimizedImage != NULL) {
            SDL_SetColorKey(optimizedImage, SDL_SRCCOLORKEY, SDL_MapRGB(optimizedImage->format, 255, 0, 255));
        }
    }

    return optimizedImage;
}

// Carga la configuracion de la dificultad
void start() {
	if(game.GetDifficulty() == 0) {			// Fácil
		MAX_ENEMY1_HP  = 50, ENEMY1_SCORE  = 150;
		MAX_ENEMY2_HP  = 2500, ENEMY2_SCORE  = 1000;
		MAX_ENEMY3_HP  = 500, ENEMY3_SCORE  = 20;
		MAX_ENEMY4_HP  = 2500, ENEMY4_SCORE  = 60;
		MAX_ENEMY5_HP  = 250, ENEMY5_SCORE  = 75;
		MAX_ENEMY6_HP  = 2500, ENEMY6_SCORE  = 90;
	}
	else if(game.GetDifficulty() == 1) {	// Normal
		MAX_ENEMY1_HP  = 75, ENEMY1_SCORE  = 250;
		MAX_ENEMY2_HP  = 5000, ENEMY2_SCORE  = 3000;
		MAX_ENEMY3_HP  = 1000, ENEMY3_SCORE  = 40;
		MAX_ENEMY4_HP  = 5000, ENEMY4_SCORE  = 120;
		MAX_ENEMY5_HP  = 400, ENEMY5_SCORE  = 150;
		MAX_ENEMY6_HP  = 5000, ENEMY6_SCORE  = 180;
	}
	else if(game.GetDifficulty() == 2) {	// Difícil
		MAX_ENEMY1_HP  = 100, ENEMY1_SCORE  = 500;
		MAX_ENEMY2_HP  = 7000, ENEMY2_SCORE  = 6000;
		MAX_ENEMY3_HP  = 1250, ENEMY3_SCORE  = 80;
		MAX_ENEMY4_HP  = 7000, ENEMY4_SCORE  = 240;
		MAX_ENEMY5_HP  = 500, ENEMY5_SCORE  = 300;
		MAX_ENEMY6_HP  = 7000, ENEMY6_SCORE  = 360;
	}
	else if(game.GetDifficulty() == 3) {	// Locura
		MAX_ENEMY1_HP  = 150, ENEMY1_SCORE  = 1000;
		MAX_ENEMY2_HP  = 10000, ENEMY2_SCORE  = 12000;
		MAX_ENEMY3_HP  = 3000, ENEMY3_SCORE  = 160;
		MAX_ENEMY4_HP  = 10000, ENEMY4_SCORE  = 480;
		MAX_ENEMY5_HP  = 700, ENEMY5_SCORE  = 600;
		MAX_ENEMY6_HP  = 10000, ENEMY6_SCORE  = 720;
	}
}

// Fade a negro
void fade() {
	static int cont = 0;
	SDL_Rect rect = {0, 0, 800, 600};
	SDL_Rect clip;
	SDL_SetAlpha(blackFade, SDL_SRCALPHA | SDL_RLEACCEL, cont++);
	SDL_BlitSurface(blackFade, NULL, screen, &rect);
	if(cont >= 255) {
		ship.SetPos(381, 281);
		SDL_SetAlpha(blackFade, SDL_SRCALPHA | SDL_RLEACCEL, 0);
		cont = 0;

		switch(stage) {
			case 1:
				clip = {0, 0, 208, 208};
				tile1.Init(0, 0, 208, 208, "Recursos/GFX/Backgrounds/Sea1.png", clip, screen);
				clip = {0, 0, 256, 256};
				tile2.Init(0, 0, 256, 256, "Recursos/GFX/Backgrounds/Sea2.png", clip, screen);
				tile2.SetColorKey(255, 0, 255);
				tile2.SetAlpha(128);
				for(int i = 0; i < 4; i++) {
					bar2[i].Create(384, 0, 40, 3, asteroide2[i].GetHP(), screen);
				}
				status = 0;
				numCiclo = 0;
				controlFade = 0;
				flag = 2;
				break;
			case 2:
				ship.SetPos(381, 400);
				controlNaveFade = false;
				cristal.Enable(true);
				boss[2].Enable(true);
				back.Stop();
				ship.SetAlpha(255);
				estado = 4;
				numeroJefe = 2;
				numBoss = 2;
				status = 0;
				numCiclo = 0;
				controlFade = 0;
				flag = 3;
				break;
		}
	}
}

void reset() {
  rectBossLife.x = 25;
  rectBossLife.y = 600;
  rectBossLife.w = 750;
  rectBossLife.h = 45;
	contBoss = 255;
	contBoss2 = 255;
	contBoss3 = 0;
	contSegundosBoss = 0;
	estadoBoss1 = 0;
	estadoBoss2 = 0;
	estadoBoss3 = 0;
	contAst2[0] = 0;
	contAst2[1] = 0;
	contAst2[2] = 0;
	contAst2[3] = 0;
	cont2Ast2[0] = 255;
	cont2Ast2[1] = 255;
	cont2Ast2[2] = 255;
	cont2Ast2[3] = 255;
	offset1 = 0;
	offset2 = 0;
	numExp = 1;
	numTotalItem = 0;
	accelX = 1;
	accelY = 1;
	status = 0;
	flag = 100;
	controlFade = 0;
	muertes = 0;
	muertes2 = 0;
	muertes3 = 0;
	estado = 0;
	numBoss = -1;
	numeroJefe = 0;
	minionsMuertos = 0;
	stage = 0;
	stageReal = 0;
	numCiclo = 0;
	estadoAsteroides[0] = 0;
	estadoAsteroides[1] = 0;
	estadoAsteroides[2] = 0;
	estadoAsteroides[3] = 0;
	flagRara = 1;
	activarBoss2 = true;
	activarBoss3 = false;
	creditosActivados = false;
	disparableAsteroides[0] = false;
	disparableAsteroides[1] = false;
	disparableAsteroides[2] = false;
	disparableAsteroides[3] = false;
	disparoA = false;
	disparoB = false;
	disparoC = false;
	disparoD = false;
	disparoMinion[0] = false;
	disparoMinion[1] = false;
	disparoMinion[2] = false;
	disparableMinions[0] = false;
	disparableMinions[1] = false;
	disparableMinions[2] = false;
	absorbeNave = false;
	controlNaveFade = false;
	ship.Stop(false);
	artesArcanas = false;
	boss1Protegido1 = false;
	deleteItems();
	unloadSprites();
}
