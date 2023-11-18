#ifndef WIN32_WINDOW_H
#define WIN32_WINDOW_H

#include "win32_window_data.h"

namespace Sirius
{
  namespace Window
  {
    static void
    win32_initBlitBuffer(Win32_BlitBuffer *buffer, HDC destDC, int width, int height);

    static void
    win32_blit(Win32_BlitBuffer *buffer);

    static void
    win32_getWindowDimensionsInternal(HWND wndHandle, int *width, int *height);

    static void
    win32_getWindowDimensions(Win32_Window *window);

    LRESULT
    win32_windowCallback(HWND window, UINT msg, WPARAM wParam, LPARAM lParam);

    static Win32_Window *
    win32_createWindow(HINSTANCE processInstance, const char *title, int width, int height);
  }
}

#endif // WIN32_WINDOW_H