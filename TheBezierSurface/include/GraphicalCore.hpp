//
// Created by edai on 20/03/18.
//

#ifndef ASSIGNMENT2_GRAPHICALCORE_HPP
#define ASSIGNMENT2_GRAPHICALCORE_HPP

#include "Application.hpp"

class GraphicalCore
{
public:
    bool Run(int ac, char **av, Options *options);
    static void UpdateGl();
    static void _KeyboardHandle(unsigned char key, int x, int y)
    {
        GraphicalCore::Instance()->KeyboardHandle(key, x, y);
    }
    static void _SpecialKeyHandle(int key, int x, int y)
    {
        GraphicalCore::Instance()->SpecialKeyHandle(key, x, y);
    }
    static void Reshape(int w, int h);

private:
    void Init();
    void KeyboardHandle(unsigned char, int, int);
    void SpecialKeyHandle(int key, int x, int y);
    GraphicalCore();
    ~GraphicalCore();

#pragma SINGLETON
private:
    static GraphicalCore* instance;

public:
    static GraphicalCore* Instance()
    {
        if (instance == nullptr)
        {
            instance = new GraphicalCore();
        }
        return instance;
    }
#pragma
};

#endif //ASSIGNMENT2_GRAPHICALCORE_HPP
