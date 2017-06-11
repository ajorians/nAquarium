#include "Aquarium.h"
#include "Background.h"

Aquarium::Aquarium(SDL_Surface* pScreen)
   : m_pScreen(pScreen), m_FishFactory(pScreen), m_nTickEvent(0)
{
   m_pBackground = nSDL_LoadImage(background);
}

Aquarium::~Aquarium()
{
   SDL_FreeSurface(m_pBackground);
}

bool Aquarium::Loop()
{
   //Handle keypresses
   if( PollEvents() == false )
      return false;

   UpdateDisplay();

   return true;
}

bool Aquarium::PollEvents()
{
   SDL_Event event;

   /* Poll for events. SDL_PollEvent() returns 0 when there are no  */
   /* more events on the event queue, our while loop will exit when */
   /* that occurs.                                                  */
   while( SDL_PollEvent( &event ) )
   {
      /* We are only worried about SDL_KEYDOWN and SDL_KEYUP events */
      switch( event.type )
      {
      case SDL_KEYDOWN:
         printf( "Key press detected\n" );
         switch (event.key.keysym.sym) 
         {
         case SDLK_ESCAPE:
            fprintf(stderr, "Hit Escape!n");
            return false;
            break;

         default:
            break;
         }
         break;

         //Called when the mouse moves
      case SDL_MOUSEMOTION:
         break;

      case SDL_KEYUP:
         printf( "Key release detected\n" );
         break;

      default:
         break;
      }
   }
   return true;
}

void Aquarium::UpdateDisplay()
{
   Uint32 tick = SDL_GetTicks();
   if( tick > (m_nTickEvent + 50) )
   {
      m_nTickEvent = tick;
   }
   else
   {
      return;
   }

   SDL_BlitSurface(m_pBackground, NULL, m_pScreen, NULL);

   //Update fish
   m_FishFactory.UpdateDisplay();

   SDL_UpdateRect(m_pScreen, 0, 0, SCREEN_WIDTH, SCREEN_HEIGHT);
}



