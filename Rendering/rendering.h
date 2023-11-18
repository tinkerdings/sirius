#ifndef RENDERING_H
#define RENDERING_H

#include "rendering_data.h"

namespace Sirius
{
  namespace Rendering
  {
    static void
    renderClear(BlitBuffer *buffer, uint8_t red, uint8_t green, uint8_t blue, uint8_t alpha);

    static void
    renderWeirdGradient(BlitBuffer *buffer);

    static void
    renderFilledSquare(BlitBuffer *buffer, Rect rect, Color color);

    static inline void
    renderPixel(BlitBuffer *buffer, int x, int y, Color color);
  } // namespace Rendering
} // namespace Sirius

#endif // RENDERING_H