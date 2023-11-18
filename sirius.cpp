namespace Sirius
{
  void updateAndRender(BlitBuffer buffer)
  {
    Gamestate::gamestates[gamestateTypeCurrent].run();
  }
} // namespace Sirius