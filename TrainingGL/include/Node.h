#pragma once

#include "Util.h"

namespace SolarGL
{
    /// \brief  A node is a container of one transform and several components
    class Node
    {
    public:
        /// \brief  Constructor
        Node();
        
        /// \brief  returns the local transform of this node
        const mat4& getLocalTransform() const{  return _transform; }

        /// \brief  sets the local transform of this node
        void setLocalTransform(const mat4& transform){   _transform = transform; }

    protected:
        mat4 _transform;
    };
}