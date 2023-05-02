#include <stdlib.h>
#include <SDL2/SDL.h>
#include <SDL2/SDL_image.h>
#include <string.h>
#include "mode2.h"

void addPassenger(_human **head_ref, int schedule[4])
{
	int random = rand() % 80; 		// define the frequency of creation of new passengers 
	if (!random) {					// if random == 0 (1/80 chances)
		_human *new_passenger = malloc(sizeof(_human)); 		// allocation of the memory for the new variable human
	    new_passenger->position = malloc(sizeof(SDL_Rect));		// allocation of the memory for its variable position  
	    new_passenger->destination = malloc(sizeof(SDL_Rect));	// allocation of the memory for its variable destination  
	    new_passenger->door = malloc(sizeof(SDL_Point));		// allocation of the memory for its variable door
	    // check that the allocation worked fine  
	    if (new_passenger == NULL || new_passenger->destination == NULL || new_passenger->door == NULL || new_passenger->position == NULL ) {
	        fprintf(stderr, "Allocation error! file:%s line:%d\n", __FILE__, __LINE__);
	        return;
	    }

	    // escalier
	    new_passenger->escalier = rand() % 2;		// randomly assign a side of the station
	    
	    // position
	    new_passenger->position->w = 20;			// set the dimensions of the passenger
	    new_passenger->position->h = 20;

	    if (new_passenger->escalier == 0)			// according to its side,
	    	new_passenger->position->y = -20;		// set the y coordinate of the passenger
	    else 
	    	new_passenger->position->y = SCREEN_HEIGHT;

	    new_passenger->position->x = 0;				// set the x coordinate to be on the stairs of the station			
	    while (new_passenger->position->x < 480 || new_passenger->position->x > SCREEN_WIDTH - 500 || (new_passenger->position->x > 700 && new_passenger->position->x < SCREEN_WIDTH - 715))
	    {
	    	new_passenger->position->x = (rand() % 620) + 480;
	    }
	    
	    // isControlled
	    new_passenger->isControlled = SDL_FALSE;

	    // mode
	    char *hurry = "hurry";
	    char *tired = "tired";
	    char *thirsty = "thirsty";
	    char *normal = "normal";

	    random = rand() % 15;				// randomly assign a mode  
	    if (random == 0) {
	    	new_passenger->mode = malloc(strlen(thirsty) + 1);
	    	strcpy(new_passenger->mode, thirsty);	// mode = "thirsty"
	    }
	    else if (random > 0 && random <= 2) {
	    	new_passenger->mode = malloc(strlen(tired) + 1);
	    	strcpy(new_passenger->mode, tired);		// mode = "tired"
	    }
	    else {
	    	new_passenger->mode = malloc(strlen(normal) + 1);
	    	strcpy(new_passenger->mode, normal);		// mode = "normal"
	    }

	    if (rand()%2)		/* be hurry if train coming soon */
	    {
		    if (new_passenger->escalier == 0) {	// top side of the station
		    	if (schedule[0] < -200 && schedule[0] > -780) {		// train coming soon
		    		if (rand() % 3) {			// 2/3 chances
		    			free(new_passenger->mode); 			// erase previously assigned mode
		    			new_passenger->mode = malloc(strlen(hurry) + 1);
		    			strcpy(new_passenger->mode, hurry);	// mode = "hurry"
		    		}
		    	}
		    }
		    else {								// other side of the station
		    	if (schedule[2] < -200 && schedule[2] > -780) {		// train coming soon
		    		if (rand() % 3) {			// 2/3 chances
		    			free(new_passenger->mode); 			// erase previously assigned mode
		    			new_passenger->mode = malloc(strlen(hurry) + 1);
		    			strcpy(new_passenger->mode, hurry);	// mode = "hurry"
		    		}
		    	}
		    }
		}

	    // speed		
	    if (0 == strcmp(new_passenger->mode, "hurry"))
	    	new_passenger->speed = 2;			// double the speed if mode = hurry
	    else 
	    	new_passenger->speed = 1;

	    // emoji		// assign appearance according to the mode and some probability
	    if (0 == strcmp(new_passenger->mode, "thirsty")) {
	    	random = rand() % 4;
	    	if (!random) 
	    		new_passenger->emoji = 1;	// little smile
	    	else 
	    		new_passenger->emoji = 0;	// normal
	    }
	    else if (0 == strcmp(new_passenger->mode, "tired")) {
	    	random = rand() % 3;
	    	if (!random) 
	    		new_passenger->emoji = 3;	// papi
	    	else 
	    		new_passenger->emoji = 0;	// normal
	    	if (!(rand() % 6))
	    		new_passenger->emoji = 4;	// sad
	    }
	    else if (0 == strcmp(new_passenger->mode, "hurry")) {
	    	new_passenger->emoji = 0;		// normal
	    }
	    else if (0 == strcmp(new_passenger->mode, "normal")) {
	    	random = rand() % 20;
	    	if (random < 2)
	    		new_passenger->emoji = 3;			// papi 2/20 chances
	    	else if (random >= 2 && random < 5)
	    		new_passenger->emoji = 2;			// smile 3/20 chances
	    	else if (random >= 5 && random < 8)
	    		new_passenger->emoji = 4;			// sad 3/20 chances 
	    	else if (random >= 8 && random < 12)
	    		new_passenger->emoji = 1;			// little smile 4/20 chances
	    	else if (random >= 12)
	    		new_passenger->emoji = 0;			// normal 8/20 chances
	    }

	    // destination
	   	setDestination(new_passenger);

	   	// direction 
	   	new_passenger->directionCounter = 77 + (rand() % 92);	// for at least 77 steps
	   	if (new_passenger->escalier == 0) 				// if top side
	    	new_passenger->direction = 's';					// go down initially
		else 											// if bottom side
	    	new_passenger->direction = 'z';					// go up initially

	    // counter
	    new_passenger->stayCounter = -1;		// allowed to move
	   
	   	// reference to the next
	    new_passenger->next = (*head_ref); 

	    // update the head of the list reference
	    *head_ref = new_passenger;
	} 
}