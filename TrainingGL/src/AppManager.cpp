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

		glFrontFace(GL_CW);
        glDisable(GL_CULL_FACE);
        glPolygonMode(GL_FRONT_AND_BACK,GL_FILL);
        glColor3f(1.f, 1.f, 1.f);

        _mesh.load();
        _mesh.prepare();

		_shader.setSources("C:\\SolarGL\\data\\shaders\\Default_VS.glsl",
                            "C:\\SolarGL\\data\\shaders\\Default_FS.glsl");
        _shader.prepare();

        _camera.setPerspective(45.f,
                               640.f/480.f,
                               1.f,
                               100.f);

        _camera.lookAt(vec3(0.f,0.f,10.f),  //camera location
                       vec3(0.f,0.f,0.f),   //target location
                       vec3(0.f,1.f,0.f));  //up direction

        //Calculate ProjectionModelView matrix
        _projectionModelView = _camera.getProjectionMatrix()*_camera.getViewMatrix();

        glutDisplayFunc(AppManager::OnDisplay);
        glutMainLoop();
    }

    void AppManager::update()
    {
        //Clear the buffer with black
        glClearColor(0.0, 0.0, 0.0, 1.0);
        glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);

        //Set the shader
        glUseProgram(_shader.getShaderId());
        Util::GLErrorAssert();

        int loc = -1;
        loc = glGetUniformLocation(_shader.getShaderId(), "ProjectionModelViewMatrix");
        glUniformMatrix4fv(loc, 1, GL_FALSE, _projectionModelView.data());
        Util::GLErrorAssert();

        //Specify the vertex coordinates
        int vertexLoc = glGetAttribLocation(_shader.getShaderId(), "InVertex");
        glBindBuffer(GL_ARRAY_BUFFER, _mesh.getVertexBufferId());
        glVertexAttribPointer(vertexLoc,            //attribute
                              3,                    //size
                              GL_FLOAT,             //type
                              GL_FALSE,             //not normalized
                              sizeof(GLfloat)*3,    //stride
                              (void*)0              //array buffer offset
                              );
        glEnableVertexAttribArray(vertexLoc);

        //Bind the index buffer before initiating draw
        glBindBuffer(GL_ELEMENT_ARRAY_BUFFER, _mesh.getElementBufferId());
        Util::GLErrorAssert();

        // Draw 2 triangles using just bound(activated) index array
        glDrawElements(GL_TRIANGLES, 24, GL_UNSIGNED_INT, 0);
        Util::GLErrorAssert();

        //Deactivate array buffers
        glDisableVertexAttribArray(vertexLoc);

        // bind with 0, so, switch back to normal pointer operation
        glBindBuffer(GL_ARRAY_BUFFER, 0);
        glBindBuffer(GL_ELEMENT_ARRAY_BUFFER, 0);
        Util::GLErrorAssert();

        //Swap buffers
        glutSwapBuffers();
    }

    void AppManager::OnDisplay()
    {
        _mainInstance->update();
    }
}
