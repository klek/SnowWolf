#include <SDL.h>

int main(int argc, char *argv[])
{
	// Initializing SDL video
	if ( SDL_Init(SDL_INIT_VIDEO) != 0 ) 
	{
		// TODO: Handle if SDL_Init fails
	}


	// Shutdown SDL before we quit
	SDL_Quit();
	return 0;
}
