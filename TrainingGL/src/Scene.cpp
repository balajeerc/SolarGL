
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
         
         _camera.lookAt(vec3(0.f, 0.f, 15.f),  //camera location
                       vec3(0.f, 0.f, 0.f),   //target location
                       vec3(0.f, 1.f, 0.f));  //up direction

         ResourceManager* resMgr = ResourceManager::get();
         
         //Create an instance of the PerPixel shader
         Shader* shader = resMgr->getShader(".\\data\\shaders\\PerPixelLighting_VS.glsl",
                                             ".\\data\\shaders\\PerPixelLighting_FS.glsl");

         //Shader* sunShader = resMgr->getShader(".\\data\\shaders\\SimpleImage_VS.glsl",
         //                                      ".\\data\\shaders\\SimpleImage_FS.glsl");

         
         Mesh* mesh;
         Texture* texture;


         // Now we load the planets
         
         //Load the sun's mesh and texture
         //mesh = resMgr->getMesh(".\\data\\meshes\\sun_mesh.json");
         //texture = resMgr->getTexture(".\\data\\images\\sunMap.jpg");
         //Model* sunModel = new Model();
         //sunModel->setTexture(texture);
         //sunModel->setMesh(mesh);
         //sunModel->setShader(sunShader);
         //_models["sun"] = sunModel;


         mesh = resMgr->getMesh(".\\data\\meshes\\earth_mesh.json");
         texture = resMgr->getTexture(".\\data\\images\\earthMap.jpg");
         Model* earthModel = new Model();
         earthModel->setTexture(texture);
         earthModel->setMesh(mesh);
         earthModel->setShader(shader);
         earthModel->getNode()->moveTo(vec3(10.f, 0.f, 0.f));
         _models["earth"] = earthModel;


         mesh = resMgr->getMesh(".\\data\\meshes\\moon_mesh.json");
         texture = resMgr->getTexture(".\\data\\images\\moonMap.jpg");
         Model* moonModel = new Model();
         moonModel->setTexture(texture);
         moonModel->setMesh(mesh);
         moonModel->setShader(shader);
         //moonModel->getNode()->moveTo(vec3(15.f, 5.f, 0.f));
         _models["moon"] = moonModel;
    }

    void Scene::update(const double& timeElapsed)
    {
        std::map<std::string, Model*>::iterator iter;
        for(iter=_models.begin(); iter!=_models.end(); ++iter)
        {
            Model* iterModel = iter->second;
            
            
            

            iterModel->render(_camera.getProjectionMatrix(),
                              _camera.getViewMatrix());  
        }
    }
}