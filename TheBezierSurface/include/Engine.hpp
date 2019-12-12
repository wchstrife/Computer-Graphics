//
// Created by edai on 20/03/18.
//

#ifndef ENGINE_HPP
#define ENGINE_HPP

#include "GraphicalCore.hpp"
#include <glm/glm.hpp>
#include <list>
#include <array>
#include <vector>

#define TEXTURES_NAMES "thu.jpg"

class Engine
{
public:
    Engine();
    ~Engine();

    static void _Update()
    {
        Instance()->InitUpdate();
        Instance()->Update();
        Instance()->EndUpdate();
        GraphicalCore::UpdateGl();
    }

    static GLfloat bezier_points[5][5][3];
    static int current_texture;
    static int ptr[2];
    static int smoothness[2];
    static bool grid;
    static bool text;
    std::vector<GLuint> *textures;

private:
    void InitUpdate();
    void EndUpdate();
    void Update();
    void InitTextures();
    void InitLights();
    void PrintInformation();
    void RenderBitmapString(float x, float y, void *font, std::string s);

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
