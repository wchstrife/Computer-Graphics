//
// Created by wchstrife.
//

#ifndef ASSIGNMENT_APPLICATION_HPP
#define ASSIGNMENT_APPLICATION_HPP

#include <GL/glew.h>
#include <OpenGL/gl.h>
#include <GLUT/glut.h>
// #include <GL/freeglut.h>
#include <iostream>
#include <SOIL/SOIL.h>
#include <unistd.h>
#include <cstdlib>
#include <getopt.h>
#include <string>

#define DEFAULT_WIDTH 960
#define DEFAULT_HEIGHT 960
#define WINDOWPOS_X 500
#define WINDOWPOS_Y 50
#define WINDOW_TITLE "Chenhao Wang - 2019214541"

struct Options
{
    std::string window_name;
    int         width;
    int         height;

public:
    Options()
    {
        width = DEFAULT_WIDTH;
        height = DEFAULT_HEIGHT;
    }
};

class Application
{
public:
    static bool Parse(Options *, int, char**);
    static void Start(int, char **);

protected:
    Application();
    ~Application();
};


#endif //ASSIGNMENT2_APPLICATION_HPP
