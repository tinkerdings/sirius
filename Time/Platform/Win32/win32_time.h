#ifndef WIN32_TIME_H
#define WIN32_TIME_H

#include "win32_time_data.h"

namespace Sirius
{
  namespace Time
  {
    void
    init();

    inline int64_t
    getDifference();

    inline int64_t
    getElapsed_s();

    inline int64_t
    getElapsed_s();

    inline int64_t
    getElapsed_us();

    void printElapsed(const char *timeUnitString, int64_t (*timeElapsedFunction)());
  } // namespace Time
} // namespace Sirius

#endif // WIN32_TIME_H