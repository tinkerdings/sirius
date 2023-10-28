#include <windows.h>

int APIENTRY WinMain(
    HINSTANCE instance,
    HINSTANCE prevInstance,
    LPSTR cmdArgs,
    int showCmd)
{
  MessageBoxA(NULL, "Hello, world", "Perlin", 0);
  return 0;
}
