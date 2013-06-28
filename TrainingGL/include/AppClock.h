#pragma once
#include "Util.h"

namespace SolarGL
{
    class AppClock
    {
    public:
        AppClock()
        {
            _y2k.tm_hour = 0;
            _y2k.tm_min = 0;
            _y2k.tm_sec = 0;
            _y2k.tm_year = 110;
            _y2k.tm_mon = 0;
            _y2k.tm_mday = 1;
        }

        const double& getTimeElapsed()
        {
            //time(&_timer);  /* get current time; same as: timer = time(NULL)  */
            //_seconds = difftime(_timer,mktime(&_y2k));
            //return _seconds;
           
            _seconds = glutGet(GLUT_ELAPSED_TIME)*0.001;
            return _seconds;
        }
        
    protected:
            time_t _timer;
            struct tm _y2k;
            double _seconds;

    };
}