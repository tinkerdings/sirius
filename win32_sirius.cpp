/*
 * sirius - cross platform software rendering game framework
 *
 * Created by Nandromeda.
 * 
 * 2023
 *
 * win32_sirius.cpp
 * 
 */

#include <stdint.h>

#include "blitBuffer.h"
#include "commonGameData.h"
#include "rendering.cpp"
#include "state.cpp"
#include "sirius.cpp"
#include "win32_window.cpp"

int 
CALLBACK WinMain(
    HINSTANCE instance,
    HINSTANCE prevInstance,
    LPSTR cmdArgs,
    int showCmd)
{
  Sirius::Win32_Window *window = Sirius::win32_createWindow(instance, "Sirius", 800, 600);
  Sirius::win32_run(window);

  return 0;
}

