#pragma once

#include "Util.h"

namespace SolarGL
{
    /// \brief  Class that implements a virtual camera functionality
    /// \detail Essentially, it handles projection and view matrix manipulations
    class Camera
    {
    public:
        /// \brief  Sets camera projection matrix given typical camera params
        void setPerspective(const float& fovy,
                            const float& aspect,
                            const float& zNear,
                            const float& zFar);

        /// \brief  Sets camera lookat matrix given typical camera params
        void lookAt(const vec3&  eye,
                    const vec3& center,
                    const vec3& up);

        /// \brief  Returns the camera's projection matrix
        const mat4& getProjectionMatrix() const{ return _projectionMatrix; }

        /// \brief  Returns the camera's view matrix
        const mat4& getViewMatrix() const{ return _viewMatrix; }

    protected:
        mat4 _viewMatrix;
        mat4 _projectionMatrix;
    };
}
