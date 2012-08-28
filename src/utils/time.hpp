//
//  SuperTuxKart - a fun racing game with go-kart
//  Copyright (C) 2004 Steve Baker <sjbaker1@airmail.net>
//
//  This program is free software; you can redistribute it and/or
//  modify it under the terms of the GNU General Public License
//  as published by the Free Software Foundation; either version 3
//  of the License, or (at your option) any later version.
//
//  This program is distributed in the hope that it will be useful,
//  but WITHOUT ANY WARRANTY; without even the implied warranty of
//  MERCHANTABILITY or FITNESS FOR A PARTICULAR PURPOSE.  See the
//  GNU General Public License for more details.
//
//  You should have received a copy of the GNU General Public License
//  along with this program; if not, write to the Free Software
//  Foundation, Inc., 59 Temple Place - Suite 330, Boston, MA  02111-1307, USA.

#ifndef HEADER_TIME_HPP
#define HEADER_TIME_HPP
#include <stdexcept>

#ifdef WIN32
#  define _WINSOCKAPI_
#  include <windows.h>
#  include <time.h>
#else
#  include <stdint.h>
#  include <sys/time.h>
#endif

#include <string>

class Time
{
public:
    typedef time_t TimeType;

    /** Converts the time in this object to a human readable string. */
    static std::string toString(const TimeType &tt)
    {
        const struct tm *t = gmtime(&tt);
        char s[16];
        strftime(s, 16, "%x", t);
        return s;
    }   // toString
    // ------------------------------------------------------------------------
    /** In integer seconds  */
    static TimeType getTimeSinceEpoch()
    {
#ifdef WIN32
        FILETIME ft;
        GetSystemTimeAsFileTime(&ft);
        __int64 t = ft.dwHighDateTime;
        t <<= 32;
        t /= 10;
        // The Unix epoch starts on Jan 1 1970.  Need to subtract 
        // the difference in seconds from Jan 1 1601.
#       if defined(_MSC_VER) || defined(_MSC_EXTENSIONS)
#           define DELTA_EPOCH_IN_MICROSECS  11644473600000000Ui64
#       else
#           define DELTA_EPOCH_IN_MICROSECS  11644473600000000ULL
#       endif
        t -= DELTA_EPOCH_IN_MICROSECS;
 
        t |= ft.dwLowDateTime;
        // Convert to seconds since epoch
        t /= 1000000UL;
        return t;
#else
        struct timeval tv;
        if (gettimeofday(&tv, NULL) != 0)
        {
            throw std::runtime_error("gettimeofday failed");
        }
        return tv.tv_sec;
#endif
    };   // getTimeSinceEpoch
    // ------------------------------------------------------------------------
    /** In floating point seconds  */
    static float getFloatTimeSinceEpoch(long startAt=0)
    {
#ifdef WIN32
        FILETIME ft;
        GetSystemTimeAsFileTime(&ft);
        __int64 t = ft.dwHighDateTime;
        t <<= 32;
        t /= 10;
        // The Unix epoch starts on Jan 1 1970.  Need to subtract 
        // the difference in seconds from Jan 1 1601.
#       if defined(_MSC_VER) || defined(_MSC_EXTENSIONS)
#           define DELTA_EPOCH_IN_MICROSECS  11644473600000000Ui64
#       else
#           define DELTA_EPOCH_IN_MICROSECS  11644473600000000ULL
#       endif
        t -= DELTA_EPOCH_IN_MICROSECS;
        
        t |= ft.dwLowDateTime;
        // Convert to seconds since epoch
        float f = (float)(double(t) / 1000000.0);
        return f;
#else
        struct timeval tv;
        gettimeofday(&tv, NULL);
        int millis = (tv.tv_sec - startAt)*1000 + tv.tv_usec/1000;
        return (float)(millis/1000.0);
#endif
    };   // getTimeSinceEpoch
    
    class ScopeProfiler
    {
        float m_time;
    public:
        ScopeProfiler(const char* name)
        {
            printf("%s {\n", name);
            // 1325966438 is an arbitrary time that is in the past but much after 1970
            // to get smaller numbers in order to not lose the precision of float
            m_time = getFloatTimeSinceEpoch(1325966438);
        }
        
        ~ScopeProfiler()
        {
            float f2 = getFloatTimeSinceEpoch(1325966438);
            printf("} // took %f s\n", (f2 - m_time));
        }
    };
    
};   // namespace time
#endif

