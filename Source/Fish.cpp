#include "Fish.h"

#define FISH_WIDTH	(71)
#define FISH_HEIGHT	(42)
#define FISH_SRC_WIDTH	(143)
#define FISH_SRC_HEIGHT	(84)
#define MINIMUM_ADJUST_PERIOD	(30)
#define VARIABLE_ADJUST_PERIOD	(70)
#define STEP_Y_FACTOR		(0.05)

void Fish::CreateFish(SDL_Surface* pScreen, SDL_Surface* pFishSprites)
{
   m_pScreen = pScreen;
   m_pFishSprites = pFishSprites;
   m_nFrame = rand()%20;
   m_pCurrentSprite = SDL_CreateRGBSurface(SDL_SWSURFACE, FISH_WIDTH, FISH_HEIGHT, 16, 0, 0, 0, 0); 

   m_dX = rand() % SCREEN_WIDTH;
   m_dY = rand() % SCREEN_HEIGHT;
   m_eOrientation = Left;
   if( rand() % 2 == 0 ) m_eOrientation = Right;

   m_nNextAdjust = rand() % VARIABLE_ADJUST_PERIOD + MINIMUM_ADJUST_PERIOD;
   m_dStepX = 1;//((double)rand()/(double)RAND_MAX) * 3. + 0.5;
   m_dStepY = (((double)rand()/(double)RAND_MAX) - 0.5) * STEP_Y_FACTOR;
   m_nDesiredY = -1;
}

void Fish::FreeFish()
{
   SDL_FreeSurface(m_pCurrentSprite);
}

Uint16 get_pixel16( SDL_Surface *surface, int x, int y ) 
{ 
   int bpp = surface->format->BytesPerPixel;
   Uint8 *p = (Uint8 *)surface->pixels + y * surface->pitch + x * bpp; //Get the requested pixel 
   return *(Uint16 *)p;
} 

void put_pixel16( SDL_Surface *surface, int x, int y, Uint16 pixel ) 
{ 
   int bpp = surface->format->BytesPerPixel;
   Uint8 *p = (Uint8 *)surface->pixels + y * surface->pitch + x * bpp;
   *(Uint16 *)p = pixel;
}

double abs(double d)
{
   return (d < 0.) ? (-d) : d;
}

void Fish::UpdateDisplay()
{
   m_nNextAdjust--;
   if( m_nNextAdjust <= 0 )
   {
      m_nNextAdjust = rand() % VARIABLE_ADJUST_PERIOD + MINIMUM_ADJUST_PERIOD;
      m_dStepY = (((double)rand()/(double)RAND_MAX) - 0.5) * STEP_Y_FACTOR;
   }

   m_dX += (m_eOrientation == Right ? 1 : -1) * m_dStepX;

   if( (m_dX + FISH_WIDTH) < 0 )
   {
      m_eOrientation = Right;
   }
   else if( m_dX > SCREEN_WIDTH )
   {
      m_eOrientation = Left;
   }

   if( m_dY > (SCREEN_HEIGHT - 10/*some amount*/) )
   {
      m_dStepY = -abs(m_dStepY);
      m_nDesiredY = rand() % SCREEN_HEIGHT;
   }
   else if( (m_dY + FISH_HEIGHT) < FISH_HEIGHT/2/*Some amount*/ )
   {
      m_dStepY = abs(m_dStepY);
      m_nDesiredY = rand() % SCREEN_HEIGHT;
   }
   if( m_nDesiredY != -1 )
   {
      if( m_nDesiredY < int(m_dY) )
      {
         m_dY -= 0.5;
      }
      else
      {
         m_dY += 0.5;
      }
      if( int(m_dY) == m_nDesiredY )
         m_nDesiredY = -1;
   }
   else
   {
      m_dY += m_dStepY;
   }

   SDL_Rect rectSrc;
   rectSrc.x = m_nFrame * FISH_SRC_WIDTH;
   rectSrc.y = 0;
   rectSrc.w = FISH_SRC_WIDTH;
   rectSrc.h = FISH_SRC_HEIGHT;

   SDL_Rect rectDst;
   rectDst.x = (int)m_dX;
   rectDst.y = (int)m_dY;
   rectDst.w = FISH_WIDTH;
   rectDst.h = FISH_HEIGHT;

   SDL_SoftStretch(m_pFishSprites, &rectSrc, m_pCurrentSprite, NULL);

   if( m_eOrientation == Right )
      FlipHorizontal(m_pCurrentSprite);

   SDL_SetColorKey(m_pCurrentSprite, SDL_SRCCOLORKEY, SDL_MapRGB(m_pCurrentSprite->format, 255, 255, 255));
   SDL_BlitSurface(m_pCurrentSprite, NULL, m_pScreen, &rectDst);	

   m_nFrame++;
   if( m_nFrame >= 20 )
      m_nFrame = 0;
}

void Fish::FlipHorizontal(SDL_Surface* pSurface)
{
   //If the surface must be locked 
   if( SDL_MUSTLOCK( pSurface ) )
   {
      //Lock the surface 
      SDL_LockSurface( pSurface );
   }

   //Go through columns 
   for( int x = 0; x < pSurface->w/2; x++ )
   {
      //Go through rows 
      for( int y = 0; y < pSurface->h; y++ )                
      {
         //Get pixel 
         Uint16 pixel1 = get_pixel16( pSurface, x, y );
         Uint16 pixel2 = get_pixel16( pSurface, pSurface->w-x, y);

         put_pixel16( pSurface, x, y, pixel2);
         put_pixel16( pSurface, pSurface->w-x, y, pixel1);

      }
   }

   //Unlock surface 
   if( SDL_MUSTLOCK( pSurface ) )
   {
      SDL_UnlockSurface( pSurface );
   }
}



