#include <stdint.h>
#include <windows.h>

#include "Time/Platform/Win32/win32_time.cpp"
#include "Window/Platform/Win32/win32_window.cpp"
#include "Gamestate/gamestate.cpp"

int 
CALLBACK WinMain(
    HINSTANCE instance,
    HINSTANCE prevInstance,
    LPSTR cmdArgs,
    int showCmd)
{
  Sirius::Time::init();
  Sirius::Window::Win32_Window *window = Sirius::Window::win32_createWindow(instance, "Sirius", 800, 600);
  Sirius::Gamestate::gamestates[GAMESTATE_INIT].run = gamestateInit;

  while(!window->quit)
  {
    MSG message;
    while(PeekMessageA(&message, 0, 0, 0, PM_REMOVE))
    {
      if(message.message == WM_QUIT)
      {
        window->quit = true;
        PostQuitMessage(0);
      }
      TranslateMessage(&message);
      DispatchMessage(&message);
    }

    Sirius::updateAndRender(&window->blitBuffer.buffer);
    Sirius::Window::win32_blit(&window->blitBuffer);
  }

  return 0;
}