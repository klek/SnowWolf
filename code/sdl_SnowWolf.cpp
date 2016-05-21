#include <SDL.h>
#include <stdio.h>
#include <sys/mman.h>
#include <stdint.h>
// Implement sine ourselves
#include <math.h>

// Macros
#define internal static
#define local_persist static
#define global_variable static

#define Pi32 3.14159265359f
#define MAX_CONTROLLERS 4

// Typedefs
typedef int8_t int8;
typedef int16_t int16;
typedef int32_t int32;
typedef int64_t int64;

typedef uint8_t uint8;
typedef uint16_t uint16;
typedef uint32_t uint32;
typedef uint64_t uint64;

typedef float real32;
typedef double real64;

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

struct sdl_audio_ring_buffer
{
  int size;
  int writeCursor;
  int playCursor;
  void *data;
};

struct sdl_sound_output
{
  int samplesPerSecond;
  int toneHz;
  int16 toneVolume;
  uint32 runningSampleIndex;
  int wavePeriod;
  int bytesPerSample;
  int secondaryBufferSize;
  real32 tSine;
  int latencySampleCount;
};

// Global variables
global_variable sdl_audio_ring_buffer audioRingBuffer;
global_variable sdl_offscreen_buffer globalBackBuffer;
global_variable SDL_GameController *controllerHandles[MAX_CONTROLLERS];
global_variable SDL_Haptic *rumbleHandles[MAX_CONTROLLERS];

// Callback-function to the SDL_AudioSpec structure
// This is needed whenever more audio data is required.
internal void
SDLAudioCallback(void *userData, uint8 *audioData, int length)
{
  sdl_audio_ring_buffer *ringBuffer = (sdl_audio_ring_buffer *)userData;

  int region1Size = length;
  int region2Size = 0;
  if ( ringBuffer->playCursor + length > ringBuffer->size )
  {
    region1Size = ringBuffer->size - ringBuffer->playCursor;
    region2Size = length - region1Size;
  }
  memcpy(audioData, (uint8 *)(ringBuffer->data) + ringBuffer->playCursor, region1Size);
  memcpy(&audioData[region1Size], ringBuffer->data, region2Size);
  ringBuffer->playCursor = (ringBuffer->playCursor + length) % ringBuffer->size;
  ringBuffer->writeCursor = (ringBuffer->playCursor + 2048) % ringBuffer->size;

}

// Function to initialize the audio spec
internal void
SDLInitAudio(int32 samplesPerSecond, int32 bufferSize)
{
  SDL_AudioSpec audioSettings = {0};

  audioSettings.freq = samplesPerSecond;
  audioSettings.format = AUDIO_S16LSB;
  audioSettings.channels = 2;
  audioSettings.samples = 512;
  audioSettings.callback = &SDLAudioCallback;
  audioSettings.userdata = &audioRingBuffer;

  audioRingBuffer.size = bufferSize;
  audioRingBuffer.data = malloc(bufferSize);
  audioRingBuffer.playCursor = audioRingBuffer.writeCursor = 0;
  
  SDL_OpenAudio(&audioSettings, 0);

  printf("Initialized an Audio device at frequency %d Hz, %d channels and buffer size equal to %d\n",
	 audioSettings.freq, audioSettings.channels, audioSettings.samples);

  if ( audioSettings.format != AUDIO_S16LSB )
  {
    printf("We didn't get AUDIO_S16LSB as our sample format!\n");
    SDL_CloseAudio();
  }

}

// Function to fill the soundbuffer with data
internal void
SDLFillSoundBuffer(sdl_sound_output *soundOutput, int byteToLock, int bytesToWrite)
{
  void *region1 = (uint8 *)audioRingBuffer.data + byteToLock;
  int region1Size = bytesToWrite;
  if ( region1Size + byteToLock > soundOutput->secondaryBufferSize )
  {
    region1Size = soundOutput->secondaryBufferSize - byteToLock;
  }
  void *region2 = audioRingBuffer.data;
  int region2Size = bytesToWrite - region1Size;

  int region1SampleCount = region1Size / soundOutput->bytesPerSample;
  int16 *sampleOut = (int16 *)region1;
  for ( int sampleIndex = 0; sampleIndex < region1SampleCount; ++sampleIndex )
  {
    real32 sineValue = sinf(soundOutput->tSine);
    int16 sampleValue = (int16)(sineValue * soundOutput->toneVolume);
    *sampleOut++ = sampleValue;
    *sampleOut++ = sampleValue;

    soundOutput->tSine += 2.0f * Pi32 * 1.0f / (real32)soundOutput->wavePeriod;
    ++soundOutput->runningSampleIndex;
  }

  int region2SampleCount = region2Size / soundOutput->bytesPerSample;
  sampleOut = (int16 *)region2;
  for ( int sampleIndex = 0; sampleIndex < region2SampleCount; ++sampleIndex )
  {
    real32 sineValue = sinf(soundOutput->tSine);
    int16 sampleValue = (int16)(sineValue * soundOutput->toneVolume);
    *sampleOut++ = sampleValue;
    *sampleOut++ = sampleValue;

    soundOutput->tSine += 2.0f * Pi32 * 1.0f / (real32)soundOutput->wavePeriod;
    ++soundOutput->runningSampleIndex;
  }

}

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


// Function to handle SDL events
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

    case SDL_KEYDOWN:
    {

    }

    case SDL_KEYUP:
    {
      SDL_Keycode keyCode = Event->key.keysym.sym;
      bool isDown = (Event->key.state == SDL_PRESSED);
      bool wasDown = false;

      if ( Event->key.state == SDL_RELEASED )
      {
	wasDown = true;
      }
      else if ( Event->key.repeat != 0 )
      {
	wasDown = true;
      }

      // Note:
      if ( Event->key.repeat == 0 )
      {
	if ( keyCode == SDLK_w )
	{
	  printf("W \n");
	}
	else if ( keyCode == SDLK_a )
	{
	}
	else if ( keyCode == SDLK_s )
	{
	}
	else if ( keyCode == SDLK_d )
	{
	}
	else if ( keyCode == SDLK_q )
	{
	}
	else if ( keyCode == SDLK_e )
	{
	}
	else if ( keyCode == SDLK_UP )
	{
	}
	else if ( keyCode == SDLK_LEFT )
	{
	}
	else if ( keyCode == SDLK_DOWN )
	{
	}
	else if ( keyCode == SDLK_RIGHT )
	{
	}
	else if ( keyCode == SDLK_ESCAPE )
	{
	  printf("ESCAPE: ");
	  if ( isDown )
	  {
	    printf("is down \n");
	  }
	  if ( wasDown )
	  {
	    printf("was down \n");
	  }

	  // If escape is pressed we also stop the program
	  // by simply putting a new event onto the queue
	  //SDL_Event userEvent;
	  //userEvent.type = SDL_QUIT;
	  //SDL_PushEvent(&userEvent);

	  // Note: Stop the program from running can also be done
	  // by simply setting the shouldQuit to true
	  shouldQuit = true;
	}
	else if ( keyCode == SDLK_SPACE )
	{
	}

      }
      
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

// Function to open game controllers
internal void
SDLOpenGameControllers(void)
{
  int maxJoysticks = SDL_NumJoysticks();
  int controllerIndex = 0;

  for ( int joystickIndex = 0; joystickIndex < maxJoysticks; ++joystickIndex)
  {
    if ( !SDL_IsGameController(joystickIndex) )
    {
      continue;
    }
    if ( controllerIndex >= MAX_CONTROLLERS )
    {
      break;
    }

    controllerHandles[controllerIndex] = SDL_GameControllerOpen(joystickIndex);
    rumbleHandles[controllerIndex] = SDL_HapticOpen(joystickIndex);

    if ( rumbleHandles[controllerIndex] &&
	 SDL_HapticRumbleInit(rumbleHandles[controllerIndex]) != 0)
    {
      SDL_HapticClose(rumbleHandles[controllerIndex]);
      rumbleHandles[controllerIndex] = 0;
    }

    controllerIndex++;
  }
}

// Function for closing game controllers
internal void
SDLCloseGameControllers(void)
{
  for ( int controllerIndex = 0; controllerIndex < MAX_CONTROLLERS; ++controllerIndex )
  {
    if ( controllerHandles[controllerIndex] )
    {
      if ( rumbleHandles[controllerIndex] )
      {
	SDL_HapticClose(rumbleHandles[controllerIndex]);
      }
      SDL_GameControllerClose(controllerHandles[controllerIndex]);
    }
  }
}

int main(int argc, char *argv[])
{
	// Previously used messagebox for SDL
//	SDL_ShowSimpleMessageBox(SDL_MESSAGEBOX_INFORMATION, "SnowWolf", "This is SnowWolf", 0);


	if (SDL_Init(SDL_INIT_VIDEO | SDL_INIT_GAMECONTROLLER | SDL_INIT_HAPTIC | SDL_INIT_AUDIO) != 0) {
		fprintf(stderr, "Unable to initialize SDL: %s\n", SDL_GetError());
		return 1;
	}

	// Initializing game controllers
	SDLOpenGameControllers();

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
	    
	    // Note: Testing sound
	    sdl_sound_output soundOutput = {};
	    soundOutput.samplesPerSecond = 48000;
	    soundOutput.toneHz = 256;
	    soundOutput.toneVolume = 5000;
	    soundOutput.runningSampleIndex = 0;
	    soundOutput.wavePeriod = soundOutput.samplesPerSecond / soundOutput.toneHz;
	    soundOutput.bytesPerSample = sizeof(int16) * 2;
	    soundOutput.secondaryBufferSize = soundOutput.samplesPerSecond * soundOutput.bytesPerSample;
	    soundOutput.tSine = 0.0f;
	    soundOutput.latencySampleCount = soundOutput.samplesPerSecond / 15;

	    // Open our audio device
	    SDLInitAudio(48000, soundOutput.secondaryBufferSize);
	    SDLFillSoundBuffer(&soundOutput, 0, soundOutput.latencySampleCount * soundOutput.bytesPerSample);
	    SDL_PauseAudio(0);
	
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

	      // Poll the controllers for input
	      for ( int controllerIndex = 0; controllerIndex < MAX_CONTROLLERS; ++controllerIndex)
	      {
		if ( controllerHandles[controllerIndex] != 0 &&
		     SDL_GameControllerGetAttached(controllerHandles[controllerIndex]) )
		{
		  // Note: We have a controller with index controllerIndex
		  bool up = SDL_GameControllerGetButton(controllerHandles[controllerIndex],
							SDL_CONTROLLER_BUTTON_DPAD_UP);
		  bool down = SDL_GameControllerGetButton(controllerHandles[controllerIndex],
							  SDL_CONTROLLER_BUTTON_DPAD_DOWN);
		  bool left = SDL_GameControllerGetButton(controllerHandles[controllerIndex],
							  SDL_CONTROLLER_BUTTON_DPAD_LEFT);
		  bool right = SDL_GameControllerGetButton(controllerHandles[controllerIndex],
							   SDL_CONTROLLER_BUTTON_DPAD_RIGHT);
		  bool start = SDL_GameControllerGetButton(controllerHandles[controllerIndex],
							   SDL_CONTROLLER_BUTTON_START);
		  bool back = SDL_GameControllerGetButton(controllerHandles[controllerIndex],
							  SDL_CONTROLLER_BUTTON_BACK);
		  bool leftShoulder = SDL_GameControllerGetButton(controllerHandles[controllerIndex],
								  SDL_CONTROLLER_BUTTON_LEFTSHOULDER);
		  bool rightShoulder = SDL_GameControllerGetButton(controllerHandles[controllerIndex],
								   SDL_CONTROLLER_BUTTON_RIGHTSHOULDER);
		  bool aButton = SDL_GameControllerGetButton(controllerHandles[controllerIndex],
							     SDL_CONTROLLER_BUTTON_A);		  
		  bool bButton = SDL_GameControllerGetButton(controllerHandles[controllerIndex],
							     SDL_CONTROLLER_BUTTON_B);
		  bool xButton = SDL_GameControllerGetButton(controllerHandles[controllerIndex],
							     SDL_CONTROLLER_BUTTON_X);
		  bool yButton = SDL_GameControllerGetButton(controllerHandles[controllerIndex],
							  SDL_CONTROLLER_BUTTON_Y);

		  int16 stickX = SDL_GameControllerGetAxis(controllerHandles[controllerIndex],
							   SDL_CONTROLLER_AXIS_LEFTX);
		  int16 stickY = SDL_GameControllerGetAxis(controllerHandles[controllerIndex],
							   SDL_CONTROLLER_AXIS_LEFTY);

		  if (aButton)
		  {
		    yOffset += 2;
		  }
		  if (bButton)
		  {
		    if ( rumbleHandles[controllerIndex] )
		    {
		      SDL_HapticRumblePlay(rumbleHandles[controllerIndex], 0.5f, 2000);
		    }
		  }
		  
		}
		else
		{
		  // Todo:  This controller isn't plugged in
		}
	      }
	      
	      RenderWeirdGradient(&globalBackBuffer, xOffset, yOffset);

	      // Sound output test
	      SDL_LockAudio();
	      int byteToLock = (soundOutput.runningSampleIndex *
				soundOutput.bytesPerSample) %
		                soundOutput.secondaryBufferSize;
	      int targetCursor = ((audioRingBuffer.playCursor +
				  (soundOutput.latencySampleCount * soundOutput.bytesPerSample)) %
				  soundOutput.secondaryBufferSize);
	      int bytesToWrite;
	      if ( byteToLock > targetCursor )
	      {
		bytesToWrite = (soundOutput.secondaryBufferSize - byteToLock);
		bytesToWrite += targetCursor;
	      }
	      else
	      {
		bytesToWrite = targetCursor - byteToLock;
	      }
	      SDL_UnlockAudio();
	      SDLFillSoundBuffer(&soundOutput, byteToLock, bytesToWrite);
	      
	      SDLUpdateWindow(window, renderer, globalBackBuffer);

	      ++xOffset;
	      //	      yOffset += 2;
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

	// Close game controllers
	SDLCloseGameControllers();
	
	// Shutdown SDL
	SDL_Quit();

	return 0;
}
