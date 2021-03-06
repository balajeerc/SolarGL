#pragma once

#include "Util.h"

namespace SolarGL
{
    class Node;
    class Mesh;
    class Shader;
    class Texture;

    class MeshRenderer
    {
    public:
        MeshRenderer();
    
        inline void setNode(Node* node){ _node = node; }
        Node* getNode() const{  return _node; }

        inline void setMesh(Mesh* mesh){ _mesh = mesh; }
        Mesh* getMesh() const{  return _mesh; }

        inline void setTexture(Texture* texture){ _texture = texture; }
        Texture* getTexture() const{  return _texture; }

        inline void setShader(Shader* shader){ _shader = shader; }
        Shader* getShader() const{  return _shader; }

        void renderMesh(const mat4& projectionMatrix,
                        const mat4& viewMatrix);

    protected:
        /// \brief mesh that this renderer will draw
        Mesh* _mesh;

        /// \brief texture to be used to map the mesh with
        Texture* _texture;

        /// \brief shader to be used to render this mesh
        Shader* _shader;

        /// \node node that mesh renderer is bound by
        Node* _node;

    };
}