#include "Mesh.h"
#include "Shader.h"
#include "Texture.h"
#include "Node.h"

#include "MeshRenderer.h"

namespace SolarGL
{
    MeshRenderer::MeshRenderer():
    _mesh(NULL),
    _texture(NULL),
    _shader(NULL),
    _node(NULL)
    {
    }

    void MeshRenderer::renderMesh(const mat4& projectionMatrix,
                                  const mat4& viewMatrix)
    {
        if((!_mesh) || (!_texture) || (!_shader) || (!_node))
        {
            //Skip render
            return;
        }

        //Set the shader
        glUseProgram(_shader->getShaderId());
        Util::GLErrorAssert();

        //Start by passing the transformation matrix to the shader
        //Set the modelview projection matrix's uniform by multiplying
        //the current modelview matrix with the transform of this renderable itself
        int matrixLoc = glGetUniformLocation(_shader->getShaderId(), "ProjectionModelViewMatrix");
        mat4 currModelViewProjectionMatrix = projectionMatrix*viewMatrix*_node->getLocalTransform();
        glUniformMatrix4fv(matrixLoc, 1, GL_FALSE, currModelViewProjectionMatrix.data());
        Util::GLErrorAssert();

        //Set the uniform variable for texture image in shader
        int textureUniform = glGetUniformLocation(_shader->getShaderId(),"imgTexture");
        glActiveTexture(GL_TEXTURE0);
        glBindTexture(GL_TEXTURE_2D, _texture->getTextureId());
        glUniform1i(textureUniform, 0);
        Util::GLErrorAssert();

        //Specify the vertex coordinates
        int vertexLoc = glGetAttribLocation(_shader->getShaderId(), "InVertex");
        glBindBuffer(GL_ARRAY_BUFFER, _mesh->getVertexBufferId());
        glVertexAttribPointer(vertexLoc,            //attribute
                              3,                    //size
                              GL_FLOAT,             //type
                              GL_FALSE,             //not normalized
                              sizeof(GLfloat)*3,    //stride
                              (void*)0              //array buffer offset
                              );
        glEnableVertexAttribArray(vertexLoc);

        //Specify the texture coordinates
        int texCoord0Loc = glGetAttribLocation(_shader->getShaderId(), "InTexCoord0");
        glBindBuffer(GL_ARRAY_BUFFER, _mesh->getTexCoordsBufferId());
        glVertexAttribPointer(texCoord0Loc,         //attribute
                              2,                    //size 
                              GL_FLOAT,             //type
                              GL_FALSE,             //normalized? 
                              sizeof(GLfloat)*2,    //stride
                              (void*)0              //array buffer offset
                              );
        glEnableVertexAttribArray(texCoord0Loc);

        //Bind the index buffer before initiating draw
        glBindBuffer(GL_ELEMENT_ARRAY_BUFFER, _mesh->getElementBufferId());
        Util::GLErrorAssert();

        // Draw triangles using just bound(activated) index array
        glDrawElements(GL_TRIANGLES, _mesh->getNumFaceIndices(), GL_UNSIGNED_INT, 0);
        Util::GLErrorAssert();

        //Deactivate array buffers
        glDisableVertexAttribArray(vertexLoc);
        glDisableVertexAttribArray(texCoord0Loc);

        // bind with 0, so, switch back to normal pointer operation
        glBindBufferARB(GL_ARRAY_BUFFER, 0);
        glBindBufferARB(GL_ELEMENT_ARRAY_BUFFER, 0);
        glBindTexture(GL_TEXTURE_2D, 0);
        glUseProgram(0);
        Util::GLErrorAssert();
    }
}