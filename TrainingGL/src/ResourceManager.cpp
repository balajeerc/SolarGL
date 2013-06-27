#include "ResourceManager.h"

namespace SolarGL
{
    ResourceManager* ResourceManager::_Instance = NULL;

    ResourceManager::ResourceManager()
    {
        //There cannot be an instance of rm before this
        assert(!_Instance);
    }

    ResourceManager::~ResourceManager()
    {
        
    }

    Shader* ResourceManager::getShader(const char* vertexShaderPath, const char* fragmentShaderPath)
    {
        std::string shaderName = std::string(vertexShaderPath) + std::string(fragmentShaderPath);
        std::map<std::string, Shader*>::iterator it = _shaders.find(shaderName);
        if(it!=_shaders.end())
        {
            return it->second;
        }

        Shader* newShader = new Shader();
        //Setup the shaders
        newShader->load(vertexShaderPath,
                        fragmentShaderPath);
        newShader->prepare();
        
        _shaders[shaderName] = newShader;

        return newShader;
    }

    Mesh* ResourceManager::getMesh(const char* filename)
    {
        std::string meshName = std::string(filename);
        std::map<std::string, Mesh*>::iterator it = _meshes.find(meshName);
        if(it!=_meshes.end())
        {
            return it->second;
        }

        Mesh* newMesh = new Mesh();

        //Setup the meshes
        newMesh->load(filename);
        newMesh->prepare();
        
        _meshes[meshName] = newMesh;

        return newMesh;
    }

    Texture* ResourceManager::getTexture(const char* filename)
    {
        std::string textureName = std::string(filename);
        std::map<std::string, Texture*>::iterator it = _textures.find(textureName);
        if(it!=_textures.end())
        {
            return it->second;
        }

        Texture* newTexture = new Texture();

        //Setup the textures
        newTexture->load(filename);
        newTexture->prepare();
        
        _textures[textureName] = newTexture;

        return newTexture;
    }
}