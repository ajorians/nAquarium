#include "FishFactory.h"
#include "FishGraphic.h"

FishFactory::FishFactory(SDL_Surface* pScreen)
   : m_pScreen(pScreen)
{
   m_pFishSprites = nSDL_LoadImage(fishes);

   for(int i=0; i<NUMBER_OF_FISH; i++)
   {
      m_aFish[i] = (Fish*)malloc(sizeof(Fish));
      m_aFish[i]->CreateFish(pScreen, m_pFishSprites);
   }
}

FishFactory::~FishFactory()
{
   for(int i=0; i<NUMBER_OF_FISH; i++)
      m_aFish[i]->FreeFish();
   SDL_FreeSurface(m_pFishSprites);
}

void FishFactory::UpdateDisplay()
{
   for(int i=0; i<NUMBER_OF_FISH; i++)
      m_aFish[i]->UpdateDisplay();
}

