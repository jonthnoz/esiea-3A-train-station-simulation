#include <stdio.h>
#include <stdlib.h>
#include <SDL2/SDL.h>
#include <SDL2/SDL_image.h>
#include "mode1.h"



// compute a random delay before the next train arrival
int initSchedule()
{
    // decimal part 
    int randint = rand() % 99;
    float decimal = randint / 100.0;

    // integer part
    int random = (rand() % 99);
    // probabilities managment
    if (random > 1 && random <= 14)
    {
        return (3 + decimal) * 400;    
    }
    if (random > 14 && random <= 34)
    {
        return (4 + decimal) * 400;
    }
    if (random > 34 && random <= 54)
    {
        return (5 + decimal) * 400;
    }
    if (random > 54 && random <= 74)
    {
        return (6 + decimal) * 400;
    }
    if (random > 74 && random <= 80)
    {
        return (7 + decimal) * 400;
    }
    if (random > 80 && random <= 86)
    {
        return (8 + decimal) * 400;
    }
    if (random > 86 && random <= 92)
    {
        return (9 + decimal) * 400;
    }
    if (random > 92 && random <= 98)
    {
        return (10 + decimal) * 400;
    }
    if (random == 99 || random <= 1)
    {
        return (19 + decimal) * 400;
    }

    return 0;
}

// update the schedules when a train has come
void updateSchedule(int schedule[4], FMOD_SYSTEM *fmodSystem, FMOD_SOUND *delayed)
{
    if (schedule[0] <= -680)		// if top train has left the station
    {
            schedule[0] = schedule[1];  	// move to the next schedule
            schedule[1] += initSchedule();	// and compute a new one
    }
    if (schedule[2] <= -680) 		// same for the other side
    {
            schedule[2] = schedule[3];
            schedule[3] += initSchedule();
    }
    // annouce delay if 3% chance 19min schedule happened
    if (schedule[1] >= 7600 + schedule[0] || schedule[3] >= 7600 + schedule[2])
       FMOD_System_PlaySound(fmodSystem, delayed, NULL, 0, NULL);
}

// substract 1 to each schedule
void decrementSchedules(int schedule[4], _train *train1, _train *train2)
{
    for (int i = 0; i < 4; i++)
    {
        schedule[i]--;
        if (schedule[0] == 0)
        {
            train1->moving = 1;
        }
        if (schedule[2] == 0)
        {
            train2->moving = 1;
        }
    }
}

void displaySchedules(SDL_Renderer *renderer, SDL_Texture *texture[21], int schedule[4])
{
    SDL_Rect dimension = {0, 0, 44, 44} ;   // where to display the number (as a texture) on the window
    int n;                                  // texture identifier

    for (int i = 0; i < 4; i++)     // for each schedule
    {
        n = 20;

        // set up n
        for(int j = 0; j < 21; j++)
        {
            if ((schedule[i]/400)+1 >= j && (schedule[i]/400)+1 < j+1)   
                n = j;
            if (schedule[i] < 0)
                n = 0;
        }  

        // set up dimension
        if (i < 2)
            dimension.y = 28;
        else
            dimension.y = SCREEN_HEIGHT - 70;

        if (i%2 == 0)
            dimension.x = SCREEN_WIDTH/2 - 46;
        else
            dimension.x = SCREEN_WIDTH/2 + 8;

        // set up display
        SDL_RenderCopy(renderer, texture[n], NULL, &dimension);
    }
}