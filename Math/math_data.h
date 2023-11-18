#ifndef MATH_DATA_H
#define MATH_DATA_H

namespace Sirius
{
  namespace Math
  {
    struct Rect
    {
      float x0, y0, x1, y1;
    };

    struct IVec2
    {
      union
      {
        int coord[2];
        struct
        {
          int x, y;
        };
      };
    };

    struct FVec2
    {
      union
      {
        float coord[2];
        struct
        {
          float x, y;
        };
      };
    };
  } // namespace Math
} // namespace Sirius

#endif // MATH_DATA_H