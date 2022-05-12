#include "main.h"

/**
 * init_2d_grid - store all the points of the 2D grid
 * @grid: grid used to store the points
 */
void init_2d_grid(SDL_Point grid[8][8])
{
	int i, j, x, y;

	for (x = 150, i = 0; x < 950; x += 100, i++)
	{
		for (y = 50, j = 0; y < 850; y += 100, j++)
		{
			grid[i][j].x = x;
			grid[i][j].y = y;
		}
	}
}

/**
 * init_iso_grid - convert the 2D grid into an isometric one
 * @grid: grid to convert
 * @alt: grid used to store the z axises
 * @file: file containing the z axises
 * @nb: number of arguments passed to the program
 */
void init_iso_grid(SDL_Point grid[8][8], int alt[8][8], char *file, int nb)
{
	char line[1000];
	char *value;
	int z, i, j;
	float wX, wY, inc = 0.65;
	FILE *fd;

	if (nb == 2)
	{
		fd = fopen(file, "r");
		i = 0;
		while (fgets(line, 1000, fd))
		{
			value = strtok(line, " ");
			for (j = 0; j < 8; j++)
			{
				alt[j][i] = atoi(value);
				value = strtok(NULL, " ");
			}
			i++;
		}
		fclose(fd);
	}

	for (i = 0; i < 8; i++)
	{
		for (j = 0; j < 8; j++)
		{
			if (nb == 2)
				z = alt[i][j];
			else
				z = 0;
			wX = inc * grid[i][j].x - inc * grid[i][j].y + 430;
			wY = (1 - inc) * grid[i][j].x + (1 - inc) * grid[i][j].y - z + 100;
			grid[i][j].x = wX;
			grid[i][j].y = wY;
		}
	}
}

/**
 * draw_grid - draw an isometric grid
 * @instance: instance of the window + renderer
 * @grid: grid of the point to use to print
 */
void draw_grid(SDL_Instance instance, SDL_Point grid[8][8])
{
	int i, j;

	SDL_SetRenderDrawColor(instance.renderer, 0xFF, 0xFF, 0xFF, 0xFF);

	for (i = 0; i < 7; i++)
	{
		for (j = 0; j < 8; j++)
		{
			SDL_RenderDrawLine(instance.renderer, grid[i][j].x, grid[i][j].y,
				grid[i + 1][j].x, grid[i + 1][j].y);
		}
	}

	for (i = 0; i < 8; i++)
	{
		for (j = 0; j < 7; j++)
		{
			SDL_RenderDrawLine(instance.renderer, grid[i][j].x, grid[i][j].y,
				grid[i][j + 1].x, grid[i][j + 1].y);
		}
	}
}

/**
 * grid_copy - copy the original points of the grid
 * @grid: grid to copy
 * @copy_grid: copy receiving the points
 */
void grid_copy(SDL_Point grid[8][8], SDL_Point copy_grid[8][8])
{
	int i, j;

	for (i = 0; i < 8; i++)
	{
		for (j = 0; j < 8; j++)
		{
			copy_grid[i][j].x = grid[i][j].x;
			copy_grid[i][j].y = grid[i][j].y;
		}
	}
}

/**
 * rot_grid - rotate the grid
 * @grid: grid to rotate
 * @angle: angle used to rotate
 */
void rot_grid(SDL_Point grid[8][8], int *angle)
{
	float a, rX, rY;
	int i, j;

	a = *angle * M_PI / 180;
	for (i = 0; i < 8; i++)
	{
		for (j = 0; j < 8; j++)
		{
			rX = (grid[i][j].x - 500) * cos(a) - (grid[i][j].y - 400) * sin(a);
			rX += 500;
			rY = (grid[i][j].x - 500) * sin(a) + (grid[i][j].y - 400) * cos(a);
			rY += 400;
			grid[i][j].x = rX;
			grid[i][j].y = rY;

		}
	}
}
