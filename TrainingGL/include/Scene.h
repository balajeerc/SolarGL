#pragma once

#include "Util.h"
#include "Model.h"
#include "Camera.h"
#include "Shader.h"

namespace SolarGL
{
    /// \brief  Scene management for scenegraph
    /// \detail Holds a collection of models
    class Scene
    {
    public:
        enum LightingMode
        {
            DYNAMIC_LIGHTING=0,
            STATIC_LIGHTING=1,
        };

        /// \brief  Constructor
        Scene();
        
        /// \brief  Destructor
        ~Scene();

        /// \brief  Initialization of scene done here
        void prepare();

        /// \brief  Called repeatedly as part of main loop
        void update(const double& timeElapsed);

        void toggleLightingMode();

    protected:
        /// \brief  All the models managed by scene
        std::map<std::string, Model*> _models;

        /// \brief  Camera used to render scene
        Camera  _camera;

        /// \brief internal timer
        double  _timeAtLastFrame;

        Model* _sun;
        Model* _earth;
        Model* _moon;

        Shader* _shaders[2];
        LightingMode _lightingMode;

    };
}