#include "Shader.h"

namespace SolarGL
{
    Shader::Shader()
    {
    }

    void Shader::setSources(const char* vertexShaderPath,
                            const char* fragmentShaderPath)
    {
        _vertexShaderPath = std::string(vertexShaderPath);
        _fragmentShaderPath = std::string(fragmentShaderPath);
    }

    void Shader::prepare()
    {
        std::string vertexSrc;
        _readShaderSource(_vertexShaderPath.c_str(), vertexSrc);

        std::string fragmentSrc;
        _readShaderSource(_fragmentShaderPath.c_str(), fragmentSrc);

        //Compile vertex shader
        _compileShader(vertexSrc, _vertexShaderId, GL_VERTEX_SHADER);

        //Compile fragment shader
        _compileShader(fragmentSrc, _fragmentShaderId, GL_FRAGMENT_SHADER);

        //Attach and link shaders
        _attachAndLinkShader(_vertexShaderId, _fragmentShaderId, _shaderProgramId);
    }

    void Shader::_compileShader(const std::string& shaderSrc, GLuint& shaderId, GLenum shaderType)
    {
        //Obtain length of source
        int shaderSourceLen = shaderSrc.length();
        const char* shaderSrcStr = shaderSrc.c_str();

        //Create shader
        shaderId = glCreateShader(shaderType);
        ASSERT(shaderId!=0,"Unable to create shader\n");

        //Specify the shader source
        glShaderSource(shaderId,           //Shader Id
                       1,                  //Number of shaders required
                       &shaderSrcStr,      //Shader source
                       &shaderSourceLen);   //Character length of the source
        Util::GLErrorAssert();

        //Compile the shader
        glCompileShader(shaderId);

        //We now check compilation status
        GLint shader_ok;
        glGetShaderiv(shaderId, GL_COMPILE_STATUS, &shader_ok);
        if (!shader_ok)
        {
            //Compilation failed
            printf("ERROR: Shader failed to compile. Error log follows:\n");
            _getErrorLog(shaderId);
            glDeleteShader(shaderId);
            assert(false);
        }
        Util::GLErrorAssert();
    }

    void Shader::_attachAndLinkShader(const GLuint& vertShaderId, const GLuint& fragShaderId, GLuint& shaderProgramId)
    {
        //Create a new program ID
       shaderProgramId = glCreateProgram();

       glAttachShader(shaderProgramId, vertShaderId);
       glAttachShader(shaderProgramId, fragShaderId);
       Util::GLErrorAssert();

       //We can bind attribute variables here in case we are specifying
       //the indices to bind to. Since we don't do that, and let GL implementation
       //assign the indices for attribute variables, we can bind buffers *after* linking the shader.
       //We query the ids bound during rendering via glGetAttribLocation
       glLinkProgram(shaderProgramId);

       GLint program_ok;
       glGetProgramiv(shaderProgramId, GL_LINK_STATUS, &program_ok);
       if (!program_ok)
       {
           printf("Failed to link program with vertex and fragment shaders\n");
           GLint log_length;
           char *log;

           glGetProgramiv(shaderProgramId, GL_INFO_LOG_LENGTH, &log_length);
           log = new char[log_length+1];

           glGetProgramInfoLog(shaderProgramId, log_length, NULL, log);

           //Dump the error to console
           printf("%s\n", log);

           delete [] log;

           glDeleteProgram(shaderProgramId);
           assert(false);
       }
    }

    void Shader::_readShaderSource(const char* filename, std::string& output)
    {
        FILE* pShaderFile;
        pShaderFile = fopen(filename, "r");
        if (pShaderFile==NULL)
        {
            printf("For file named:%s\n",filename);
            assert(false);
        }

        //Obtain length of source
        fseek (pShaderFile , 0 , SEEK_END);
        int shaderLength = ftell (pShaderFile);
        rewind (pShaderFile);

        //Allocate memory for source
        char* source = new char[shaderLength+1];

        //Copy the file's contents over
        int num_read = fread(source,1,shaderLength,pShaderFile);
		source[shaderLength] = '\0';

        //Close the file now that we are done with it
        fclose (pShaderFile);

        if (num_read != shaderLength)
        {
            printf("DW_ERROR: While reading file: %s", filename);
            assert(false);
        }

        output = std::string(source);
        delete [] source;
    }

    void Shader::_getErrorLog(int shaderId)
    {
        GLint log_length;
        char *log;

        //glGetShaderiv returns a parameter from a shader object
        //We use it to get information regarding the log string
        glGetShaderiv(shaderId, GL_INFO_LOG_LENGTH, &log_length);

        //Allocate memory for the log error string
        log = new char[log_length+1];

        //Now we get the shader log string itself
        glGetShaderInfoLog(shaderId, log_length, NULL, log);

        //Dump the error to console
        printf("%s\n", log);
        delete [] log;
    }

}
