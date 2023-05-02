#include <stdlib.h>
#include <SDL2/SDL.h>
#include <SDL2/SDL_image.h>
#include <string.h>
#include "mode2.h"


void selectPassenger(_human *passenger, SDL_Point click)
{
	int count = 0;		// save the place in the linked list of the passenger to control
	int check = 0;		// state to know if the click was on a passenger
	_human *p = passenger;	// save a reference to the first element of the linked list 
	char* normal = "normal";

	while (passenger != NULL)	// for each passenger
	{
		if (SDL_PointInRect(&click, passenger->position) == SDL_TRUE) {	// if the click is on it
			passenger->isControlled = SDL_TRUE;			// swap isControlled value
			if (0 != strcmp(passenger->mode, "normal")) {
				free(passenger->mode); 				// erase previously assigned mode
		    	passenger->mode = malloc(strlen(normal) + 1);	// allocate memory for mode 
		    	strcpy(passenger->mode, normal);	// mode <- "normal"
		    	setDestination(passenger);			// set a new destination
		    }
			check = 1;						// save the state
			break;							// exit the while loop
		}
		count++;								// increment the counter
		passenger = passenger->next;			// move to the next passenger in the list
	}
	if (check) {								// if a passenger has been clicked
		while (p != NULL)						// for each passenger
		{
			if (count != 0) 					// except the clicked one
				p->isControlled = SDL_FALSE;	// make sur it is no more controlled
			count--;
			p = p->next;
		}
	}
}


void controlePassenger(char direction, _human *passenger, int schedule[4], _human **head_ref)
{
	int r = 0;
	// find the passenger in the list that is controlled
	while (passenger != NULL)			 
	{
		if (passenger->isControlled == SDL_TRUE) 
			break;
		passenger = passenger->next;
	}
	if (passenger != NULL) {
		switch (direction) 		// according to the direction wanted
		{
			case 'z': 
				passenger->position->y -= 5;							// set a new position
				r = checkMoveAllowed(passenger, schedule, head_ref);
				if (r == 1)										// if it is forbidden
					passenger->position->y += 5;				// undo the move
				if (r == 2)										// if it is in a train or out of the station
					deletePassenger(passenger, head_ref);		// delete the passenger from the list
				break;
			case 'q': 								// same for all possible direction
				passenger->position->x -= 5;
				r = checkMoveAllowed(passenger, schedule, head_ref);
				if (r == 1)
					passenger->position->x += 5;
				if (r == 2)
					deletePassenger(passenger, head_ref);
				break;
			case 's': 
				passenger->position->y += 5;
				r = checkMoveAllowed(passenger, schedule, head_ref);
				if (r == 1)
					passenger->position->y -= 5;
				if (r == 2)
					deletePassenger(passenger, head_ref);
				break;
			case 'd': 
				passenger->position->x += 5;
				r = checkMoveAllowed(passenger, schedule, head_ref);
				if (r == 1)
					passenger->position->x -= 5;
				if (r == 2)
					deletePassenger(passenger, head_ref);
				break;
		}
	}
}