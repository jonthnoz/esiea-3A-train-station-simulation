#include <stdio.h>
#include <stdlib.h>
#include <SDL2/SDL.h>
#include <SDL2/SDL_image.h>
#include "mode1.h"


// create and initialize the trains with default values for the beginning of the program
int createTrains(_train **train1, _train **train2, SDL_Renderer *renderer)
{ 
    _train *t1 = NULL;
    _train *t2 = NULL;

    t1 = malloc(sizeof(_train));
    t2 = malloc(sizeof(_train));
    if (t2 == NULL || t1 == NULL)
    {
        fprintf(stderr, "Struct allocation error! file:%s line:%d\n", __FILE__, __LINE__);
        return -1;
    }
    t1->train_texture = loadImage("images/train_up.png", renderer); // train at the top
    if (t1->train_texture == NULL)
        return -1;

    t2->train_texture = loadImage("images/train_down.png", renderer); // train at the bottom
    if (t2->train_texture == NULL)
        return -1;

    t1->trainPosition = malloc(sizeof(SDL_Rect));
    t2->trainPosition = malloc(sizeof(SDL_Rect));
    if (t2->trainPosition == NULL || t1->trainPosition == NULL)
    {
        fprintf(stderr, "Rect allocation error! file:%s line:%d\n", __FILE__, __LINE__);
        return -1;
    }

    t1->trainPosition->x = SCREEN_WIDTH;
    t1->trainPosition->y = 204;
    t1->trainPosition->w = 1576;
    t1->trainPosition->h = 96;

    t2->trainPosition->x = -SCREEN_WIDTH;
    t2->trainPosition->y = SCREEN_HEIGHT-202-96;
    t2->trainPosition->w = 1576;
    t2->trainPosition->h = 96;

    t1->id = 1;
    t2->id = 2;
    t1->chrono = 0;
    t2->chrono = 0;
    t1->moving = 0;
    t2->moving = 0;

    *train1 = t1;
    *train2 = t2;

    return 0;
}

// trains managment main function
int moveTrain(_train *train, SDL_Rect doors[16], SDL_Renderer *renderer, FMOD_SYSTEM *fmodSystem, FMOD_SOUND *biip)
{
    if (train->moving)     // check the state of the train
    {
        int center = train->trainPosition->x + train->trainPosition->w / 2;     // compute its middle

        if (train->id == 1)    // select top or bottom train
        { 
            // speed controler to make acceleration and deceleration
            if (center > SCREEN_WIDTH/2 + 660 || center <= SCREEN_WIDTH/2 - 830)
            {
                train->trainPosition->x -= 10;
            }
            if (center <= SCREEN_WIDTH/2 + 660 && center > SCREEN_WIDTH/2 + 440 || center  > SCREEN_WIDTH/2 - 830 && center <= SCREEN_WIDTH/2 - 460)
            {
                train->trainPosition->x -= 8;
            }
            if (center <= SCREEN_WIDTH/2 + 440 && center > SCREEN_WIDTH/2 + 275 || center  > SCREEN_WIDTH/2 - 460 && center <= SCREEN_WIDTH/2 - 260)
            {
                train->trainPosition->x -= 6;
            }
            if (center <= SCREEN_WIDTH/2 + 275 && center > SCREEN_WIDTH/2 + 95 || center  > SCREEN_WIDTH/2 - 260 && center <= SCREEN_WIDTH/2 - 90)
            {
                train->trainPosition->x -= 4;
            }
            if (center <= SCREEN_WIDTH/2 + 95 && center > SCREEN_WIDTH/2 || center  > SCREEN_WIDTH/2 - 90 && center </*=*/ SCREEN_WIDTH/2)
            {
                train->trainPosition->x -= 2;
            }
            if (center == SCREEN_WIDTH/2)   // when it arrives at the stop position
            {
                train->trainPosition->x -= moveDoors(doors, train, fmodSystem, biip);    // call the doors controler function (returns 1 to restart the train, 0 until this)
                SDL_RenderCopy(renderer, train->train_texture, NULL, train->trainPosition);    // prepare the train picture to be displayed under the doors
                displayDoors(renderer, doors);                      // prepare the doors to be displayed at their new positions 
                return 0;               // signal that the train was stopped (to know if we have to RenderCopy)
            }
        }

        // same but for the second train 
        if (train->id == 2)
        {
            if (center > SCREEN_WIDTH/2 + 660 || center <= SCREEN_WIDTH/2 - 830)
            {
                train->trainPosition->x += 10;
            }
            if (center <= SCREEN_WIDTH/2 + 660 && center > SCREEN_WIDTH/2 + 440 || center  > SCREEN_WIDTH/2 - 830 && center <= SCREEN_WIDTH/2 - 460)
            {
                train->trainPosition->x += 8;
            }
            if (center <= SCREEN_WIDTH/2 + 440 && center > SCREEN_WIDTH/2 + 275 || center  > SCREEN_WIDTH/2 - 460 && center <= SCREEN_WIDTH/2 - 260)
            {
                train->trainPosition->x += 6;
            }
            if (center <= SCREEN_WIDTH/2 + 275 && center > SCREEN_WIDTH/2 + 95 || center  > SCREEN_WIDTH/2 - 260 && center <= SCREEN_WIDTH/2 - 90)
            {
                train->trainPosition->x += 4;
            }
            if (center <= SCREEN_WIDTH/2 + 95 && center > SCREEN_WIDTH/2 || center  > SCREEN_WIDTH/2 - 90 && center </*=*/ SCREEN_WIDTH/2)
            {
                train->trainPosition->x += 2;
            }
            if (center == SCREEN_WIDTH/2)
            {
                train->trainPosition->x += moveDoors(doors, train, fmodSystem, biip);
                SDL_RenderCopy(renderer, train->train_texture, NULL, train->trainPosition);
                displayDoors(renderer, doors);
                return 0;
            }
        }
    }
    return 1;       // signal that the train was moving
}


void displayDoors(SDL_Renderer *renderer, SDL_Rect doors[16])
{
    for(int i = 0; i < 16; i++) // for each door of a train
    {
        SDL_SetRenderDrawColor(renderer, 121, 245, 171, 255);   // set the green color of the inside
        SDL_RenderFillRect(renderer, &doors[i]);                // draw the full rectangle
        SDL_SetRenderDrawColor(renderer, 219, 219, 219, 255);   // set the grey color of the border
        SDL_RenderDrawRect(renderer, &doors[i]);                // draw the border
    }
}


int moveDoors(SDL_Rect doors[16], _train *train, FMOD_SYSTEM *fmodSystem, FMOD_SOUND *biip)
{
    int movingTime = 50;    // time of the opening or closing animation
    int openTime = 300;     // time to stay open
    int closeTime = 20;     // time to wait close
    
    train->chrono += 1;       // increment chronometer

    if (train->chrono == 5)
       FMOD_System_PlaySound(fmodSystem, biip, NULL, 0, NULL);

    //1st part of the animation, open in direction of the plateform (verticaly first)
    if (train->chrono < closeTime)   
    {
        if (train->chrono % 5 == 4)   // speed controller to change doors position during this part
        {        
            // train at the top
            if (doors[0].y == 204 || doors[0].y == 203 || doors[0].y == 202)
            {
                for(int i = 0; i < 16; i++) 
                {
                    doors[i].y -= 1;   
                }
            }

            // train at the bottom
            if (doors[0].y == SCREEN_HEIGHT-210 || doors[0].y == SCREEN_HEIGHT-209 || doors[0].y == SCREEN_HEIGHT-208)
            {
                for(int i = 0; i < 16; i++)
                {
                    doors[i].y += 1;
                }
            }
        }
    }
    
    else if (train->chrono % 2 == 0)  // speed controller to change doors position during these parts
    {        
        if (train->chrono < closeTime + movingTime)   // 2nd part of the animation, really open (horizontaly)
        {    
            if (doors[0].y == 201 || doors[0].y == SCREEN_HEIGHT-207)   // any train
            {
                if (doors[0].x <= 131 && doors[0].x > 131-25)   // if not completely open
                {
                    for(int i = 0; i < 16; i+=2)    // left doors
                    {
                        doors[i].x -= 1 ;
                    }
                    for(int i = 1; i < 16; i+=2)    // right doors
                    {
                        doors[i].x += 1 ;
                    }
                }
            }
        }

        if (train->chrono > closeTime+movingTime+openTime)    // 3rd part (closing horizontaly) after having keep open
        {   
            if (doors[0].x == 131)      // when closed
            {
                // top train
                if (doors[0].y == 201 || doors[0].y == 203 || doors[0].y == 202)
                {
                    for(int i = 0; i < 16; i++)
                    {
                        doors[i].y += 1 ;   // hide in direction of the train (verticaly)
                    }
                }
                // bottom train
                if (doors[0].y == SCREEN_HEIGHT-207 || doors[0].y == SCREEN_HEIGHT-209 || doors[0].y == SCREEN_HEIGHT-208)
                {
                    for(int i = 0; i < 16; i++)
                    {
                        doors[i].y -= 1 ;
                    }
                }
            }  

            if (doors[0].y == 201 || doors[0].y == SCREEN_HEIGHT-207)   // if not closed yet
            {
                if (doors[0].x < 131 && doors[0].x >= 131-25)
                {
                    for(int i = 0; i < 16; i+=2)
                    {
                        doors[i].x += 1 ;       // left doors
                    }
                    for(int i = 1; i < 16; i+=2)
                    {
                        doors[i].x -= 1 ;       // right doors
                    }
                }
            }
        } 
        
        // at the very end of the animation    
        if (train->chrono > 2*movingTime+openTime+2*closeTime)
        {
            train->chrono = 0;    // reset the given chronometer
            return 1;       // signal to restart the train
        }
    }

    return 0;       // return value to keep animating the doors
}

int checkTrainsOut(_train *train1, _train *train2)
{
            // when top train reach the end of the window 
            if (train1->trainPosition->x < -SCREEN_WIDTH)
            {
                train1->trainPosition->x = SCREEN_WIDTH;  // reset train position at the beginning 
                train1->moving = 0;                      // disable
                return 1;               // compute the next train schedule
            }
            // same for the bottom train
            if (train2->trainPosition->x > SCREEN_WIDTH)
            {
                train2->trainPosition->x = -SCREEN_WIDTH;
                train2->moving = 0;
                return 1;
            }
            return 0;
}