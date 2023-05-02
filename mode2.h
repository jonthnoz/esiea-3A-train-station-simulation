#ifndef MODE2_H
#define MODE2_H

#include "mode1.h"

/* Stucture */

typedef struct _human {			// structure of a passenger
	int emoji;					// to know which appearance to display
	int escalier;				// 0 = top, 1 = bottom of the map
	int speed;					// number of px for moving
	int stayCounter;			// time to wait at a state (several use)
	int directionCounter;		// n° of steps before recomputing direction
	char direction;				// direction of the next step 'z', 'q', 's' or 'd'
	char* mode;					// behaviour characteristic
	SDL_Rect *position;			// position in the window
	SDL_Rect *destination;		// coordinates of where the passenger is going in the station
	SDL_Point *door;			// coordinates of where the passenger is going inside the train
	SDL_bool isControlled;		// to identify the passenger that the user can control
	struct _human *next;		// address of the next passenger in the link list
} _human;


/* Prototypes */

// controlled_passenger.c
void selectPassenger(_human *passenger, SDL_Point click);
void controlePassenger(char direction, _human *passenger, int schedule[4], _human **head_ref);

// passenger_creation.c
void addPassenger(_human **head_ref, int schedule[4]);

// moving_basics.c
void movePassenger(_human **head_ref, int schedule[4]);
int checkMoveAllowed(_human *passenger, int schedule[4], _human **head_ref);

// linkedlist.c
void displayPassengers(_human *passenger, SDL_Texture *smiley[6] ,SDL_Renderer *renderer);
void deletePassenger(_human *passenger, _human **head_ref);

// moving_advanced.c
void setDestination(_human *passenger);
void reinitDirection(_human *passenger, int schedule[4]);
void checkDestination(_human *passenger, int schedule[4], _human **head_ref);







#endif