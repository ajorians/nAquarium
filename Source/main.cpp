extern "C"
{
#include <os.h>
#include "SDL/SDL.h"
}

#include "Aquarium.h"

#define SCREEN_BIT_DEPTH        (16)
#define SCREEN_VIDEO_MODE (SDL_SWSURFACE|SDL_FULLSCREEN|SDL_HWPALETTE)

int main(int argc, char *argv[]) 
{
   printf("Initializing SDL.\n");

   /* Initialize the SDL library (starts the event loop) */
   if ( SDL_Init(SDL_INIT_VIDEO ) < 0 )
   {
      fprintf(stderr,
         "Couldn't initialize SDL: %s\n", SDL_GetError());
      exit(1);
   }

   printf("SDL initialized.\n");

   SDL_Surface* pScreen = NULL;
   pScreen = SDL_SetVideoMode(SCREEN_WIDTH, SCREEN_HEIGHT, SCREEN_BIT_DEPTH, SCREEN_VIDEO_MODE);

   if( pScreen == NULL )
   {
      fprintf(stderr, "Couldn't set %dx%dx%d video mode: %s\n", SCREEN_WIDTH, SCREEN_HEIGHT, SCREEN_BIT_DEPTH, SDL_GetError());
      exit(1);
   }
   else
   {
      /* Hides the cursor */
      SDL_ShowCursor(SDL_DISABLE);

      while(true)
      {
         Aquarium m(pScreen);
         while(m.Loop()){}
         break;
      }

   }

   SDL_FreeSurface(pScreen);

   printf("Quitting SDL.\n");

   /* Shutdown all subsystems */
   SDL_Quit();

   printf("Quitting...\n");

   return 0;
}
