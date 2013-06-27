#pragma once

#include "Util.h"

namespace SolarGL
{
    /// \brief  Class that manages the shader loading and compiling
    class Shader
    {
    public:
        /// \brief  Constructor
        Shader();

        /// \brief  Sets the filepaths for vertex and fragment shader programs
        void load(const char* vertexShaderPath,
                  const char* fragmentShaderPath);

        /// \brief  Compiles and links the shaders; assigns shader ids
        void prepare();

        inline GLuint& getShaderId(){  return _shaderProgramId; }

    protected:
        /// \brief  Dumps error log if any in shader compilation/linking
        void _getErrorLog(int shaderId);

        /// \brief  Opens a shader file and loads the source
        void _readShaderSource(const char* filename, std::string& output);

        /// \brief  Loads and compiles a specific shader
        /// \detail Assigns the shader id
        void _compileShader(const std::string& shaderSrc, GLuint& shaderId, GLenum shaderType);

        /// \brief  Attaches and links a specific shader
        /// \detail Assigns the corresponding shader shader id
        void _attachAndLinkShader(const GLuint& vertShaderId, const GLuint& fragShaderId, GLuint& shaderProgramId);


        GLuint _vertexShaderId;
        GLuint _fragmentShaderId;
        GLuint _shaderProgramId;

        std::string _vertexShaderPath;
        std::string _fragmentShaderPath;
    };
}
