#ifndef WIN32_TIME_DATA_H
#define WIN32_TIME_DATA_H

namespace Sirius
{
  namespace Time
  {
    static LARGE_INTEGER timeLast, timeCurrent;
    static LARGE_INTEGER frequency;
  } // namespace Time
} // namespace Sirius

#endif //WIN32_TIME_DATA_H