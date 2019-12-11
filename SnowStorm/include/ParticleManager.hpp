//
// Created by wchstrife.
//

#ifndef SNOWSTORM_PARTICLEMANAGER_HPP
#define SNOWSTORM_PARTICLEMANAGER_HPP

#include <OpenGL/gl.h>
#include <glm/vec4.hpp>
#include <glm/vec2.hpp>
#include <vector>
#include <random>
#include <SOIL/SOIL.h>
#include <glm/vec3.hpp>

#define TEXTURES_NAME "snow.png"
#define SNOW_SIZE 0.05f
#define MAX_PARTICLES 10000

struct Particle {
    glm::vec3 Position;
    glm::vec3 Velocity;
    GLfloat Size;

    Particle() : Position(0.0f), Velocity(0.0f), Size(0.0f){
    }
    Particle(glm::vec3 p, glm::vec3 v, GLfloat l) : Position(p), Velocity(v), Size(l){
    }
};

class ParticleManager
{
public:
    void LoadTexture();
    void Render(float dt);

private:
    ParticleManager();
    ~ParticleManager() = default;
    void CreateRandomParticle(bool r = true);
    void PutSnow(glm::vec3 &s, float size);
    void ResetPosition(Particle &p);

    int spawnfactor;
    GLuint texture;
    std::vector<Particle> *buffer;
    std::random_device rd;

    #pragma SINGLETON
private:
    static ParticleManager* instance;

public:
    static ParticleManager* Instance()
    {
        if (instance == nullptr)
        {
            instance = new ParticleManager();
        }
        return instance;
    }
    #pragma

};

#endif //SNOWSTORM_PARTICLEMANAGER_HPP
