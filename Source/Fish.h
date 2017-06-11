#ifndef FISH_H
#define FISH_H

extern "C"
{
#include <os.h>
#include "SDL/SDL.h"
}

class Fish
{
public:
   void CreateFish(SDL_Surface* pScreen, SDL_Surface* pFishSprites);
   void FreeFish();
   void UpdateDisplay();

protected:
   static void FlipHorizontal(SDL_Surface* pSurface);

protected:
   SDL_Surface	*m_pScreen;//Does not own
   SDL_Surface	*m_pFishSprites;//Does not own
   SDL_Surface	*m_pCurrentSprite;
   int 		m_nFrame;

   double		m_dX;
   double		m_dY;
   enum{Left, Right} m_eOrientation;

   int		m_nNextAdjust;
   double		m_dStepX;
   double		m_dStepY;
   int			m_nDesiredY;
};

#endif
