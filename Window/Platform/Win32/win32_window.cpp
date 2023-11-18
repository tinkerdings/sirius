/*
 * sirius
 *
 * Created by Nandromeda.
 * 
 * 2023
 *
 * win32_window.cpp
 * 
 */

#include <stdio.h>
#include <stdint.h>
#include <math.h>

#include "win32_window.h"

namespace Sirius
{
  namespace Window
  {
    static void
    win32_initBlitBuffer(Win32_BlitBuffer *buffer, HDC destDC, int width, int height)
    {
      if(buffer->DIB)
      {
        DeleteObject(buffer->DIB);
      }

      if(!buffer->srcDeviceContext)
      {
        buffer->srcDeviceContext = CreateCompatibleDC(0);
      }

      buffer->width = width;
      buffer->height = height;
      buffer->bytesPerPixel = 4;
      buffer->info.bmiHeader.biSize = sizeof(buffer->info.bmiHeader);
      buffer->info.bmiHeader.biWidth = buffer->width;
      buffer->info.bmiHeader.biHeight = -buffer->height;
      buffer->info.bmiHeader.biPlanes = 1;
      buffer->info.bmiHeader.biBitCount = 32;
      buffer->info.bmiHeader.biCompression = BI_RGB;
      buffer->pitch = width*buffer->bytesPerPixel;

      buffer->DIB = CreateDIBSection(
          buffer->srcDeviceContext,
          &buffer->info,
          DIB_RGB_COLORS,
          &buffer->memory,
          0,0);

      buffer->destDeviceContext = destDC;

      SelectObject(buffer->srcDeviceContext, buffer->DIB);
    }

    static void 
    win32_getWindowDimensionsInternal(HWND wndHandle, int *width, int *height)
    {
      RECT clientRect;
      GetClientRect(wndHandle, &clientRect);
      *width = clientRect.right - clientRect.left;
      *height = clientRect.bottom - clientRect.top;
    }

    static void
    win32_getWindowDimensions(Win32_Window *window)
    {
      RECT clientRect;
      GetClientRect(window->wndHandle, &clientRect);
      window->width = clientRect.right - clientRect.left;
      window->height = clientRect.bottom - clientRect.top;
    }

    LRESULT win32_windowCallback(
        HWND wndHandle,
        UINT msg,
        WPARAM wParam,
        LPARAM lParam)
    {
      Win32_Window *window = (Win32_Window *)GetWindowLongPtr(wndHandle, 0);

      LRESULT result = 0;

      switch(msg)
      {
        case(WM_SIZE):
          {
            if(window)
            {
              win32_getWindowDimensions(window);
              win32_initBlitBuffer(&window->blitBuffer, window->blitBuffer.destDeviceContext, window->width, window->height);
            }
            break;
          }
        case(WM_CLOSE):
          {
            window->quit = true;
            break;
          }
        case(WM_ACTIVATEAPP):
          {
            OutputDebugString("WM_ACTIVATEAPP\n");
            break;
          }
        case(WM_DESTROY):
          {
            window->quit = true;
            break;
          }
        case(WM_QUIT):
          {
            window->quit = true;
            break;
          }
        default:
          {
            return DefWindowProc(wndHandle, msg, wParam, lParam);
            break;
          }
      }

      return result;
    }

    static Win32_Window *
    win32_createWindow(HINSTANCE processInstance, const char *title, int width, int height)
    {
      Win32_Window *window = (Win32_Window *)calloc(1, sizeof(Win32_Window));
      window->width = width;
      window->height = height;
      window->wndClass = {};
      window->wndClass.cbSize = sizeof(WNDCLASSEX);
      window->wndClass.style = CS_OWNDC | CS_HREDRAW | CS_VREDRAW | CS_DBLCLKS;
      window->wndClass.lpfnWndProc = win32_windowCallback;
      window->wndClass.cbClsExtra = 0;
      window->wndClass.cbWndExtra = sizeof(Win32_Window);
      window->wndClass.hInstance = processInstance;
      window->wndClass.hIcon = 0;
      window->wndClass.hCursor = 0;
      window->wndClass.hbrBackground = 0;
      window->wndClass.lpszMenuName = NULL;
      window->wndClass.lpszClassName = "wndClass";
      window->wndClass.hIconSm = 0;
      if(!RegisterClassEx(&window->wndClass))
      {
        printf("Failed to register window class: (%lu)\n", GetLastError());
        return NULL;
      }

      window->wndHandle = CreateWindowEx(
          0, // dwExStyle
          window->wndClass.lpszClassName, // lpClassName
          title, // lpWindowName
          WS_OVERLAPPEDWINDOW | WS_VISIBLE, // dwStyle
          CW_USEDEFAULT, // X
          CW_USEDEFAULT, // Y
          width, // W
          height, // H
          0, // hWndParent
          0, // hMenu
          processInstance, // hInstance
          0 // lpParam
          );
      if(!window->wndHandle)
      {
        printf("Failed to create window: (%lu)\n", GetLastError());
        return NULL;
      }

      window->wndDeviceContext = GetDC(window->wndHandle);
      SetWindowLongPtr(window->wndHandle, 0, (LONG_PTR)window);

      win32_initBlitBuffer(&window->blitBuffer, window->wndDeviceContext, window->width, window->height);

      window->quit = false;

      return window;
    }
  }
} // namespace Sirius