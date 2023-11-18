#ifndef RENDERING_DATA_H
#define RENDERING_DATA_H

namespace Sirius
{
  namespace Rendering
  {
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

    struct BlitBuffer
    {
      void *memory;
      int width;
      int height;
      int pitch;
      int bytesPerPixel;
    };
  } // namespace Rendering
} // namespace Sirius

#endif // RENDERING_DATA_H