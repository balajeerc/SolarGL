#pragma once

#include "Util.h"

namespace SolarGL
{
    class Mesh
    {
    public:
        /// \brief  Constructor
        Mesh();

        /// \brief  Destructor
        ~Mesh();

        /// \brief  Loads mesh data
        void load();

        /// \brief  Prepares the mesh
        /// \detail This sets up/prepares the vertex buffers
        void prepare();

        /// \brief  Renders out this mesh
        void render(const mat4& viewMatrix,
                    const mat4& projectionMatrix);

        inline GLuint& getVertexBufferId(){ return _vertexBufferId; }
        inline GLuint& getElementBufferId(){ return _elementBufferId; }

    protected:
		
        std::vector<GLfloat> _vertices;
        std::vector<GLuint> _faceIndices;
        std::vector<vec2> _texCoords;

        GLuint _vertexBufferId;
        GLuint _elementBufferId;
    };
}
