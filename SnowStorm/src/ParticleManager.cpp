//
// Created by wchstrife.
//

#include <iostream>
#include <GraphicalCore.hpp>
#include "ParticleManager.hpp"
#include <algorithm>

ParticleManager *ParticleManager::instance = nullptr;

ParticleManager::ParticleManager()
{
    buffer = new std::vector<Particle>();
    spawnfactor = 100;
    texture = 0;
    for (int i = 0; i < spawnfactor; i++)
        CreateRandomParticle();
}

void ParticleManager::LoadTexture()
{
    if (texture == 0)
        texture = SOIL_load_OGL_texture(TEXTURES_NAME, SOIL_LOAD_AUTO, SOIL_CREATE_NEW_ID, SOIL_FLAG_NTSC_SAFE_RGB | SOIL_FLAG_MULTIPLY_ALPHA);
    glBindTexture(GL_TEXTURE_2D, texture);
    glTexEnvf(GL_TEXTURE_ENV, GL_TEXTURE_ENV_MODE, GL_MODULATE);
    glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MAG_FILTER, GL_LINEAR);
    glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MIN_FILTER, GL_LINEAR);
}

void ParticleManager::CreateRandomParticle(bool random)
{
    static std::mt19937 gen(rd());
    static std::uniform_real_distribution<> dis(-1.0f, 1.0f);
    static std::uniform_real_distribution<> dis_f(0.05f, 0.15f);
    static std::uniform_real_distribution<> dis_s(SNOW_SIZE  - 0.025f, SNOW_SIZE + 0.05f);

    auto s =  (float)dis_s(gen);
    auto *p = new Particle( (*new glm::vec3((float)dis(gen), random ? dis(gen) : 1.0f + s, 0.2)),
            (*new glm::vec3(0.0, - dis_f(gen), 0.0)),
                            s);
    buffer->push_back(*p);
}

void ParticleManager::ResetPosition(Particle &p)
{
    static std::mt19937 gen(rd());
    static std::uniform_real_distribution<> dis(-1.0f, 1.0f);
    static std::uniform_real_distribution<> dis_f(0.05f, 0.15f);
    static std::uniform_real_distribution<> dis_s(SNOW_SIZE  - 0.025f, SNOW_SIZE + 0.025f);

    p.Velocity = *(new glm::vec3(0.0, - dis_f(gen), 0.0f));
    p.Size = (float)dis_s(gen);
    p.Position = *(new glm::vec3(dis(gen), 1.0f + p.Size, 0.2));
}

void ParticleManager::PutSnow(glm::vec3 &s, float size)
{
    glColor4f(1.0f, 1.0f, 1.0f, 1.0f);
    glTexCoord3f(0.0, 1.0, s.z);
    glVertex3f(s.x - size, s.y + size, s.z);
    glTexCoord3f(1.0, 1.0, s.z);
    glVertex3f(s.x + size, s.y + size, s.z);
    glTexCoord3f(1.0, 0.0, s.z);
    glVertex3f(s.x + size, s.y - size, s.z);
    glTexCoord3f(0.0, 0.0, s.z);
    glVertex3f(s.x - size, s.y - size, s.z);
}

void ParticleManager::Render(float dt)
{
    static float timer = 0.0f;

    glLoadIdentity();
    timer += dt;
    if (timer > 0.25f && spawnfactor < MAX_PARTICLES)
    {
        CreateRandomParticle(false);
        spawnfactor++;
        timer = 0.0f;
    }
    glBegin(GL_QUADS);
    for (auto p = buffer->begin(); p != buffer->end() ; )
    {
        PutSnow(p->Position, p->Size);
        p->Position += (p->Velocity * dt);
        if (p->Position.y < -1.0f - p->Size)
            ResetPosition(*p);
        else
            p++;
    }
    glEnd();
    glPopMatrix();
}
