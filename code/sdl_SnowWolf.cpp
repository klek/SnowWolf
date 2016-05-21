#include <SDL.h>
#include <stdio.h>
#include <sys/mman.h>
#include <stdint.h>

// Macros
#define internal static
#define local_persist static
#define global_variable static

// Typedefs
typedef int8_t int8;
typedef int16_t int16;
typedef int32_t int32;
typedef int64_t int64;

typedef uint8_t uint8;
typedef uint16_t uint16;
typedef uint32_t uint32;
typedef uint64_t uint64;

// Global variables
global_variable SDL_Texture *texture = 0;
global_variable void *bitMapMemory = 0;
global_variable int bitMapWidth = 0;
global_variable int bitMapHeight = 0;
global_variable int bytesPerPixel = 4;


internal void
RenderWeirdGradient(int blueOffset, int greenOffset)
{
  int width = bitMapWidth;
  int height = bitMapHeight;

  int pitch = width * bytesPerPixel;
  uint8 *row = (uint8 *)bitMapMemory;

  for (int Y = 0; Y < bitMapHeight; Y++)
  {
    uint32 *pixel = (uint32 *)row;

    for (int X = 0; X < bitMapWidth; X++)
    {
      uint8 blue = (X + blueOffset);
      uint8 green = (Y + greenOffset);

      *pixel++ = ((green << 8) | blue);
    }

    row += pitch;
  }
}

// Function for resizing a texture used with SDL
internal void
SDLResizeTexture(SDL_Renderer *renderer, int width, int height)
{
  if (bitMapMemory)
  {
    // Deallocating the memory stored at bitMapMemory. Previously used free() here
    munmap(bitMapMemory,
	   bitMapWidth * bitMapHeight * bytesPerPixel);
  }
  if (texture)
  {
    SDL_DestroyTexture(texture);
  }

  texture = SDL_CreateTexture(renderer,
			      SDL_PIXELFORMAT_ARGB8888,
			      SDL_TEXTUREACCESS_STREAMING,
			      width,
			      height);

  bitMapWidth = width;
  bitMapHeight = height;

  // Allocating memory. Previously used malloc() here.
  bitMapMemory = mmap(0,
		      width * height * bytesPerPixel,
		      PROT_READ | PROT_WRITE,
		      MAP_PRIVATE | MAP_ANONYMOUS,
		      -1,
		      0);
}


// Function to update the window
internal void
SDLUpdateWindow(SDL_Window *window, SDL_Renderer *renderer)
{
  SDL_UpdateTexture(texture,
		    0,
		    bitMapMemory,
		    bitMapWidth * bytesPerPixel);

  SDL_RenderCopy(renderer,
		 texture,
		 0,
		 0);

  SDL_RenderPresent(renderer);
}


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

        case SDL_WINDOWEVENT_SIZE_CHANGED:
	{
	  SDL_Window *window = SDL_GetWindowFromID(Event->window.windowID);
	  SDL_Renderer *renderer = SDL_GetRenderer(window);
	  printf("SDL_WINDOWEVENT_SIZE_CHANGED (%d, %d)\n", Event->window.data1, Event->window.data2);
	  SDLResizeTexture(renderer, Event->window.data1, Event->window.data2);
	} break;

	case SDL_WINDOWEVENT_FOCUS_GAINED:
	{
	  printf("SDL_WINDOWEVENT_FOCUS_GAINED\n");
	} break;
	  
        case SDL_WINDOWEVENT_EXPOSED:
	{
	  SDL_Window *window = SDL_GetWindowFromID(Event->window.windowID);
	  SDL_Renderer *renderer = SDL_GetRenderer(window);
	  SDLUpdateWindow(window, renderer);
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
	    bool running = true;
	    int width, height;
	    SDL_GetWindowSize(window, &width, &height);
	    SDLResizeTexture(renderer, width, height);
	    int xOffset = 0;
	    int yOffset = 0;
	    
	    while (running)
	    {
	      SDL_Event Event;
	      while (SDL_PollEvent(&Event))
	      {
		if ( handleEvent(&Event) )
		{
		  running = false;
		}
	      }
	      RenderWeirdGradient(xOffset, yOffset);
	      SDLUpdateWindow(window, renderer);

	      ++xOffset;
	      yOffset += 2;
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
