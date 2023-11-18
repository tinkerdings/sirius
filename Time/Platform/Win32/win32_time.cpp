#include "win32_time.h"

namespace Sirius
{
  namespace Time
  {
    void 
    init()
    {
      QueryPerformanceCounter(&timeLast);
      QueryPerformanceFrequency(&frequency);
    }

    inline int64_t
    getDifference()
    {
      QueryPerformanceCounter(&timeCurrent);
      int64_t difference = timeCurrent.QuadPart - timeLast.QuadPart;
      timeLast = timeCurrent;
      return difference;
    }

    inline int64_t 
    getElapsed_s()
    {
      int64_t difference = getDifference();
      return difference / frequency.QuadPart;
    }

    inline int64_t 
    getElapsed_ms()
    {
      int64_t difference = getDifference();
      return (1000 * difference) / frequency.QuadPart;
    }

    inline int64_t 
    getElapsed_us()
    {
      int64_t difference = getDifference();
      return (1000000 * difference) / frequency.QuadPart;
    }

    void printElapsed(const char *timeUnitString, int64_t (*timeElapsedFunction)())
    {
      int64_t timeElapsed = timeElapsedFunction();
      char buffer[256] = {};
      wsprintf(buffer, "time elapsed (%s): %d\n", timeUnitString, timeElapsed);
      OutputDebugStringA(buffer);
    }
  } // namespace Time
} // namespace Sirius
