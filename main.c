#include "main.h"

/**
 * poll_events - look for change with the keyboard
 * @instance: instance of the window + renderer
 * @angle: angle used to determine a
 * @grid: original 2D grid
 * @copy_grid: copy of the original 2D grid to work on
 * @alt: grid of z axises
 * @file: file with the z axises inside
 * @nb: number of arguments passed to the program
 * Return: 1
 */
int poll_events(SDL_Instance instance, int *angle, SDL_Point grid[8][8],
				SDL_Point copy_grid[8][8], int alt[8][8], char *file, int nb)
{
	SDL_Event event;
	SDL_KeyboardEvent key;

	grid_copy(grid, copy_grid);
	while (SDL_PollEvent(&event))
	{
		switch (event.type)
		{
			case SDL_QUIT:
				return (1);
			case SDL_KEYDOWN:
				key = event.key;
				if (key.keysym.scancode == 0x29)
					return (1);
				else if (key.keysym.scancode == SDL_SCANCODE_LEFT
						|| key.keysym.scancode == SDL_SCANCODE_RIGHT)
				{
					SDL_SetRenderDrawColor(instance.renderer, 0, 0, 0, 0);
					SDL_RenderClear(instance.renderer);
					if (key.keysym.scancode == SDL_SCANCODE_LEFT)
						*angle -= 1;
					else
						*angle += 1;
					rot_grid(copy_grid, angle);
					init_iso_grid(copy_grid, alt, file, nb);
					draw_grid(instance, copy_grid);
				}
			break;
		}
	}
	return (0);
}

/**
 * main - Entry point
 * @ac: number of arguments
 * @av: array of arguments
 * Return: 0 or 1
 */
int main(int ac, char **av)
{
	SDL_Instance instance;
	SDL_Point grid[8][8], copy_grid[8][8];
	int alt[8][8];
	int angle = 0;

	if (init_instance(&instance) != 0)
		return (1);

	SDL_SetRenderDrawColor(instance.renderer, 0, 0, 0, 0);
	SDL_RenderClear(instance.renderer);
	init_2d_grid(grid);
	grid_copy(grid, copy_grid);
	init_iso_grid(copy_grid, alt, av[1], ac);
	draw_grid(instance, copy_grid);

	while (1)
	{
		if (poll_events(instance, &angle, grid, copy_grid, alt, av[1], ac)
			== 1)
			break;
		SDL_RenderPresent(instance.renderer);
	}
	SDL_DestroyRenderer(instance.renderer);
	SDL_DestroyWindow(instance.window);
	SDL_Quit();
	return (0);
}
