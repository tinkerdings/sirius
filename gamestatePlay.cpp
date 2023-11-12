namespace Sirius
{
  void
  gamestatePlay()
  {
    renderClear(commonGameData.blitBuffer, 255, 0, 0, 255);
    renderWeirdGradient(commonGameData.blitBuffer);

    Rect square = {100, 100, 200, 200};
    Color squareColor = {255, 255, 0, 255};
    Rect square2 = {300, 300, 400, 400};
    Color squareColor2 = {0, 255, 255, 255};
    renderFilledSquare(commonGameData.blitBuffer, square, squareColor);
    renderFilledSquare(commonGameData.blitBuffer, square2, squareColor2);
  }
}