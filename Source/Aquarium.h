#ifndef AQUARIUM_H
#define AQUARIUM_H

extern "C"
{
#include <os.h>
#include "SDL/SDL.h"
}

#include "FishFactory.h"

class Aquarium
{
public:
   Aquarium(SDL_Surface* pScreen);
   ~Aquarium();

   bool Loop();

protected:
   bool PollEvents();
   void UpdateDisplay();

protected:
   SDL_Surface	*m_pScreen;//Does not own
   SDL_Surface	*m_pBackground;
   FishFactory	m_FishFactory;
   Uint32		m_nTickEvent;
};

#endif
