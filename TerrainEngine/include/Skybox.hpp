//
// Created by edai on 10/05/18.
//

#ifndef TERRAINSkybox_SKYBOX_HPP
#define TERRAINSkybox_SKYBOX_HPP

#include "GraphicalCore.hpp"
#define FOLDER_SKYBOX "./resources/SkyBoxForCubeMap/"
#define FACES_NAMES "SkyBox0.bmp", "SkyBox1.bmp", "SkyBox2.bmp", "SkyBox3.bmp", "SkyBox4.bmp"

class Skybox
{
public:
    static GLfloat size;
    static GLfloat factorY;

    void Init();
    void Render(float dt);
    GLuint GetTexture(int i);

    enum Faces {
        MAP_POSITIVE_Z = 0,
        MAP_POSITIVE_X = 1,
        MAP_NEGATIVE_Y = 2,
        MAP_NEGATIVE_X = 3,
        MAP_POSITIVE_Y = 4
    };
private:
    Skybox() = default;
    ~Skybox() = default;
    GLuint textures[5];
    const char *faces_names[5] = {FACES_NAMES};

#pragma SINGLETON
    private:
        static Skybox* instance;

    public:
        static Skybox* Instance()
        {
            if (instance == nullptr)
            {
                instance = new Skybox();
            }
            return instance;
        }

#pragma END SINGLETON

    void ApplyTexture(GLuint t);
};

#endif //TERRAINSkybox_SKYBOX_HPP
