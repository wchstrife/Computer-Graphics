//
// Created by wchstife.
//

#include "Engine.hpp"

Engine *Engine::instance = nullptr;

void Engine::InitBackground()
{
    background = SOIL_load_OGL_texture("background.tga", SOIL_LOAD_AUTO, SOIL_CREATE_NEW_ID, SOIL_FLAG_NTSC_SAFE_RGB | SOIL_FLAG_MULTIPLY_ALPHA);
    glTexEnvf(GL_TEXTURE_ENV, GL_TEXTURE_ENV_MODE, GL_MODULATE);
}

Engine::Engine()
{
    glEnable(GL_DEPTH_TEST);
    InitBackground();
    ParticleManager::Instance()->LoadTexture();
}

void Engine::DrawBackground()
{
    glTexEnvi(GL_TEXTURE_ENV, GL_TEXTURE_ENV_MODE, GL_MODULATE);
    glBindTexture(GL_TEXTURE_2D, background);

    glBegin(GL_QUADS);
    glTexCoord2f(0, 0); glVertex3f(-1.0, 1.0, 0.2);
    glTexCoord2f(1, 0); glVertex3f(1.0, 1.0, 0.2);
    glTexCoord2f(1, 1); glVertex3f(1.0, -1.0, 0.2);
    glTexCoord2f(0, 1); glVertex3f(-1.0, -1.0, 0.2);
    glEnd();
    glPopMatrix();
}

void Engine::Update(float dt)
{
    glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);
    glLoadIdentity();
    glEnable(GL_TEXTURE_2D);
    DrawBackground();

    glLoadIdentity();
    glEnable(GL_TEXTURE_2D);
    glEnable(GL_BLEND);
    glBlendFunc(GL_SRC_ALPHA, GL_ONE_MINUS_SRC_ALPHA);
    ParticleManager::Instance()->LoadTexture();
    ParticleManager::Instance()->Render(dt);
    glDisable(GL_TEXTURE_2D);
}
