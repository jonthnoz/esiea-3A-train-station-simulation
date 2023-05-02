#ifndef MODE1_H
#define MODE1_H
 
/* constant define */
#define SCREEN_WIDTH 1600
#define SCREEN_HEIGHT 690


/* include */
#include "fmodex/inc/fmod.h"	// sound librairy


/* Stucture */
typedef struct _train {			// structure of a train
	int id;							// to identify which train (top or bottom)
	SDL_Rect *trainPosition;		// where to display the train
	SDL_Texture *train_texture; 	// will contain the train image
	int chrono;						// used to controle the doors animation
	int moving;						// state indicator to know if the train is visible in the station (0=no)
	int open;						// state indicator to know if passengers can get in and out of the train (0=no)
} _train;


/* Prototypes */
int init(SDL_Window **window, SDL_Renderer **renderer, int w, int h);
SDL_Texture *loadImage(const char path[], SDL_Renderer *renderer);
int loadImages(SDL_Texture **station, SDL_Texture **menuBackground_texture, SDL_Texture **entrance, SDL_Texture **goinside, SDL_Texture *numbers_texture[21], SDL_Texture *smiley[6], SDL_Renderer *renderer);
void initRects(SDL_Rect choixMenu[3], SDL_Rect doorsRect[2][16]);

int initSchedule();
void updateSchedule(int schedule[4], FMOD_SYSTEM *fmodSystem, FMOD_SOUND *delayed);
void decrementSchedules(int schedule[4], _train *train1, _train *train2);
void displaySchedules(SDL_Renderer *renderer, SDL_Texture *texture[21], int schedule[4]);

int createTrains(_train **train1, _train **train2, SDL_Renderer *renderer);
int moveTrain(_train *train, SDL_Rect doors[16], SDL_Renderer *renderer, FMOD_SYSTEM *fmodSystem, FMOD_SOUND *biip);
int moveDoors(SDL_Rect doors[16], _train *train, FMOD_SYSTEM *fmodSystem, FMOD_SOUND *biip);
void displayDoors(SDL_Renderer *renderer, SDL_Rect doors[16]);
int checkTrainsOut(_train *train1, _train *train2);


#endif
