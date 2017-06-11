#ifndef FISHFACTORY_H
#define FISHFACTORY_H

#include "Fish.h"

#define NUMBER_OF_FISH	3

extern "C"
{
#include <os.h>
#include "SDL/SDL.h"
}

class FishFactory
{
public:
   FishFactory(SDL_Surface* pScreen);
   ~FishFactory();

   void UpdateDisplay();

protected:
   SDL_Surface	*m_pScreen;//Does not own
   SDL_Surface	*m_pFishSprites;
   Fish		*m_aFish[NUMBER_OF_FISH];
};

#endif
