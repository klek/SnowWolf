#include <SDL.h>
#include <stdio.h>

int main(int argc, char *argv[])
{
	// Previously used messagebox for SDL
//	SDL_ShowSimpleMessageBox(SDL_MESSAGEBOX_INFORMATION, "SnowWolf", "This is SnowWolf", 0);


	// Variables
	SDL_Window *Window;

	if (SDL_Init(SDL_INIT_VIDEO) != 0) {
		// Todo: SDL_Init didn't work!
		fprintf(stderr, "Unable to initialize SDL: %s\n", SDL_GetError());
		return 1;
	}

	// Setting up the SDL window
	Window = SDL_CreateWindow("SnowWolf",
				  SDL_WINDOWPOS_UNDEFINED,
				  SDL_WINDOWPOS_UNDEFINED,
				  640,
				  480,
				  SDL_WINDOW_RESIZABLE);


	// Shutdown SDL
	SDL_Quit();

	return 0;
}
