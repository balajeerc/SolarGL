
#include "ResourceManager.h"
#include "Scene.h"

namespace SolarGL
{
    Scene::Scene()
    {

    }

    Scene::~Scene()
    {
        std::map<std::string, Model*>::iterator iter;
        for(iter=_models.begin(); iter!=_models.end(); ++iter)
        {
            Model* iterModel = iter->second;
            delete iterModel;
        }
    }

    void Scene::prepare()
    {
         _camera.setPerspective(45.f,
                               640.f/480.f,
                               1.f,
                               100.f);
         
         _camera.lookAt(vec3(0.f,0.f, 5.f),  //camera location
                       vec3(0.f,0.f,0.f),   //target location
                       vec3(0.f,1.f,0.f));  //up direction

         ResourceManager* resMgr = ResourceManager::get();
         
         //Create an instance of the PerPixel shader
         Shader* shader = resMgr->getShader("C:\\SolarGL\\data\\shaders\\PerPixelLighting_VS.glsl",
                                             "C:\\SolarGL\\data\\shaders\\PerPixelLighting_FS.glsl");
         
         //Load a suzanne mesh
         Mesh* mesh = resMgr->getMesh("C:\\SolarGL\\data\\meshes\\suzanne_mesh.json");

         //Load a grey texture
        Texture* texture = resMgr->getTexture("C:\\SolarGL\\data\\images\\gray.png");
        
        //Setup the mesh renderer
        Model* model = new Model();
        model->setTexture(texture);
        model->setMesh(mesh);
        model->setShader(shader);

        _models["suzanne"] = model;
    }

    void Scene::update(const double& timeElapsed)
    {
        std::map<std::string, Model*>::iterator iter;
        for(iter=_models.begin(); iter!=_models.end(); ++iter)
        {
            Model* iterModel = iter->second;
            iterModel->update(timeElapsed);
            iterModel->render(_camera.getProjectionMatrix(),
                              _camera.getViewMatrix());  
        }
    }
}