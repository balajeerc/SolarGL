#include "Mesh.h"
#include "Shader.h"
#include "Texture.h"
#include "Node.h"

#include "Model.h"

namespace SolarGL
{
    Model::Model():
    _mesh(NULL),
    _texture(NULL),
    _shader(NULL),
    _node(NULL)
    {
    }

    void Model::renderMesh(const mat4& projectionMatrix,
                                  const mat4& viewMatrix)
    {
        if((!_mesh) || (!_texture) || (!_shader) || (!_node))
        {
            //Skip render
            return;
        }

        //Set the shader
        int shaderId = _shader->getShaderId();
        glUseProgram(shaderId);
        Util::GLErrorAssert();

        //Calculate the model view matrix
        mat4 modelView = viewMatrix*_node->getLocalTransform();
        mat4 modelViewInv = cml::inverse(modelView);
        mat3 modelViewInv3x3;
        matrix_linear_transform(modelViewInv3x3, modelViewInv);
        modelViewInv3x3.transpose();

        //Calculate the model inv
        mat4 modelInv = cml::inverse(_node->getLocalTransform()); 
        mat3 modelInv3x3;
        matrix_linear_transform(modelInv3x3, modelInv);
        modelInv3x3.transpose();

        //Caclulate view matrix inverse
        mat4 viewInv = cml::inverse(viewMatrix);
        viewInv.transpose();

        mat4 modelMatrix = _node->getLocalTransform();
        mat4 modelMatrixT = modelMatrix;
        modelMatrixT.transpose();

        mat4 viewMatrixT = viewMatrix;
        viewMatrixT.transpose();

        mat4 projectionMatrixT = projectionMatrix;
        projectionMatrixT.transpose();

        mat4 modelViewProjectionMatrix = projectionMatrix*viewMatrix*_node->getLocalTransform();
        modelViewProjectionMatrix.transpose();

        //Get the entry point handles in the shader
        int modelMatLoc = glGetUniformLocation(shaderId, "m");
        int viewMatLoc = glGetUniformLocation(shaderId, "v");
        int projectionMatLoc = glGetUniformLocation(shaderId, "p");
        int modelViewProjMat = glGetUniformLocation(shaderId, "mvpIn");
        int invModelViewMatLoc = glGetUniformLocation(shaderId, "m_3x3_inv_transp");
        int invViewMatLoc = glGetUniformLocation(shaderId, "v_inv");    

        int vertexLoc = glGetAttribLocation(shaderId, "v_coord");
        int normalLoc = glGetAttribLocation(shaderId, "v_normal");
        int texCoord0Loc = glGetAttribLocation(shaderId, "v_texcoord");
        int textureUniform = glGetUniformLocation(shaderId,"imgTexture");
                
        glUniformMatrix4fv(modelMatLoc, 1, GL_FALSE, modelMatrixT.data());
        glUniformMatrix4fv(viewMatLoc, 1, GL_FALSE, viewMatrixT.data());
        glUniformMatrix4fv(projectionMatLoc, 1, GL_FALSE, projectionMatrixT.data());
        glUniformMatrix3fv(invModelViewMatLoc, 1, GL_FALSE, modelViewInv3x3.data());
        glUniformMatrix4fv(invViewMatLoc, 1, GL_FALSE, viewInv.data());
        glUniformMatrix4fv(modelViewProjMat, 1, GL_FALSE, modelViewProjectionMatrix.data());

        Util::GLErrorAssert();

        //Set the uniform variable for texture image in shader
        glActiveTexture(GL_TEXTURE0);
        glBindTexture(GL_TEXTURE_2D, _texture->getTextureId());
        glUniform1i(textureUniform, 0);
        Util::GLErrorAssert();

        //Specify the vertex coordinates
        glBindBuffer(GL_ARRAY_BUFFER, _mesh->getVertexBufferId());
        glVertexAttribPointer(vertexLoc,            //attribute
                              3,                    //size
                              GL_FLOAT,             //type
                              GL_FALSE,             //not normalized
                              sizeof(GLfloat)*3,    //stride
                              (void*)0              //array buffer offset
                              );
        glEnableVertexAttribArray(vertexLoc);

        //Specify the normal data
        glBindBuffer(GL_ARRAY_BUFFER, _mesh->getNormalBufferId());
        glVertexAttribPointer(normalLoc,            //attribute
                              3,                    //size
                              GL_FLOAT,             //type
                              GL_FALSE,             //not normalized
                              sizeof(GLfloat)*3,    //stride
                              (void*)0              //array buffer offset
                              );
        glEnableVertexAttribArray(normalLoc);

        //Specify the texture coordinates
        glBindBuffer(GL_ARRAY_BUFFER, _mesh->getTexCoordsBufferId());
        glVertexAttribPointer(texCoord0Loc,         //attribute
                              2,                    //size 
                              GL_FLOAT,             //type
                              GL_FALSE,             //normalized? 
                              sizeof(GLfloat)*2,    //stride
                              (void*)0              //array buffer offset
                              );
        glEnableVertexAttribArray(texCoord0Loc);
        Util::GLErrorAssert();


        //Bind the index buffer before initiating draw
        glBindBuffer(GL_ELEMENT_ARRAY_BUFFER, _mesh->getElementBufferId());
        Util::GLErrorAssert();

        // Draw triangles using just bound(activated) index array
        glDrawElements(GL_TRIANGLES, _mesh->getNumFaceIndices(), GL_UNSIGNED_INT, 0);
        Util::GLErrorAssert();

        //Deactivate array buffers
        glDisableVertexAttribArray(vertexLoc);
        glDisableVertexAttribArray(normalLoc);
        glDisableVertexAttribArray(texCoord0Loc);

        // bind with 0, so, switch back to normal pointer operation
        glBindBufferARB(GL_ARRAY_BUFFER, 0);
        glBindBufferARB(GL_ELEMENT_ARRAY_BUFFER, 0);
        glBindTexture(GL_TEXTURE_2D, 0);
        glUseProgram(0);
        Util::GLErrorAssert();
    }
}