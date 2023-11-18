#ifndef GAMESTATE_H
#define GAMESTATE_H

#include "gamestate_data.h"

namespace Sirius
{
  namespace Gamestate
  {
    void 
    changeGamestate(GamestateType gamestateType);
    void
    gamestateInit();
    void
    gamestatePlay();
  } // namespace Gamestate
} // namespace Sirius

#endif // GAMESTATE_H