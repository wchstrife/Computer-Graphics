

#include <Mesh.hpp>
#include "Engine.hpp"

Engine *Engine::instance = nullptr;
Camera* Engine::mainCamera = new Camera();

Engine::Engine()
{
    mainCamera->SetPosition(glm::vec3(0, 0.0f, 0));
    mainCamera->SetLookAt(glm::vec3(0.0, 0.0, 0.035));
    for (auto &i : GraphicalCore::Instance()->meshes)
        i.Init();
}

void Engine::SetLight(GLfloat* pos)
{
    GLfloat light_ambient[] = {0.1, 0.1, 0.1, 1.0};
    GLfloat light_diffuse[] = {1.0, 1.0, 1.0, 1.0};
    GLfloat light_specular[] = {1.0, 1.0, 1.0, 1.0};

    glLightModeli(GL_LIGHT_MODEL_TWO_SIDE, GL_TRUE);
    glLightfv(GL_LIGHT0, GL_AMBIENT, light_ambient);
    glLightfv(GL_LIGHT0, GL_DIFFUSE, light_diffuse);
    glLightfv(GL_LIGHT0, GL_SPECULAR, light_specular);
    glLightfv(GL_LIGHT0, GL_POSITION, pos);
    glEnable(GL_LIGHT0);
}

void Engine::Update(float dt)
{
    GLfloat light_position[] = {2.0, 4.0, 8.0, 1.0};

    glHint(GL_PERSPECTIVE_CORRECTION_HINT, GL_NICEST);
    glShadeModel(GL_SMOOTH);
    glDepthFunc(GL_LEQUAL);
    glEnable(GL_NORMALIZE);
    glEnable(GL_AUTO_NORMAL);
    glEnable(GL_DEPTH_TEST);
    glEnable(GL_LIGHTING);

    SetLight(light_position);
    mainCamera->Update();
    for (auto &i : GraphicalCore::Instance()->meshes)
        i.Render();

    glDisable(GL_NORMALIZE);
    glDisable(GL_AUTO_NORMAL);
    glDisable(GL_DEPTH_TEST);
    glDisable(GL_LIGHTING);
    glDisable(GL_LIGHT0);
}
