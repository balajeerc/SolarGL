#pragma once

#include "Util.h"
#include "Scene.h"
#include "AppClock.h"

namespace SolarGL
{
    //  \brief  Class that starts and handles main thread of app
    //  \detail Control center of this application
    class AppManager
    {
    public:
        /// \brief  Constructor
        AppManager();

        /// \brief  Destructor
        ~AppManager();

        /// \brief  Starts application thread
        void initApplication(int argc, char* argv[]);

        /// \brief  Main loop for the application
        void update();

        /// \brief  Returns a pointer to the timer
        AppClock& getTimer(){ return _timer; }

    protected:
        static AppManager* _mainInstance;

        Scene _scene;

        AppClock _timer;

        /// brief   Glut annoyingly requires a C function for all its callbacks
        static void OnDisplay();

        static void OnIdle();
    };
}
