#include <stdio.h>
#include <stdlib.h>
#include <SDL2/SDL.h>
#include <SDL2/SDL_image.h>
#include "mode1.h"
#include "mode2.h"

int main(int argc, char *argv[]) {

// INITIALISATION

    /* declaration of variables */

    srand(time(NULL));                          // to have a different game each time
    int statut = EXIT_FAILURE;                  // exit status
    SDL_Window *window = NULL;
    SDL_Renderer *renderer = NULL;

    SDL_Texture *menuBackground_texture = NULL; // background of menu screen
    SDL_Rect choixMenu[3];                      // location of the buttons for the choice of the mode 
    SDL_Texture *stationTexture = NULL;         // station background
    SDL_Texture *entrance = NULL;               // home background
    SDL_Texture *goinside_texture = NULL;       // home button texture
    SDL_Rect goinside_rect = {630, 444, 250, 89};    // home button position
    SDL_Texture *numbers_texture[21] = {NULL};  // images of numbers to display the schedules  
    SDL_Rect doorsRect[2][16];                  // doors positions
    int schedule[4] = {400,1661,930,3022};      // delays before next train to come              
    _train *train1 = NULL;                  // train variables (structure) on the top
    _train *train2 = NULL;                  // on the bottom

    _human *liste_p = NULL;             // linked list of passengers
    SDL_Texture *smiley[6] = {NULL};    // passenger appearances

    SDL_Event event;                    // catch all the event of the window
    SDL_Point mousePosition;            // point used to save the mouse coordinate
    SDL_bool menu = SDL_FALSE;          // game controler (exit the home loop)
    SDL_bool start = SDL_FALSE;         // game controler (exit the menu loop)
    SDL_bool quit = SDL_FALSE;          // game controler (exit the principal loop)
    int newTime, oldTime = 0;           // to track the time in the program
    int mode = 0;                       // mode chosen
   
    FMOD_SYSTEM *fmodSystem = NULL;     // sound system from fmod librairy
    FMOD_SOUND *biip = NULL;            // doors sound
    FMOD_SOUND *delayed = NULL;         // delay announce


    /* loading variables */ 

    // window
    if (0 != init(&window, &renderer, SCREEN_WIDTH, SCREEN_HEIGHT))
        goto Quit;
    
    SDL_RaiseWindow(window);    // put our window on the foreground

    // trains
    if (0 != createTrains(&train1, &train2, renderer))
        goto Quit;

    // sound 
    FMOD_System_Create(&fmodSystem);
    FMOD_System_Init(fmodSystem, 10, FMOD_INIT_NORMAL, NULL);
    if (FMOD_OK != FMOD_System_CreateSound(fmodSystem, "sounds/bip_doors.mp3", FMOD_CREATESAMPLE, 0, &biip)) {
        fprintf(stderr, "Error FMOD_System_CreateSound. file:%s line:%d\n", __FILE__, __LINE__);
        goto Quit;
    }
    if (FMOD_OK != FMOD_System_CreateSound(fmodSystem, "sounds/delay_announce.mp3", FMOD_CREATESAMPLE, 0, &delayed)) {
        fprintf(stderr, "Error FMOD_System_CreateSound. file:%s line:%d\n", __FILE__, __LINE__);
        goto Quit;
    }

    // menu and background and passengers look textures
    if (0 != loadImages(&stationTexture, &menuBackground_texture, &entrance, &goinside_texture, numbers_texture, smiley, renderer))
        goto Quit;

    // initialize the dimensions for menu buttons and doors
    initRects(choixMenu, doorsRect);


// PROCESSING

    // display home screen
    SDL_RenderCopy(renderer, entrance, NULL, NULL);
    SDL_RenderCopy(renderer, goinside_texture, NULL, &goinside_rect);
    SDL_RenderPresent(renderer);

    // home loop
    while(!menu)       
    {
        while(SDL_PollEvent(&event))    // when an event is catched
        {
            if(event.type == SDL_QUIT)  // close the window with cross (x) button
            {
                menu = SDL_TRUE;
                start = SDL_TRUE;
                quit = SDL_TRUE;
            }

            // if the user click with the left button of the mouse
            else if(event.type == SDL_MOUSEBUTTONUP && event.button.button == SDL_BUTTON_LEFT)
            {
                mousePosition.x = event.button.x;   // read the coordinates of the click
                mousePosition.y = event.button.y;
                // on start button
                if ( SDL_PointInRect(&mousePosition, &goinside_rect))
                {
                    menu = SDL_TRUE;
                }
            }
        }
        SDL_Delay(20);
    }


    //display the menu
    SDL_RenderCopy(renderer, menuBackground_texture, NULL, NULL);
    SDL_RenderPresent(renderer);

    // menu events loop
    while(!start)       
    {
        while(SDL_PollEvent(&event))    // when an event is catched
        {
            if(event.type == SDL_QUIT)  // close the window with cross (x) button
            {
                start = SDL_TRUE;
                quit = SDL_TRUE;
            }

            // if the user click with the left button of the mouse
            else if(event.type == SDL_MOUSEBUTTONUP && event.button.button == SDL_BUTTON_LEFT)
            {
                mousePosition.x = event.button.x;   // read the coordinates of the click
                mousePosition.y = event.button.y;
                // in 1st button
                if ( SDL_PointInRect(&mousePosition, &choixMenu[0]))
                {
                    mode = 1;
                    start = SDL_TRUE;
                }
                // in 2nd button
                else if ( SDL_PointInRect(&mousePosition, &choixMenu[1]))
                {
                    mode = 2;
                    start = SDL_TRUE;
                }
                // in 3rd button
                else if ( SDL_PointInRect(&mousePosition, &choixMenu[2]))
                {
                    mode = 3;
                    start = SDL_TRUE;
                }
            }
        }
        SDL_Delay(20);
    }

/* subway simulation starts here */

    // display station
    SDL_RenderCopy(renderer, stationTexture, NULL, NULL);
    SDL_RenderPresent(renderer);

    // general loop
    while(!quit)        
    {
        // events manager
        while(SDL_PollEvent(&event))
        {
            if(event.type == SDL_QUIT)
                quit = SDL_TRUE;
        
            else if(mode == 3) {                    
                if(event.key.state == SDL_PRESSED) {        // if a key is pressed
                    if(event.key.keysym.sym == SDLK_z)
                        controlePassenger('z', liste_p, schedule, &liste_p);
                    if(event.key.keysym.sym == SDLK_q) 
                        controlePassenger('q', liste_p, schedule, &liste_p);
                    if(event.key.keysym.scancode == SDL_SCANCODE_S )
                        controlePassenger('s', liste_p, schedule, &liste_p);
                    if(event.key.keysym.scancode == SDL_SCANCODE_D )
                        controlePassenger('d', liste_p, schedule, &liste_p);
                }
                // if the user click with the left button of the mouse
                else if(event.type == SDL_MOUSEBUTTONUP && event.button.button == SDL_BUTTON_LEFT){
                    mousePosition.x = event.button.x;   // read the coordinates of the click
                    mousePosition.y = event.button.y;
                    selectPassenger(liste_p, mousePosition);    // set control over a clicked passenger 
                }
            }
        }

        newTime = SDL_GetTicks();       // timer update
        if ( newTime - oldTime > 16)    // refresh rate manager
        {
            oldTime = newTime;          // timer update

            SDL_RenderCopy(renderer, stationTexture, NULL, NULL);

            // decrement schedules 
            decrementSchedules(schedule, train1, train2);
            
            // refresh schedules display  
            displaySchedules(renderer, numbers_texture, schedule);

            // to manage when a train reach the end of the window 
            if (checkTrainsOut(train1, train2))
                updateSchedule(schedule, fmodSystem, delayed);

            // controller for the trains
            if (moveTrain(train1, doorsRect[0], renderer, fmodSystem, biip))
                SDL_RenderCopy(renderer, train1->train_texture, NULL, train1->trainPosition);

            if (moveTrain(train2, doorsRect[1], renderer, fmodSystem, biip))
                SDL_RenderCopy(renderer, train2->train_texture, NULL, train2->trainPosition);   

            if (mode > 1)   // in modes with passengers
            {
                // eventually add new passenger in the station
                addPassenger(&liste_p, schedule);
                // perform their travelling
                movePassenger(&liste_p, schedule);
                // refresh the passengers display
                displayPassengers(liste_p, smiley, renderer);
            }

            SDL_RenderPresent(renderer);    // update the display
        }
    }

// ENDING

    statut = EXIT_SUCCESS; 

Quit:
    if(NULL != biip)
    { 
        FMOD_Sound_Release(biip);
        biip = NULL;
    }
    if(NULL != biip)
    { 
        FMOD_Sound_Release(delayed);
        biip = NULL;
    }
    if(NULL != fmodSystem)
    { 
        FMOD_System_Close(fmodSystem); 
        FMOD_System_Release(fmodSystem);   
        fmodSystem = NULL; 
    }
    
    if(NULL != renderer){
        SDL_DestroyRenderer(renderer);
        renderer = NULL;
    }
    if(NULL != window){
        SDL_DestroyWindow(window);
        window = NULL;
    }
    IMG_Quit();
    SDL_Quit();

    return statut;
}

