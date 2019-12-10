//
// Created by edai on 19/03/18.
//

#ifndef ASSIGNMENT2_APPLICATION_HPP
#define ASSIGNMENT2_APPLICATION_HPP

#include <OpenGL/gl.h>
#include <GLUT/glut.h>
#include <iostream>
#include <SOIL/SOIL.h>
#include <unistd.h>
#include <cstdlib>
#include <getopt.h>
#include <string>

#define DEFAULT_WIDTH 960
#define DEFAULT_HEIGHT 960
#define WINDOW_TITLE "Assignment 2"

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
