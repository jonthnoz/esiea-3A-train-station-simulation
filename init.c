#include <stdio.h>
#include <stdlib.h>
#include <SDL2/SDL.h>
#include <SDL2/SDL_image.h>
#include "mode1.h"



/* Initializations, creation of the window and the renderer. */
int init(SDL_Window **window, SDL_Renderer **renderer, int w, int h)
{
    if(0 != SDL_Init(SDL_INIT_VIDEO))
    {
        fprintf(stderr, "Error SDL_Init : %s file:%s line:%d\n", SDL_GetError(), __FILE__, __LINE__);
        return -1;
    }
    
    *window = SDL_CreateWindow("Simulateur Metro 3A", SDL_WINDOWPOS_CENTERED, SDL_WINDOWPOS_CENTERED, w, h, SDL_WINDOW_SHOWN);
    if(NULL == *window)
    {
        fprintf(stderr, "Error SDL_CreateWindow : %s file:%s line:%d\n", SDL_GetError(), __FILE__, __LINE__);
        return -1;
    }
    
    *renderer = SDL_CreateRenderer(*window, -1, SDL_RENDERER_PRESENTVSYNC);
    if(NULL == *renderer)
    {
        fprintf(stderr, "Error SDL_CreateRenderer : %s file:%s line:%d\n", SDL_GetError(), __FILE__, __LINE__);
        return -1;
    }

    return 0;
}

// loading of a picture
SDL_Texture *loadImage(const char path[], SDL_Renderer *renderer)
{
    SDL_Texture *texture = NULL;
    texture = IMG_LoadTexture(renderer, path);
    if(NULL == texture)
    {
        fprintf(stderr, "Erreur IMG_LoadTexture : %s file:%s line:%d\n", IMG_GetError(), __FILE__, __LINE__);
        return NULL;
    }

    return texture;
}

int loadImages(SDL_Texture **stationTexture, SDL_Texture **menuBackground_texture, SDL_Texture **entrance, SDL_Texture **goinside, SDL_Texture *numbers_texture[21], SDL_Texture *smiley[6], SDL_Renderer *renderer)
{
	*stationTexture = loadImage("images/station.bmp", renderer); // station background
    if (*stationTexture == NULL)
        return -1;

    *menuBackground_texture = loadImage("images/menu.jpg", renderer); // menu background 
    if (*menuBackground_texture == NULL)
        return -1;

    *entrance = loadImage("images/entree_station.bmp", renderer); // home backgroung 
    if (*menuBackground_texture == NULL)
        return -1;

    *goinside = loadImage("images/goinside.png", renderer); // home backgroung 
    if (*menuBackground_texture == NULL)
        return -1;

    numbers_texture[0] = loadImage("images/0.png", renderer);  // schedules
    if (numbers_texture[0] == NULL)
        return -1;
    numbers_texture[1] = loadImage("images/1.png", renderer);
    if (numbers_texture[1] == NULL)
        return -1;
    numbers_texture[2] = loadImage("images/2.png", renderer);
    if (numbers_texture[2] == NULL)
        return -1;
    numbers_texture[3] = loadImage("images/3.png", renderer);
    if (numbers_texture[3] == NULL)
        return -1;
    numbers_texture[4] = loadImage("images/4.png", renderer);
    if (numbers_texture[4] == NULL)
        return -1;
    numbers_texture[5] = loadImage("images/5.png", renderer);
    if (numbers_texture[5] == NULL)
        return -1;
    numbers_texture[6] = loadImage("images/6.png", renderer);
    if (numbers_texture[6] == NULL)
        return -1;
    numbers_texture[7] = loadImage("images/7.png", renderer);
    if (numbers_texture[7] == NULL)
        return -1;
    numbers_texture[8] = loadImage("images/8.png", renderer);
    if (numbers_texture[8] == NULL)
        return -1;
    numbers_texture[9] = loadImage("images/9.png", renderer);
    if (numbers_texture[9] == NULL)
        return -1;
    numbers_texture[10] = loadImage("images/10.png", renderer);
    if (numbers_texture[10] == NULL)
        return -1;
    numbers_texture[11] = loadImage("images/11.png", renderer);
    if (numbers_texture[11] == NULL)
        return -1;
    numbers_texture[12] = loadImage("images/12.png", renderer);
    if (numbers_texture[12] == NULL)
        return -1;
    numbers_texture[13] = loadImage("images/13.png", renderer);
    if (numbers_texture[13] == NULL)
        return -1;
    numbers_texture[14] = loadImage("images/14.png", renderer);
    if (numbers_texture[14] == NULL)
        return -1;
    numbers_texture[15] = loadImage("images/15.png", renderer);
    if (numbers_texture[15] == NULL)
        return -1;
    numbers_texture[16] = loadImage("images/16.png", renderer);
    if (numbers_texture[16] == NULL)
        return -1;
    numbers_texture[17] = loadImage("images/17.png", renderer);
    if (numbers_texture[17] == NULL)
        return -1;
    numbers_texture[18] = loadImage("images/18.png", renderer);
    if (numbers_texture[18] == NULL)
        return -1;
    numbers_texture[19] = loadImage("images/19.png", renderer);
    if (numbers_texture[19] == NULL)
        return -1;
    numbers_texture[20] = loadImage("images/++.png", renderer);
    if (numbers_texture[20] == NULL)
        return -1;

    smiley[0] = loadImage("images/normal.png", renderer);  // passenger images
    if (smiley[0] == NULL)
        return -1;
    smiley[1] = loadImage("images/lilsmile.png", renderer);
    if (smiley[1] == NULL)
        return -1;
    smiley[2] = loadImage("images/smile.png", renderer);
    if (smiley[2] == NULL)
        return -1;
    smiley[3] = loadImage("images/papi.png", renderer);  
    if (smiley[3] == NULL)
        return -1;
    smiley[4] = loadImage("images/sad.png", renderer);
    if (smiley[4] == NULL)
        return -1;
    smiley[5] = loadImage("images/missed.png", renderer);
    if (smiley[5] == NULL)
        return -1;
    return 0;
}

void initRects(SDL_Rect choixMenu[3], SDL_Rect doorsRect[2][16])
{
    // define the menu buttons location
    choixMenu[0].x = 185;
    choixMenu[0].y = 310;
    choixMenu[0].w = 235;    
    choixMenu[0].h = 160;

    choixMenu[1].x = 622;
    choixMenu[1].y = 310;
    choixMenu[1].w = 235;    
    choixMenu[1].h = 160;

    choixMenu[2].x = 1150;
    choixMenu[2].y = 310;
    choixMenu[2].w = 235;    
    choixMenu[2].h = 160;    

    // set up the doors location
    for (int i = 0; i < 16; i++)
    {
        doorsRect[0][i].w = 36;
        doorsRect[1][i].w = 36;
        doorsRect[0][i].h = 8;
        doorsRect[1][i].h = 8;
        doorsRect[0][i].y = 204;
        doorsRect[1][i].y = SCREEN_HEIGHT-210;
    }
    for (int i = 0; i < 2; i++)
    {
        doorsRect[i][0].x = 131;
        doorsRect[i][1].x = 131+35;
        doorsRect[i][2].x = 311;
        doorsRect[i][3].x = 311+35;
        doorsRect[i][4].x = 492;
        doorsRect[i][5].x = 492+35;
        doorsRect[i][6].x = 666;
        doorsRect[i][7].x = 666+35;
        doorsRect[i][8].x = SCREEN_WIDTH-666-35-36;
        doorsRect[i][9].x = SCREEN_WIDTH-666-36;
        doorsRect[i][10].x = SCREEN_WIDTH-492-35-36;
        doorsRect[i][11].x = SCREEN_WIDTH-492-36;
        doorsRect[i][12].x = SCREEN_WIDTH-311-35-36;
        doorsRect[i][13].x = SCREEN_WIDTH-311-36;
        doorsRect[i][14].x = SCREEN_WIDTH-131-35-36;
        doorsRect[i][15].x = SCREEN_WIDTH-131-36;
    }
}