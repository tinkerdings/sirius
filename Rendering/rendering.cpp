#include <stdint.h>

#include "rendering.h"

namespace Sirius
{
  namespace Rendering
  {
    static void
    renderWeirdGradient(BlitBuffer *buffer)
    {
      static int blueOffset = 0;
      static int greenOffset = 0;
      uint8_t *row = (uint8_t *)buffer->memory;
      for (int y = 0; y < buffer->height; y++)
      {
        uint32_t *pixel = (uint32_t *)row;
        for (int x = 0; x < buffer->width; ++x)
        {
          uint8_t blue = x + blueOffset;
          uint8_t green = y + greenOffset;
          uint8_t red = x * y;

          *pixel++ = ((green << 8) | blue);
        }
        row += buffer->pitch;
      }
      blueOffset++;
      greenOffset++;
    }

    static void
    renderClear(BlitBuffer *buffer, uint8_t red, uint8_t green, uint8_t blue, uint8_t alpha)
    {
      uint8_t *row = (uint8_t *)buffer->memory;

      uint32_t color = ((alpha << 24) | (red << 16) | (green << 8) | (blue));

      for (int y = 0; y < buffer->height; y++)
      {
        uint32_t *pixel = (uint32_t *)row;
        for (int x = 0; x < buffer->width; ++x)
        {
          *pixel++ = color;
        }
        row += buffer->pitch;
      }
    }

    static void
    renderFilledSquare(BlitBuffer *buffer, Rect rect, Color color)
    {
      int width = rect.x1 - rect.x0;
      int height = rect.y1 - rect.y0;
      uint8_t *pos = (uint8_t *)buffer->memory + ((buffer->pitch * (int)rect.y0) + ((int)rect.x0 * buffer->bytesPerPixel));
      uint32_t outColor = ((color.alpha << 24) | (color.red << 16) | (color.green << 8) | (color.blue));

      for (int y = 0; y < height; ++y)
      {
        uint32_t *pixel = (uint32_t *)pos;
        for (int x = 0; x < width; ++x)
        {
          *pixel++ = outColor;
        }
        pos += buffer->pitch;
      }
    }

    static inline void
    renderPixel(BlitBuffer *buffer, int x, int y, Color color)
    {
      uint8_t *pos = (uint8_t *)buffer->memory + ((buffer->pitch * y) + (x * buffer->bytesPerPixel));

      uint32_t outColor = ((color.alpha << 24) | (color.red << 16) | (color.green << 8) | (color.blue));

      uint32_t *pixel = (uint32_t *)pos;
      *pixel = outColor;
    }

    static void
    renderLine(BlitBuffer *buffer, int x0, int y0, int x1, int y1, Color color)
    {
      // y = mx + b
      //
      // m = dy/dx
      // dy = (y1 - y0)
      // dx = (x1 - x0)
      //
      // y = (dy/dx)x + b
      // (dx)y = (dy)x + (dx)b
      // 0 = (dy)x - (dx)y + (dx)b
      // 0 = Ax + By + C
      // A = dy
      // B = -dx
      // C = (dx)b
      //
      // 0 = (y1 - y0)x - (x1 - x0)y + (x1 - x0)b
      //
      // y = mx + b
      // b = y - mx
      // set x and y to x0 and y0 and solve b
      // b = y0 - ((y1 - y0)/(x1 - x0))x0
      // b = y0 - (x0y1 - x0y0)/(x1 - x0)
      // b = (x1y0-x0y0)-(x0y1-x0y0)
      // b = x1y0-x0y0-x0y1-x0y0
      // b = y0(x1-x0-x0)-x0y1
      // b = y0(x1-2x0)-x0y1

      int sy = y0;

      int dx = x1 - x0;
      int dy = y1 - y0;
      int b = (y0 * (x1 - x0 - x0)) - (x0 * y1);
      renderPixel(buffer, x0, y0, color);
      /* for(int sx = x0; sx <= x1; ++sx) */
      /* { */
      /*   if(dy * sx - dx * (sy + 0. */
      /* } */
    }
  } // namespace Rendering
} // namespace Sirius
