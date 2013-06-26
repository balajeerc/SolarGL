#include "Camera.h"

namespace SolarGL
{
    void Camera::setPerspective(const float& fovy,
                                const float& aspect,
                                const float& zNear,
                                const float& zFar)
    {
        cml::matrix_perspective_yfov(_projectionMatrix,		//Projection matrix to set
                                     fovy,					//Vertical field of view
                                     aspect,				//Aspect ratio
                                     zNear,					//Near plane
                                     zFar,					//Far plane	
                                     cml::right_handed,		//Handedness
                                     cml::z_clip_neg_one		//Near z-clipping range for the canonical view volume
                                    );	
    }

    void Camera::lookAt(const vec3&  eye,
                        const vec3& center,
                        const vec3& up)
    {
        cml::matrix_look_at_RH(_viewMatrix,
                               eye,
                               center,
                               up);
    }
}
