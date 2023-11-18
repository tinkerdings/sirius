#ifndef GAMESTATE_DATA_H
#define GAMESTATE_DATA_H

namespace Sirius
{
  namespace Gamestate
  {
    enum GamestateType
    {
      GAMESTATE_INIT,
      GAMESTATE_PLAY,
      _GAMESTATE_N
    };

    struct Gamestate
    {
      void (*pre)();
      void (*run)();
      void (*post)();
    };

    static GamestateType gamestateTypeCurrent;
    static Gamestate gamestates[_GAMESTATE_N];
  } // namespace Gamestate
} // namespace Sirius

#endif // GAMESTATE_DATA_H