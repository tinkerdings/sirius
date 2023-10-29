/*
 * SWORD - SoftWare Only Renderer Deluxe.
 *
 * Created by Nandromeda.
 * 
 * 2023
 *
 * win32_sword.cpp
 * 
 */

#include <stdint.h>

#include "blitBuffer.h"
#include "rendering.cpp"
#include "win32_window.cpp"

int CALLBACK WinMain(
    HINSTANCE instance,
    HINSTANCE prevInstance,
    LPSTR cmdArgs,
    int showCmd)
{
  Sword::Win32_Window *window = Sword::win32_createWindow(instance, "SWORD", 800, 600);
  Sword::win32_run(window);

  return 0;
}

