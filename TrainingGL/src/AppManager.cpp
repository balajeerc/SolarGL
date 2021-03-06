#include "AppManager.h"

namespace SolarGL
{
    AppManager* AppManager::_mainInstance = NULL;

    AppManager::AppManager()
    {
        if(_mainInstance)
        {
            fprintf(stderr, "Error: %s\n", "An app manager instance already exists! Cannot reinstantiate!");
            exit(1);
        }

       _mainInstance = this;
    }

    AppManager::~AppManager()
    {


    }

    void AppManager::initApplication(int argc, char* argv[])
    {
        glutInit(&argc, argv);

        glutInitDisplayMode(GLUT_RGBA|GLUT_DOUBLE|GLUT_DEPTH);
        glutInitWindowSize(640, 480);

        glutCreateWindow("SolarGL: Solar System");

        //Print some OpenGL information
        printf("Found OpenGL Version: %s\n", glGetString(GL_VERSION));

        //Initialise extension wrangler
        GLenum glew_status = glewInit();
        if (glew_status != GLEW_OK)
        {
          fprintf(stderr, "Error: %s\n", glewGetErrorString(glew_status));
          exit(1);
        }

		glFrontFace(GL_CCW);
        glEnable(GL_DEPTH_TEST);
        //glDisable(GL_CULL_FACE);
        //glPolygonMode(GL_FRONT_AND_BACK,GL_FILL);
        glPolygonMode(GL_FRONT,GL_FILL);
        glColor3f(1.f, 1.f, 1.f);

        _scene.prepare();
        
        glutIdleFunc(AppManager::OnIdle);
        glutDisplayFunc(AppManager::OnDisplay);
        glutKeyboardFunc(AppManager::OnKeyPress);
        glutMainLoop();
    }

    void AppManager::update()
    {
        //Clear the buffer with black
        glClearColor(0.0, 0.0, 0.0, 1.0);
        glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);

        _scene.update(_timer.getTimeElapsed());

        //Swap buffers
        glutSwapBuffers();

        glutPostRedisplay();
    }

    void AppManager::handleKeyPress(unsigned char key, int x, int y)
    {
        if (key == 27)
		    exit(0);
	    else if (key=='l')
            _scene.toggleLightingMode();
    }

    void AppManager::OnDisplay()
    {
        _mainInstance->update();
        
    }

    void AppManager::OnKeyPress(unsigned char key, int x, int y)
    {
        _mainInstance->handleKeyPress(key, x, y);
    }

    void AppManager::OnIdle()
    {
        static int frameCount = 0;

        //  Increase frame count
        frameCount++;
 
        static double currentTime = 0;
        static double previousTime = 0;

        //  Get the number of milliseconds since glutInit called
        //  (or first call to glutGet(GLUT ELAPSED TIME)).
        currentTime = glutGet(GLUT_ELAPSED_TIME);
 
        //  Calculate time passed
        static int timeInterval;
        timeInterval = currentTime - previousTime;
 
        if(timeInterval > 1000)
        {
            //  calculate the number of frames per second
            int fps = frameCount / (timeInterval / 1000.0f);
            printf("FPS:%d\n", fps);

            //  Set time
            previousTime = currentTime;
     
            //  Reset frame count
            frameCount = 0;
        }

        glutPostRedisplay();
    }
}
