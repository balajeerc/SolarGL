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
            
        glutDisplayFunc(AppManager::OnDisplay);
        glutMainLoop();
    }

    void AppManager::update()
    {
        //Clear the buffer with black
        glClearColor(0.0, 0.0, 0.0, 1.0);
        glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);

        _scene.update(0.f);

        //Swap buffers
        glutSwapBuffers();
    }

    void AppManager::OnDisplay()
    {
        _mainInstance->update();
    }
}
