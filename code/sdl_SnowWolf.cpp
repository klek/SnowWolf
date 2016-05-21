#include <SDL.h>
#include <stdio.h>

// Functions
bool handleEvent(SDL_Event * Event)
{
  
  bool shouldQuit = false;

  switch(Event->type)
  {
    case SDL_QUIT:
    {
      printf("SDL_QUIT\n");
      shouldQuit = true;
    } break;

    case SDL_WINDOWEVENT:
    {
      switch(Event->window.event)
      {
        case SDL_WINDOWEVENT_RESIZED:
	{
	  printf("SDL_WINDOWEVENT_RESIZED (%d, %d)\n", Event->window.data1, Event->window.data2);
	} break;

	case SDL_WINDOWEVENT_FOCUS_GAINED:
	{
	  printf("SDL_WINDOWEVENT_FOCUS_GAINED\n");
	} break;
	  
        case SDL_WINDOWEVENT_EXPOSED:
	{
	  SDL_Window *window = SDL_GetWindowFromID(Event->window.windowID);
	  SDL_Renderer *renderer = SDL_GetRenderer(window);
	  static bool isWhite = true;
	  if ( isWhite == true )
	  {
	    SDL_SetRenderDrawColor(renderer, 255, 255, 255, 255);
	    isWhite = false;
	  }
	  else
	  {
	    SDL_SetRenderDrawColor(renderer, 0, 0, 0, 255);
	    isWhite = true;
	  }

	  SDL_RenderClear(renderer);
	  SDL_RenderPresent(renderer);
	} break;
      }
    } break;
  }

  // Return value
  return(shouldQuit);
}

int main(int argc, char *argv[])
{
	// Previously used messagebox for SDL
//	SDL_ShowSimpleMessageBox(SDL_MESSAGEBOX_INFORMATION, "SnowWolf", "This is SnowWolf", 0);


	if (SDL_Init(SDL_INIT_VIDEO) != 0) {
		// Todo: SDL_Init didn't work!
		fprintf(stderr, "Unable to initialize SDL: %s\n", SDL_GetError());
		return 1;
	}

	// Setting up the SDL window
	SDL_Window *window = SDL_CreateWindow("SnowWolf",
					      SDL_WINDOWPOS_UNDEFINED,
					      SDL_WINDOWPOS_UNDEFINED,
					      640,
					      480,
					      SDL_WINDOW_RESIZABLE);

	if (window)
	{
	  // Create a "Renderer"
	  SDL_Renderer *renderer = SDL_CreateRenderer(window,
						      -1,
						      0);
	  if (renderer)
	  {
	    for( ; ; )
	    {
	      SDL_Event Event;
	      SDL_WaitEvent(&Event);
	      
	      if ( handleEvent(&Event) )
	      {
		break;
	      }
	    }
	  }
	  else
	  {
	    // TODO: Add logging
	  }
	}
	else
	{
	  // Todo: Add logging
	}


	// Shutdown SDL
	SDL_Quit();

	return 0;
}
