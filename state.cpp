namespace Sirius
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

  GamestateType gamestateTypeCurrent;
  Gamestate gamestates[_GAMESTATE_N];

  void 
  changeGamestate(GamestateType gamestateType);

  // declare gamestate functions here
  void
  gamestateInit();
  void
  gamestatePlay();

  void 
  changeGamestate(GamestateType gamestateType)
  {
    if(gamestates[gamestateTypeCurrent].post)
    {
      gamestates[gamestateTypeCurrent].post();
    }

    gamestateTypeCurrent = gamestateType;

    if(gamestates[gamestateTypeCurrent].pre)
    {
      gamestates[gamestateTypeCurrent].pre();
    }
  }
} // namespace Sirius

// include gamestate function files here
#include "gamestateInit.cpp"
#include "gamestatePlay.cpp"