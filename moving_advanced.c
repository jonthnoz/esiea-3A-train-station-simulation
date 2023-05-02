#include <stdio.h>
#include <stdlib.h>
#include <SDL2/SDL.h>
#include <SDL2/SDL_image.h>
#include <string.h>
#include "mode2.h"

int seatList[48];		// each index correspond to a seat in the station, to check if it is taken

// setup a destination area and a door targeted according to the mode and some probabilities
void setDestination(_human *passenger)
{
	int random = rand() % 99;				// random integer between 0 and 99
	SDL_Point door = {131+25,330};			// default values of the door
	SDL_Rect destination = {1,1,1,1};		// default values of the destination

	// a hurry passenger only focus on a door
    if (0 == strcmp(passenger->mode, "hurry")) 	
    {
		if (passenger->escalier == 0)		// the y coordinate depends on its side of the station
			door.y = 212;
		else
			door.y = 475;

		if (random < 25)					// the x coordinate is randomly selected between the 
			door.x = SCREEN_WIDTH-666-46;	// 4 doors in the middle 
		if (random > 24 && random < 50)
			door.x = SCREEN_WIDTH-492-45;
		if (random > 49 && random < 75)
			door.x = 492+25;
		if (random > 74)
			door.x = 666+25;
    }

    // a door and the cooresponding area on the platform are attributed to the normal passengers
    if (0 == strcmp(passenger->mode, "normal")) 
    {
		if (random < 13){
			destination.x = 0;
			door.x = 131+25;
		}
		if (random > 12 && random < 26){
			destination.x = 200;
			door.x = 311+25;
		}
		if (random > 25 && random < 38){
			destination.x = 400;
			door.x = 492+25;
		}
		if (random > 37 && random < 50){
			destination.x = 600;
			door.x = 666+25;
		}
		if (random > 49 && random < 62){
			destination.x = 800;
			door.x = SCREEN_WIDTH-46-666;
		}
		if (random > 61 && random < 74){
			destination.x = 1000;
			door.x = SCREEN_WIDTH-46-492;
		}
		if (random > 73 && random < 77){
			destination.x = 1200;
			door.x = SCREEN_WIDTH-46-311;
		}
		if (random > 76 && random < 99){
			destination.x = 1400;
			door.x = SCREEN_WIDTH-46-131;
		}
		
		if (passenger->escalier == 1){	// y coordinate depends on the side of the station
			destination.y = 488;
			door.y = 475;
		}
		else {
			destination.y = 40;
			door.y = 212;
		}

		destination.w = 200;			// with fixed dimensions for the destination
		destination.h = 150;			
    }
	

	// a thirsty passenger destination is the area in front of a vending machine
    if (0 == strcmp(passenger->mode, "thirsty")) 
    {
        if (passenger->escalier == 0){				// on the top platform
        	if (random < 50)
				destination.x = rand()%14 + 156;	// either the first machine
        	else
				destination.x = rand()%16 + 1160;	// or the second
			destination.y = rand()%2 + 31;
        }
        else {
        	if (random < 50)
				destination.x = rand()%12 + 1180;
        	else
				destination.x = rand()%15 + 1210;
			destination.y = SCREEN_HEIGHT-(rand()%3 + 50);        	
        }
        destination.w = 12;				// fixed dimensions
        destination.h = 2;
    }

    // a thirsty passenger destination is a seat
    if (0 == strcmp(passenger->mode, "tired")) 
	{
        int seat = random/4;				// transform the random range
        if (passenger->escalier == 0){		// check the side
        	while (seatList[seat] != 0){	// check that the seat is free
        		seat = rand() % 24;			// otherwise selected another one until its a free one
        	}
    		seatList[seat] = 1;				// mark it as taken
    		if (seat == 0)					// and assign the corresponging x coordinate
    			destination.x = 214;
    		if (seat == 1)
    			destination.x = 230;	
    		if (seat == 2)
    			destination.x = 246;	
    		if (seat == 3)
    			destination.x = 280;	
    		if (seat == 4)
    			destination.x = 296;	
    		if (seat == 5)
    			destination.x = 312;	
    		if (seat == 6)
    			destination.x = 352;	
    		if (seat == 7)
    			destination.x = 368;	
    		if (seat == 8)
    			destination.x = 384;	
    		if (seat == 9)
    			destination.x = 420;	
    		if (seat == 10)
    			destination.x = 436;	
    		if (seat == 11)
    			destination.x = 452;	
    		if (seat == 12)
    			destination.x = 1212;	
    		if (seat == 13)
    			destination.x = 1228;	
    		if (seat == 14)
    			destination.x = 1243;	
    		if (seat == 15)
    			destination.x = 1279;	
    		if (seat == 16)
    			destination.x = 1295;	
    		if (seat == 17)
    			destination.x = 1310;	
    		if (seat == 18)
    			destination.x = 1351;	
    		if (seat == 19)
    			destination.x = 1367;	
    		if (seat == 20)
    			destination.x = 1382;	
    		if (seat == 21)
    			destination.x = 1418;	
    		if (seat == 22)
    			destination.x = 1434;	
    		if (seat == 23)
    			destination.x = 1450;	
			destination.y = 10;					// and y coordinate
    	}
        else {
        	seat += 24;							// for the seats on the other side
        	while (seatList[seat] != 0){
        		seat = rand() % 24;
        		seat += 24;
        	}
    		seatList[seat] = 1;
    		if (seat == 24)
    			destination.x = 124;	
    		if (seat == 25)
    			destination.x = 139;	
    		if (seat == 26)
    			destination.x = 155;	
    		if (seat == 27)
    			destination.x = 190;	
    		if (seat == 28)
    			destination.x = 206;	
    		if (seat == 29)
    			destination.x = 222;	
    		if (seat == 30)
    			destination.x = 262;	
    		if (seat == 31)
    			destination.x = 278;	
    		if (seat == 32)
    			destination.x = 294;	
    		if (seat == 33)
    			destination.x = 329;	
    		if (seat == 34)
    			destination.x = 345;	
    		if (seat == 35)
    			destination.x = 361;	
    		if (seat == 36)
    			destination.x = 1263;	
    		if (seat == 37)
    			destination.x = 1279;	
    		if (seat == 38)
    			destination.x = 1295;	
    		if (seat == 39)
    			destination.x = 1330;	
    		if (seat == 40)
    			destination.x = 1346;	
    		if (seat == 41)
    			destination.x = 1362;	
    		if (seat == 42)
    			destination.x = 1401;	
    		if (seat == 43)
    			destination.x = 1417;	
    		if (seat == 44)
    			destination.x = 1433;	
    		if (seat == 45)
    			destination.x = 1468;	
    		if (seat == 46)
    			destination.x = 1484;	
    		if (seat == 47)
    			destination.x = 1500;	
			destination.y = SCREEN_HEIGHT - 31;
        }
        destination.w = 2;
        destination.h = 2;
	}

	// finally change the destination and door values of the passenger
	passenger->destination->x = destination.x;
	passenger->destination->y = destination.y;
	passenger->destination->w = destination.w;
	passenger->destination->h = destination.h;
	passenger->door->x = door.x;
	passenger->door->y = door.y;
}

void reinitDirection(_human *passenger, int schedule[4]) 
{
	// create a point with the coordinate of the passenger to be able to use the PointInRect function (SDL)
	SDL_Point position = {passenger->position->x, passenger->position->y};
	
	// make sure the passenger go out of the stairs
	if (passenger->position->y <= 97 && passenger->position->x >= 480 && passenger->position->x <= SCREEN_WIDTH-500)
	{
		passenger->direction = 's';
	}
	else if (passenger->position->y >= SCREEN_HEIGHT-100 && passenger->position->x >= 480 && passenger->position->x <= SCREEN_WIDTH-500)	
	{
		passenger->direction = 'z';
	}
	
	else 
    {	
    	// for thirsty and tired
		if (0 == strcmp(passenger->mode, "thirsty") || 0 == strcmp(passenger->mode, "tired")) 
		{
			// go to the door if a train is here
			if (passenger->escalier == 0 && schedule[0] < 0)
			{
				// do move horizontaly if in front of the door
				if (rand()%2 && abs(passenger->position->x - passenger->door->x) > 10)
				{
					// select the correct direction between left or right
					if (passenger->position->x < passenger->door->x)
					{
						passenger->direction = 'd';
						passenger->directionCounter = rand()% 130;	
						// and a number of steps not bigger than the distance to reach the door
						while (passenger->directionCounter > passenger->door->x + 10 - passenger->position->x)
						{
							passenger->directionCounter = rand()% 130;
						}
					}
					else
					{
						passenger->direction = 'q';
						passenger->directionCounter = rand()% 130;
						while (passenger->directionCounter > passenger->position->x - passenger->door->x - 10)
						{
							passenger->directionCounter = rand()% 130;
						}
					}		
				}
				else
				{	// or setup a vertical displacement 
					passenger->direction = 's';
					passenger->directionCounter = rand()% 130;
				}
			}
			// same case for the other side of the station
			else if (passenger->escalier == 1 && schedule[2] < 0)
			{
				if (rand()%2 && abs(passenger->position->x - passenger->door->x) > 10)
				{
					if (passenger->position->x < passenger->door->x)
					{
						passenger->direction = 'd';
						passenger->directionCounter = rand()% 130;
						while (passenger->directionCounter > passenger->door->x + 10 - passenger->position->x)
						{
							passenger->directionCounter = rand()% 130;
						}
					}
					else
					{
						passenger->direction = 'q';
						passenger->directionCounter = rand()% 130;
						while (passenger->directionCounter > passenger->position->x - passenger->door->x - 10)
						{
							passenger->directionCounter = rand()% 130;
						}
					}		
				}
				else
				{
					passenger->direction = 'z';
					passenger->directionCounter = rand()% 130;
				}
			} 
			// if the train is not here yet
			else if (SDL_TRUE == SDL_PointInRect(&position, passenger->destination))
			{	
				passenger->direction = 'e';		// do not move if in its destination area
			}
			else 		// if not, go in it
			{
				// don't move verticaly if in front of the stairs  
				if (rand()%2 || (passenger->position->x >= 480 && passenger->position->x < SCREEN_WIDTH-500))
				{
					if (passenger->position->x < passenger->destination->x)
					{
						passenger->direction = 'd';
						passenger->directionCounter = rand()% 199;
						// and don't go to far
						while (passenger->directionCounter > passenger->destination->x - passenger->position->x)
						{
							passenger->directionCounter = rand()% 150;
						}
					}
					else // and for the left
					{ 
						passenger->direction = 'q';
						passenger->directionCounter = rand()% 199;
						while (passenger->directionCounter > passenger->position->x - passenger->destination->x)
						{
							passenger->directionCounter = rand()% 150;
						}
					}
				}
				else // and vertically
				{
					if (passenger->position->y < passenger->destination->y)
					{
						passenger->direction = 's';
						passenger->directionCounter = rand()% 100;
						while (passenger->directionCounter > passenger->destination->y - passenger->position->y)
						{
							passenger->directionCounter = rand()% 100;
						}
					}
					else
					{ 
						passenger->direction = 'z';
						passenger->directionCounter = rand()% 100;
						while (passenger->directionCounter > passenger->position->y - passenger->destination->y)
						{
							passenger->directionCounter = rand()% 100;
						}
					}
				}
			}
		}
			
		// for the ones in a hurry
		if (0 == strcmp(passenger->mode, "hurry")) 
		{	
			if (passenger->escalier == 0) 		  // 1st side
			{	// don't move horizontaly if in front of the door, otherwise 1/2 chance
				if (rand()%2 && abs(passenger->position->x - passenger->door->x) > 10)
				{
					if (passenger->position->x < passenger->door->x)
					{
						passenger->direction = 'd';
						passenger->directionCounter = rand()% 130;
						while (passenger->directionCounter > (passenger->door->x + 10 - passenger->position->x)/2)
						{
							passenger->directionCounter = rand()% 130;
						}
					}
					else
					{
						passenger->direction = 'q';
						passenger->directionCounter = rand()% 130;
						while (passenger->directionCounter > (passenger->position->x - passenger->door->x - 10)/2)
						{
							passenger->directionCounter = rand()% 130;
						}
					}		
				}
				else
				{
					passenger->direction = 's';
					passenger->directionCounter = rand()% 130;
				}
			}
			else if (passenger->escalier == 1)		// otherside (same process)
			{
				if (rand()%2 && abs(passenger->position->x - passenger->door->x) > 10)
				{
					if (passenger->position->x < passenger->door->x)
					{
						passenger->direction = 'd';
						passenger->directionCounter = rand()% 130;
						while (passenger->directionCounter > passenger->door->x + 10 - passenger->position->x)
						{
							passenger->directionCounter = rand()% 130;
						}
					}
					else
					{
						passenger->direction = 'q';
						passenger->directionCounter = rand()% 130;
						while (passenger->directionCounter > passenger->position->x - passenger->door->x - 10)
						{
							passenger->directionCounter = rand()% 130;
						}
					}		
				}
				else
				{
					passenger->direction = 'z';
					passenger->directionCounter = rand()% 130;
				}
			} 
		}

		// normal passengers
		if (0 == strcmp(passenger->mode, "normal")) 
		{
			// focus on door when train is here
			if (passenger->escalier == 0 && schedule[0] < 0)
			{
				if (rand()%2 && abs(passenger->position->x - passenger->door->x) > 10)
				{
					if (passenger->position->x < passenger->door->x)
					{
						passenger->direction = 'd';
						passenger->directionCounter = rand()% 130;
						while (passenger->directionCounter > passenger->door->x + 10 - passenger->position->x)
						{
							passenger->directionCounter = rand()% 130;
						}
					}
					else
					{
						passenger->direction = 'q';
						passenger->directionCounter = rand()% 130;
						while (passenger->directionCounter > passenger->position->x - passenger->door->x - 10)
						{
							passenger->directionCounter = rand()% 130;
						}
					}		
				}
				else
				{
					passenger->direction = 's';
					passenger->directionCounter = rand()% 130;
				}
			}
			else if (passenger->escalier == 1 && schedule[2] < 0)
			{
				if (rand()%2 && abs(passenger->position->x - passenger->door->x) > 10)
				{
					if (passenger->position->x < passenger->door->x)
					{
						passenger->direction = 'd';
						passenger->directionCounter = rand()% 130;
						while (passenger->directionCounter > passenger->door->x + 10 - passenger->position->x)
						{
							passenger->directionCounter = rand()% 130;
						}
					}
					else
					{
						passenger->direction = 'q';
						passenger->directionCounter = rand()% 130;
						while (passenger->directionCounter > passenger->position->x - passenger->door->x - 10)
						{
							passenger->directionCounter = rand()% 130;
						}
					}		
				}
				else
				{
					passenger->direction = 'z';
					passenger->directionCounter = rand()% 130;
				}
			} 
			// on the destination area otherwise
			else if (SDL_TRUE == SDL_PointInRect(&position, passenger->destination))
			{
				passenger->direction = 'e';		// do not move if inside its destination 
			}
			else 
			{
				if (rand()%3 > 0)
				{
					if (passenger->position->x < passenger->destination->x)
					{	// to the right
						passenger->direction = 'd';
						passenger->directionCounter = rand()% 199;
						// don't go too far
						while (passenger->directionCounter > passenger->destination->x + 180 - passenger->position->x)
						{
							passenger->directionCounter = rand()% 199;
						}
					}
					else
					{	// to the left
						passenger->direction = 'q';
						passenger->directionCounter = rand()% 199;
						// don't go too far
						while (passenger->directionCounter > passenger->position->x - passenger->destination->x)
						{
							passenger->directionCounter = rand()% 199;
						}
					}
				}
				else 
				{ 	// freely and randomyl move verticaly
					if (rand()%2)
						passenger->direction = 'z';
					else 
						passenger->direction = 's';
					passenger->directionCounter = rand()%80;
				}
			}
		}
	}
}


void checkDestination(_human *passenger, int schedule[4], _human **head_ref)
{
	char *normal = "normal";
	SDL_Point position = {passenger->position->x, passenger->position->y};

	// delete the passenger locked on the rails (not fully reached the train) because of bad timing at train departure
	if ((passenger->escalier == 0 && schedule[0] < -700 && schedule[0] > -850) || (passenger->escalier == 1 && schedule[2] < -700 && schedule[2] > -850))
    {
    	if (passenger->position->y >= 192 && passenger->position->y <= 488)
			deletePassenger(passenger, head_ref);
    }

	// mode = normal
	if (0 == strcmp(passenger->mode, "normal")) 
	{	// when a train is here
		if ((passenger->escalier == 0 && schedule[0] < 0) || (passenger->escalier == 1 && schedule[2] < 0))
		{	// if the passenger was not moving
			if (passenger->stayCounter == -1)
			{
				reinitDirection(passenger, schedule);	// setup new direction
				passenger->stayCounter = 0;				// enable moving
			}
		}
		else 
			passenger->stayCounter = -1;	// mark not moving (so we don't reset direction each time we train is here)
    }

    // mode = hurry
	if (0 == strcmp(passenger->mode, "hurry")) 
	{	
		// if the train is leaving
		if ((passenger->escalier == 0 && schedule[0] < -700 && schedule[0] > -810) || (passenger->escalier == 1 && schedule[2] < -700 && schedule[2] > -810))
		{
			passenger->emoji = 5;	// change aooearance (sweating)
		}
		// and then become a normal passenger
		else if ((passenger->escalier == 0 && schedule[0] < -810) || (passenger->escalier == 1 && schedule[2] < -810))
		{
			free(passenger->mode); 					// erase previously assigned mode
			passenger->mode = malloc(strlen(normal) + 1);	// allocate memory for mode 
			strcpy(passenger->mode, normal);		// mode <- "normal
			setDestination(passenger);				// set new destination and door
			passenger->speed = 1;					// normal speed
			passenger->emoji = 0;					// normal look
			reinitDirection(passenger, schedule);	// new direction setup
		}
	}

	// mode = thirsty
	if (0 == strcmp(passenger->mode, "thirsty")) 
	{	// if destination is reached 
		if (SDL_PointInRect(&position, passenger->destination) == SDL_TRUE)
		{	// at the arrival
			if (passenger->stayCounter < 0)
			{
				passenger->stayCounter = 60;	// set the time to stay
				passenger->direction = 'e';		// no further move
			}
			else 
			{	// if already in before
				if (passenger->stayCounter == 0)	// after the waiting time
				{	
					if (rand() % 2)						// 1/2 chances	
						passenger->emoji += 1;			// to get happier look
					free(passenger->mode); 				// erase previously assigned mode
					passenger->mode = malloc(strlen(normal) + 1);	// allocate memory for mode 
					strcpy(passenger->mode, normal);	// mode <- "normal
    				setDestination(passenger);			// set a new destination
					reinitDirection(passenger, schedule);	// reset direction of next move
				}
				passenger->stayCounter -= 1;		// decrement the time to stay
			}
		}
	}

	// mode = tired
	if (0 == strcmp(passenger->mode, "tired")) 
	{	// if train not here
		if ((passenger->escalier == 0 && schedule[0] > 0) || (passenger->escalier == 1 && schedule[2] > 0))
		{	// and seat reached
			if (SDL_PointInRect(&position, passenger->destination) == SDL_TRUE)
			{	// right at this moment
				if (passenger->stayCounter < 0)
				{
					if (rand() % 5 < 3)					// 3/5 chances	
					{									// to get happier look
						if (passenger->emoji == 0)
							passenger->emoji = 1;	
						else if (passenger->emoji == 4)
							passenger->emoji = 0;		
					}
					passenger->stayCounter = 0;		// mark destination reached
					passenger->direction = 'e';		// no further move
				}
			}
		}
		// if train is here
		else if ((passenger->escalier == 0 && schedule[0] < 0) || (passenger->escalier == 1 && schedule[2] < 0))
		{	// if passenger seating
			if (passenger->stayCounter >= 0)
			{
				passenger->stayCounter = -1;		// don't seat anymore
				free(passenger->mode); 				// erase previously assigned mode
				passenger->mode = malloc(strlen(normal) + 1);	// allocate memory for mode 
				strcpy(passenger->mode, normal);	// mode <- "normal
				setDestination(passenger);			// set a new destination
				reinitDirection(passenger, schedule);	// reset direction of next move
			}
		}
	}
}
