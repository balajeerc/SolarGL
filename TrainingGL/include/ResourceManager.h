#pragma once

#include "Util.h"
#include "Shader.h"
#include "Mesh.h"
#include "Texture.h"

namespace SolarGL
{
    /// \brief  Class that handles resource loading
    /// \detail Globally accessible singleton that ensures that there
    ///         is only one instance of a given resource loaded. It then
    ///         returns pointers/references to the resource when requested
    ///         subsequently
    class ResourceManager
    {
    public:
        Shader* getShader(const char* vertexShaderPath, const char* fragmentShaderPath);
        Mesh* getMesh(const char* filename);
        Texture* getTexture(const char* filename);

        static ResourceManager* get()
        {
            if(!_Instance)
            {
                _Instance = new ResourceManager();
            }
            
            return _Instance;
        }

    protected:
        ResourceManager();
        virtual ~ResourceManager();

        static ResourceManager* _Instance;

        std::map<std::string, Shader*> _shaders;
        std::map<std::string, Mesh*> _meshes;
        std::map<std::string, Texture*> _textures;
    };
};