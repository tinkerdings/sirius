#ifndef WIN32_WINDOW_DATA_H
#define WIN32_WINDOW_DATA_H

struct BlitBuffer;

namespace Sirius
{
  namespace Window
  {
    struct Win32_BlitBuffer
    {
      HDC srcDeviceContext;
      HDC destDeviceContext;
      HBITMAP DIB;
      BITMAPINFO info;
      int width;
      int height;
      int pitch;
      int bytesPerPixel;
      void *memory;
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
  } // namespace Window
} // namespace Sirius

#endif // WIN32_WINDOW_DATA_H