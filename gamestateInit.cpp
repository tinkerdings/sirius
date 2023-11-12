  namespace Sirius
  {
    void
    gamestateInit()
    {
      // initialize other game states
      gamestates[GAMESTATE_PLAY].run = gamestatePlay;
      changeGamestate(GAMESTATE_PLAY);
    }
  }