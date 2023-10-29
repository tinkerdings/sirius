/*
 * SWORD - SoftWare Only Renderer Deluxe.
 *
 * Created by Nandromeda.
 * 
 * 2023
 *
 * win32_window.cpp
 * 
 */

#include <windows.h>
#include <stdio.h>
#include <stdint.h>
#include <math.h>

namespace Sword
{
  struct Win32_BlitBuffer;
  struct Win32_Window;

  static void
    win32_initBlitBuffer(Win32_BlitBuffer *buffer, HDC destDC, int width, int height);

  static void
    win32_clearBuffer(Win32_BlitBuffer *buffer);

  static void 
    win32_blit(Win32_BlitBuffer *buffer);

  static void
    win32_getWindowDimensionsInternal(HWND wndHandle, int *width, int *height);

  static void
    win32_getWindowDimensions(Win32_Window *window);

  LRESULT 
    win32_wndCallback(HWND window, UINT msg, WPARAM wParam, LPARAM lParam);

  static Win32_Window *
    win32_createWindow(HINSTANCE processInstance, const char *title, int width, int height);

  struct Win32_BlitBuffer
  {
    HDC srcDeviceContext;
    HDC destDeviceContext;
    HBITMAP DIB;
    BITMAPINFO info;
    BlitBuffer buffer;
  };

  struct Win32_Window
  {
    WNDCLASSEX wndClass;
    HWND wndHandle;
    HDC wndDeviceContext;
    int width;
    int height;
    bool quit;
    Win32_BlitBuffer blitBuffer;
  };

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

    buffer->buffer.width = width;
    buffer->buffer.height = height;
    buffer->buffer.bytesPerPixel = 4;
    buffer->info.bmiHeader.biSize = sizeof(buffer->info.bmiHeader);
    buffer->info.bmiHeader.biWidth = buffer->buffer.width;
    buffer->info.bmiHeader.biHeight = -buffer->buffer.height;
    buffer->info.bmiHeader.biPlanes = 1;
    buffer->info.bmiHeader.biBitCount = 32;
    buffer->info.bmiHeader.biCompression = BI_RGB;
    buffer->buffer.pitch = width*buffer->buffer.bytesPerPixel;

    buffer->DIB = CreateDIBSection(
        buffer->srcDeviceContext,
        &buffer->info,
        DIB_RGB_COLORS,
        &buffer->buffer.memory,
        0,0);

    buffer->destDeviceContext = destDC;

    SelectObject(buffer->srcDeviceContext, buffer->DIB);
  }

  static void
  win32_clearBuffer(Win32_BlitBuffer *buffer)
  {
    BitBlt(
        buffer->destDeviceContext,
        0, 0,
        buffer->buffer.width, buffer->buffer.height,
        buffer->srcDeviceContext,
        0, 0,
        BLACKNESS
        );
  }

  static void 
  win32_blit(Win32_BlitBuffer *buffer)
  {
    BitBlt(
        buffer->destDeviceContext,
        0, 0,
        buffer->buffer.width, buffer->buffer.height,
        buffer->srcDeviceContext,
        0, 0,
        SRCCOPY
        );
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

  LRESULT wndCallback(
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
    window->wndClass.lpfnWndProc = wndCallback;
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


  static void
  win32_run(Win32_Window *window)
  {

    float squareWidth = 80.0;
    float squareHeight = 80.0;
    float radius = window->height / 4;
    float t = 0.0;
    float squareX = radius * cosf(t) + (((float)window->width / 2.0) - (squareWidth / 2.0));
    float squareY = radius * sinf(t) + (((float)window->height / 2.0) - (squareHeight / 2.0));
    Rect square = {squareX, squareY, squareX + squareWidth, squareY + squareHeight};
    Color squareColor = {255, 64, 64, 255};

    LARGE_INTEGER timestampLast;
    QueryPerformanceCounter(&timestampLast);
    LARGE_INTEGER timeFreq;
    QueryPerformanceFrequency(&timeFreq);

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

      renderClear(&window->blitBuffer.buffer, 0, 0, 255, 30);
      renderWeirdGradient(&window->blitBuffer.buffer);
      renderFilledSquare(&window->blitBuffer.buffer, square, squareColor);
      win32_blit(&window->blitBuffer);

      t -= 0.01;
      square.x0 = radius * cosf(t) + (((float)window->width / 2.0) - (squareWidth / 2.0));
      square.y0 = radius * sinf(t) + (((float)window->height / 2.0) - (squareHeight / 2.0));
      square.x1 = square.x0 + squareWidth;
      square.y1 = square.y0 + squareHeight;
      radius = window->height / 4;

      LARGE_INTEGER timestampNow;
      QueryPerformanceCounter(&timestampNow);
      int64_t msPerFrame = (1000 * (timestampNow.QuadPart - timestampLast.QuadPart)) / timeFreq.QuadPart;
      char buffer[256] = {};
      wsprintf(buffer, "ms: %d\n", msPerFrame);
      OutputDebugStringA(buffer);

      timestampLast = timestampNow;
    }
  }
}

