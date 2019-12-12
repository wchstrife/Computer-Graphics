
#ifndef ENGINE_HPP
#define ENGINE_HPP

#include "GraphicalCore.hpp"

#include <glm/glm.hpp>
#include <list>
#include <array>
#include <vector>

class Engine
{
public:
    Engine();
    ~Engine() = default;
    void SetLight(GLfloat* pos);

    void Update(float dt);
    static Camera *mainCamera;

#pragma SINGLETON
private:
    static Engine* instance;

public:
    static Engine* Instance()
    {
        if (instance == nullptr)
        {
            instance = new Engine();
        }
        return instance;
    }
#pragma END SINGLETON

};

#endif //ENGINE_HPP
