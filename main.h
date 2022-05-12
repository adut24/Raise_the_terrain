#ifndef MAIN_H
#define MAIN_H
#include <SDL.h>
#include <string.h>
#include <stdio.h>
#include <stdlib.h>
#include <math.h>

/**
 * struct SDL_Instance - Instance created
 * @window: pointer to the window
 * @renderer: pointer to the renderer
 */
typedef struct SDL_Instance
{
	SDL_Window *window;
	SDL_Renderer *renderer;
} SDL_Instance;

int init_instance(SDL_Instance *);
void init_2d_grid(SDL_Point grid[8][8]);
void init_iso_grid(SDL_Point grid[8][8], int alt[8][8], char *file, int nb);
void grid_copy(SDL_Point grid[8][8], SDL_Point copy_grid[8][8]);
void draw_grid(SDL_Instance instance, SDL_Point grid[8][8]);
void rot_grid(SDL_Point grid[8][8], int *angle);

#endif /* MAIN_H */
