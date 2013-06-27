#pragma once

#include "Util.h"
#include "Camera.h"
#include "Mesh.h"
#include "Shader.h"
#include "Node.h"
#include "Texture.h"
#include "MeshRenderer.h"


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

    protected:
        static AppManager* _mainInstance;

        Camera _camera;
        Mesh _mesh;
        Shader _shader;
        Texture _texture;
        Node _node;
        MeshRenderer _meshRenderer;

        mat4 _projectionModelView;

        /// brief   Glut annoyingly requires a C function for all its callbacks
        static void OnDisplay();
    };
}
