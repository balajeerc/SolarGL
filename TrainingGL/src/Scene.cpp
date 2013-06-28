#include "AppClock.h"
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
         
         _camera.lookAt(vec3(0.f, 10.f, 30.f),  //camera location
                       vec3(0.f, 0.f, 0.f),   //target location
                       vec3(0.f, 1.f, -5.f));  //up direction

         ResourceManager* resMgr = ResourceManager::get();
         
         //Create an instance of the PerPixel shader
         Shader* shader = resMgr->getShader(".\\data\\shaders\\PerPixelLighting_VS.glsl",
                                             ".\\data\\shaders\\PerPixelLighting_FS.glsl");

         Shader* sunShader = resMgr->getShader(".\\data\\shaders\\SimpleImage_VS.glsl",
                                               ".\\data\\shaders\\SimpleImage_FS.glsl");
         //shader = sunShader;
         _shaders[DYNAMIC_LIGHTING] = shader;
         _shaders[STATIC_LIGHTING] = sunShader;
         
         Mesh* mesh;
         Texture* texture;


         // Now we load the planets
         
         //Load the sun's mesh and texture
         mesh = resMgr->getMesh(".\\data\\meshes\\sun_mesh.json");
         texture = resMgr->getTexture(".\\data\\images\\sunMap.jpg");
         _sun = new Model();
         _sun->setTexture(texture);
         _sun->setMesh(mesh);
         _sun->setShader(sunShader);
         _sun->rotationSpeed = 15.f;   //degrees per second
         _models["sun"] = _sun;


         mesh = resMgr->getMesh(".\\data\\meshes\\earth_mesh.json");
         texture = resMgr->getTexture(".\\data\\images\\earthMap.jpg");
         _earth = new Model();
         _earth->setTexture(texture);
         _earth->setMesh(mesh);
         _earth->setShader(shader);
         _earth->getNode()->moveTo(vec3(15.f, 0.f, 0.f));
         _earth->getNode()->setParent(_sun->getNode());
         _earth->rotationSpeed = 30.f;   //degrees per second
         _models["earth"] = _earth;


         mesh = resMgr->getMesh(".\\data\\meshes\\moon_mesh.json");
         texture = resMgr->getTexture(".\\data\\images\\moonMap.png");
         _moon = new Model();
         _moon->setTexture(texture);
         _moon->setMesh(mesh);
         _moon->setShader(shader);
         _moon->getNode()->setParent(_earth->getNode());
         _moon->getNode()->moveTo(vec3(5.f, 3.f, 0.f));         
         _models["moon"] = _moon;

         AppClock timer;
         _timeAtLastFrame = timer.getTimeElapsed();
    }

    void Scene::update(const double& timeElapsed)
    {
        std::map<std::string, Model*>::iterator iter;
        for(iter=_models.begin(); iter!=_models.end(); ++iter)
        {
            Model* iterModel = iter->second;
            
            double timeSinceLastFrame = timeElapsed - _timeAtLastFrame;

            float earthRotation = ((float)timeSinceLastFrame)*_earth->rotationSpeed;
            _earth->getNode()->rotate(vec3(0.f, earthRotation, 0.f));

            float sunRotation = ((float)timeSinceLastFrame)*_sun->rotationSpeed;
            _sun->getNode()->rotate(vec3(0.f, sunRotation, 0.f));


            iterModel->render(_camera.getProjectionMatrix(),
                              _camera.getViewMatrix());  

            //Reset timer
            _timeAtLastFrame = timeElapsed;
        }
    }

    void Scene::toggleLightingMode()
    {
        LightingMode currentMode = _lightingMode;
        if(_lightingMode==DYNAMIC_LIGHTING)
        {
            _lightingMode = STATIC_LIGHTING;
        }
        else
        {
            _lightingMode = DYNAMIC_LIGHTING;
        }

        _earth->setShader(_shaders[_lightingMode]);
        _moon->setShader(_shaders[_lightingMode]);
    }


}