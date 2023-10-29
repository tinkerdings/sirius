#include <stdint.h>
#include <string.h>

struct BlitBuffer;

namespace Sword
{
  struct Rect
  {
    float x0, y0, x1, y1;
  };

  struct Color
  {
    union
    {
      uint8_t channels[4];
      uint32_t color;

      struct
      {
        uint8_t red, green, blue, alpha;
      };
    };
  };

  static void 
  renderWeirdGradient(BlitBuffer *buffer)
  {
    static int blueOffset = 0;
    static int greenOffset = 0;
    uint8_t *row = (uint8_t *)buffer->memory;
    for(int y = 0; y < buffer->height; y++)
    {
      uint32_t *pixel = (uint32_t *)row;
      for(int x = 0; x < buffer->width; ++x)
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

    for(int y = 0; y < buffer->height; y++)
    {
      uint32_t *pixel = (uint32_t *)row;
      for(int x = 0; x < buffer->width; ++x)
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
    uint8_t *pos = (uint8_t*)buffer->memory + ((buffer->pitch * (int)rect.y0) + ((int)rect.x0 * buffer->bytesPerPixel));
    uint32_t outColor = ((color.alpha << 24) | (color.red << 16) | (color.green << 8) | (color.blue));

    for(int y = 0; y < height; ++y)
    {
      uint32_t *pixel = (uint32_t *)pos;
      for(int x = 0; x < width; ++x)
      {
        *pixel++ = outColor;
      }
      pos += buffer->pitch;
    }
  }
}
