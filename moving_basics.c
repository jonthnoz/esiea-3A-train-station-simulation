#include <stdlib.h>
#include <SDL2/SDL.h>
#include <SDL2/SDL_image.h>
#include <string.h>
#include "mode2.h"

void movePassenger(_human **head_ref, int schedule[4])
{
	_human *passenger = *head_ref;		// set a human address pointing to the head of the list
	int r = 3;							// will store the result of checkMoveAllowed function 

	while (passenger != NULL)			// for each element in the linked list
	{
		if (passenger->isControlled == SDL_FALSE)	// only if it is not manually controlled
		{
			switch (passenger->direction) 			// according to the direction wanted
			{
				case 'z': 
					passenger->position->y -= passenger->speed;				// set a new position
					r = checkMoveAllowed(passenger, schedule, head_ref);
					if (r == 1) {											// if it is forbidden
						passenger->position->y += passenger->speed;			// undo the move
						reinitDirection(passenger, schedule);				// reset the direction setup
					}
					break;
				case 'q': 
					passenger->position->x -= passenger->speed;
					r = checkMoveAllowed(passenger, schedule, head_ref);
					if (r == 1) {
						passenger->position->x += passenger->speed;
						reinitDirection(passenger, schedule);
					}
					break;
				case 's': 
					passenger->position->y += passenger->speed;
					r = checkMoveAllowed(passenger, schedule, head_ref);
					if (r == 1) {
						passenger->position->y -= passenger->speed;
						reinitDirection(passenger, schedule);
					}
					break;
				case 'd': 
					passenger->position->x += passenger->speed;
					r = checkMoveAllowed(passenger, schedule, head_ref);
					if (r == 1) {
						passenger->position->x -= passenger->speed;
						reinitDirection(passenger, schedule);
					}
					break;
				default: break;
			}
			if (r == 2) 									// if it is in a train or out of the station
				deletePassenger(passenger, head_ref);		// delete the passenger from the list
			if (r == 0) {									// if the mov is confirmed
				passenger->directionCounter -= 1;			// decrement the counter of steps before changing direction
			}
			if (passenger->directionCounter == 0)			// if the counter reach 0
				reinitDirection(passenger, schedule);		// new direction setup

			checkDestination(passenger, schedule, head_ref);	// check special action such as waiting if destination is reached
			r = 3;											// reset r value
		}
			passenger = passenger->next;				// change to the next passenger in the list
	}
}

// return 1 if move not allowed, 2 if in train or out of station, 0 if ok
int checkMoveAllowed(_human *passenger, int schedule[4], _human **head_ref)
{
	int x = passenger->position->x;		// save passenger coordinates in smaller variables
	int y = passenger->position->y;

	// out 
	if (y < -30 || y > SCREEN_HEIGHT + 10)	// outside the window
		return 2;							// should be deleted

	// middle (train, doors)
	if (y >= 158 && y <= 330) {				// do not approach the rails
		if (passenger->escalier == 0 && (schedule[0] > -300 || schedule[0] < -700)) 
				return 1;					// unless a train is here
		else {							
			if (y > 210)					// in the train
				return 2;					// should be deleted
			if (x <= 131+40  && x >= 131+10)		// at a door
				return 0;							// move is allowed
			else if (x <= 311+40 && x >= 311+10)
				return 0;
			else if (x <= 492+40 && x >= 492+10)
				return 0;
			else if (x <= 666+40 && x >= 666+10)
				return 0;
			else if (x >= SCREEN_WIDTH-666-60 && x <= SCREEN_WIDTH-666-30)
				return 0;
			else if (x >= SCREEN_WIDTH-492-60 && x <= SCREEN_WIDTH-492-30)
				return 0;
			else if (x >= SCREEN_WIDTH-311-60 && x <= SCREEN_WIDTH-311-30)
				return 0;
			else if (x >= SCREEN_WIDTH-131-60 && x <= SCREEN_WIDTH-131-30)
				return 0;
			else 							// not at a door
				return 1;					// move is not allowed
		}
	}
	if (y >= 330 && y <= 510) {				// same reasoning for the bottom side
		if (passenger->escalier == 1 && (schedule[2] > -300 || schedule[2] < -700)) 
				return 1;
		else {
			if (y < 478)
				return 2;
			if (x <= 131+40  && x >= 131+10)
				return 0;
			else if (x <= 311+40 && x >= 311+10)
				return 0;
			else if (x <= 492+40 && x >= 492+10)
				return 0;
			else if (x <= 666+40 && x >= 666+10)
				return 0;
			else if (x >= SCREEN_WIDTH-666-60 && x <= SCREEN_WIDTH-666-30)
				return 0;
			else if (x >= SCREEN_WIDTH-492-60 && x <= SCREEN_WIDTH-492-30)
				return 0;
			else if (x >= SCREEN_WIDTH-311-60 && x <= SCREEN_WIDTH-311-30)
				return 0;
			else if (x >= SCREEN_WIDTH-131-60 && x <= SCREEN_WIDTH-131-30)
				return 0;
			else
				return 1;
		}
	}

	// plants
	if (x <= 83 && y <= 101)			// move not allowed if at the position
		return 1;						// of the decoration of the station
	if (x >= 1497-20 && y <= 130)
		return 1;
	if (x <= 92 && y >= 591-20 )
		return 1;
	if (x >= 1488-20 && y >= 571-20)
		return 1;

	// walls
	if (x <= 8 || x >= SCREEN_WIDTH-8-20)		// neither in the walls
		return 1;
	if (x <= 470 || x >= SCREEN_WIDTH - 500) {
		if (y <= 8 || y >= SCREEN_HEIGHT-8-20)
			return 1; }

	if (y <= 77) {								
		if (x < 480 && x > 474-20)			// nor at the place where the scheduled are displayed
			return 1;
		if (x < 1124 && x > 1120-20)
			return 1; 
		if (x < 883 && x > 721-20)
			return 1; }
	if (y >= 615-20) {
		if (x < 480 && x > 474-20)
			return 1;
		if (x < 1124 && x > 1120-20)
			return 1; 
		if (x < 883 && x > 721-20)
			return 1; }

	// vending machines
	if (y <= 30) {
		if (x <= 191 && x >= 158-20) 
			return 1;
		if (x <= 1197 && x >= 1161-20) 
			return 1; }
	if (y >= SCREEN_HEIGHT-49) {
		if (x <= 1248 && x >= 1178-20) 
			return 1; }

	return 0;
}