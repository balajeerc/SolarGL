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
        void load(const char* filename);

        /// \brief  Prepares the mesh
        /// \detail This sets up/prepares the vertex buffers
        void prepare();

        /// \brief  Renders out this mesh
        void render(const mat4& viewMatrix,
                    const mat4& projectionMatrix);

        inline GLuint& getVertexBufferId(){ return _vertexBufferId; }
        inline GLuint& getNormalBufferId(){ return _normalBufferId; }
        inline GLuint& getElementBufferId(){ return _elementBufferId; }
        inline GLuint& getTexCoordsBufferId(){ return _texCoordsBufferId; }

        inline int getNumVertices() const{ return _vertices.size(); }
        inline int getNumFaceIndices() const{ return _faceIndices.size(); }
        inline int getNumTexCoords() const{ return _texCoords.size(); }

    protected:
		void generateVertexNormals(const float& smoothingAngle);

        std::vector<GLfloat> _vertices;
        std::vector<GLfloat> _texCoords;
        std::vector<GLfloat> _normals;   
        std::vector<GLuint> _faceIndices;

        GLuint _vertexBufferId;
        GLuint _normalBufferId;
        GLuint _elementBufferId;
        GLuint _texCoordsBufferId;
    };
}
