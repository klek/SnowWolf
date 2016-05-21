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

// Structs
struct sdl_offscreen_buffer
{
  // Note: Pixels are always 32-bits wide, memory order BB GG RR XX
  SDL_Texture *texture;
  void *memory;
  int width;
  int height;
  int pitch;
};

struct sdl_window_dimension
{
  int width;
  int height;
};

// Global variables
global_variable sdl_offscreen_buffer globalBackBuffer;


// Function to get the dimensions of the current window
sdl_window_dimension
SDLGetWindowDimension(SDL_Window *window)
{
  sdl_window_dimension result;

  SDL_GetWindowSize(window, &result.width, &result.height);

  return(result);
}

// Function to render a gradient to our backbuffer which later will be output to the
// SDLUpdateWindow()
internal void
RenderWeirdGradient(sdl_offscreen_buffer *buffer, int blueOffset, int greenOffset)
{
  uint8 *row = (uint8 *)buffer->memory;

  for (int Y = 0; Y < buffer->height; Y++)
  {
    uint32 *pixel = (uint32 *)row;

    for (int X = 0; X < buffer->width; X++)
    {
      uint8 blue = (X + blueOffset);
      uint8 green = (Y + greenOffset);

      *pixel++ = ((green << 8) | blue);
    }

    row += buffer->pitch;
  }
}

// Function for resizing a texture used with SDL
internal void
SDLResizeTexture(sdl_offscreen_buffer *buffer, SDL_Renderer *renderer, int width, int height)
{
  // Set the bytesPerPixel to 4
  int bytesPerPixel = 4;
  
  if (buffer->memory)
  {
    // Deallocating the memory stored at bitMapMemory. Previously used free() here
    munmap(buffer->memory,
	   buffer->width * buffer->height * bytesPerPixel);
  }
  if (buffer->texture)
  {
    SDL_DestroyTexture(buffer->texture);
  }

  buffer->texture = SDL_CreateTexture(renderer,
			      SDL_PIXELFORMAT_ARGB8888,
			      SDL_TEXTUREACCESS_STREAMING,
			      width,
			      height);

  buffer->width = width;
  buffer->height = height;
  buffer->pitch = width * bytesPerPixel;

  // Allocating memory. Previously used malloc() here.
  buffer->memory = mmap(0,
		      width * height * bytesPerPixel,
		      PROT_READ | PROT_WRITE,
		      MAP_PRIVATE | MAP_ANONYMOUS,
		      -1,
		      0);
}


// Function to update the window
internal void
SDLUpdateWindow(SDL_Window *window, SDL_Renderer *renderer, sdl_offscreen_buffer buffer)
{
  SDL_UpdateTexture(buffer.texture,
		    0,
		    buffer.memory,
		    buffer.pitch);

  SDL_RenderCopy(renderer,
		 buffer.texture,
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
	} break;

	case SDL_WINDOWEVENT_FOCUS_GAINED:
	{
	  printf("SDL_WINDOWEVENT_FOCUS_GAINED\n");
	} break;
	  
        case SDL_WINDOWEVENT_EXPOSED:
	{
	  SDL_Window *window = SDL_GetWindowFromID(Event->window.windowID);
	  SDL_Renderer *renderer = SDL_GetRenderer(window);
	  SDLUpdateWindow(window, renderer, globalBackBuffer);
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
	    sdl_window_dimension dimension = SDLGetWindowDimension(window);
	    SDLResizeTexture(&globalBackBuffer, renderer, dimension.width, dimension.height);
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
	      RenderWeirdGradient(&globalBackBuffer, xOffset, yOffset);
	      SDLUpdateWindow(window, renderer, globalBackBuffer);

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
