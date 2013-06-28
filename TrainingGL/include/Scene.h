#pragma once

#include "Util.h"
#include "Model.h"
#include "Camera.h"

namespace SolarGL
{
    /// \brief  Scene management for scenegraph
    /// \detail Holds a collection of models
    class Scene
    {
    public:
        /// \brief  Constructor
        Scene();
        
        /// \brief  Destructor
        ~Scene();

        /// \brief  Initialization of scene done here
        void prepare();

        /// \brief  Called repeatedly as part of main loop
        void update(const double& timeElapsed);

    protected:
        /// \brief  All the models managed by scene
        std::map<std::string, Model*> _models;

        /// \brief  Camera used to render scene
        Camera  _camera;
    };
}