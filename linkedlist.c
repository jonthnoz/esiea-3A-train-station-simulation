#include <stdio.h>
#include <stdlib.h>
#include <SDL2/SDL.h>
#include <SDL2/SDL_image.h>
#include <string.h>
#include "mode2.h"


void deletePassenger(_human *passenger, _human **head_ref)
{
	_human *prev = *head_ref;			// save the address of 1st element

	if (*head_ref == passenger) {		// if we should delete 1st element
		*head_ref = passenger->next; 	// 2nd become the head reference
	}

	else {
		while(prev->next != passenger){	// reach the element before the one to delete
			prev = prev->next;
		}
		prev->next = passenger->next;	// link it to the one after
	}
	free(passenger->position);		//
	free(passenger);				// free the memory allocated for the passenger deleted
	passenger = NULL;				//
}

// renderCopy all the passengers from a linked list using the textures in the array smiley
void displayPassengers(_human *passenger, SDL_Texture *smiley[6], SDL_Renderer *renderer)
{
	while(passenger != NULL) 	
	{
        SDL_RenderCopy(renderer, smiley[passenger->emoji], NULL, passenger->position);   
        passenger = passenger->next;
	}
}