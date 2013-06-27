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
        //glDisable(GL_CULL_FACE);
        //glPolygonMode(GL_FRONT_AND_BACK,GL_FILL);
        glPolygonMode(GL_FRONT,GL_FILL);
        glColor3f(1.f, 1.f, 1.f);

        //load the mesh    
        _mesh.load("C:\\SolarGL\\data\\meshes\\suzanne_mesh.json");
        _mesh.prepare();

        //Setup the shaders
        _shader.setSources("C:\\SolarGL\\data\\shaders\\PerPixelLighting_VS.glsl",
                            "C:\\SolarGL\\data\\shaders\\PerPixelLighting_FS.glsl");
        _shader.prepare();

        //Setup the camera
        _camera.setPerspective(45.f,
                               640.f/480.f,
                               1.f,
                               100.f);
        _camera.lookAt(vec3(0.f,0.f, 5.f),  //camera location
                       vec3(0.f,0.f,0.f),   //target location
                       vec3(0.f,1.f,0.f));  //up direction

        //Setup texture
        _texture.loadFromFile("C:\\SolarGL\\data\\images\\gray.png");
        _texture.prepare();

        //Setup the mesh renderer
        _meshRenderer.setNode(&_node);
        _meshRenderer.setTexture(&_texture);
        _meshRenderer.setMesh(&_mesh);
        _meshRenderer.setShader(&_shader);

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

        _meshRenderer.renderMesh(_camera.getProjectionMatrix(),
                                 _camera.getViewMatrix());

        //Swap buffers
        glutSwapBuffers();
    }

    void AppManager::OnDisplay()
    {
        _mainInstance->update();
    }
}
