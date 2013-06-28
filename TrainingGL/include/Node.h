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
        
        void setParent(Node* parent){ _parent = parent; }
        Node* getParent() const{ return _parent; }

        /// \brief  returns the local transform of this node
        const mat4& getLocalTransform() const{  return _transform; }

        /// \brief  sets the local transform of this node
        void setLocalTransform(const mat4& transform){   _transform = transform; }

        void getWorldTransform(mat4& outTransform) const
        {  
            if(_parent)
            {
                mat4 parentTransform;
                _parent->getWorldTransform(parentTransform);
                outTransform = parentTransform*_transform;
            }
            else
            {
                outTransform = _transform;
            }
        }

        /// \brief  Sets location of current transform w.r.t its parent
        void moveTo(const vec3& newPos)
        {
            float* m = _transform.data();
            m[3] = newPos.data()[0];
            m[7] = newPos.data()[1];
            m[11] = newPos.data()[2];
        }

        /// \brief  rotates object about its own axis (i.e. w.r.t its parent)
        /// \detail NOTE: Euler order xyz assumed; rotations in degrees
        void rotate(const vec3& rotation)
        {
            mat4 temp = _transform;
            mat4 rotaMat;
            rotaMat.identity();
            const float degToRadian = (float)PI/180.f;
            matrix_rotation_euler(rotaMat,
                                  rotation.data()[0] * degToRadian,
                                  rotation.data()[1] * degToRadian,
                                  rotation.data()[2] * degToRadian,
                                  cml::euler_order_xyz);
            _transform = rotaMat*temp;
        }

    protected:
        mat4 _transform;

        Node* _parent;
    };
}