//
// Created by edai on 20/03/18.
//

#include <StarEngine.hpp>

GraphicalCore* GraphicalCore::instance = nullptr;
int GraphicalCore::Rotation = 20;

void GraphicalCore::Init()
{
    glEnable(GL_TEXTURE_2D);
    glShadeModel(GL_SMOOTH);
    glClearColor(0.0f, 0.0f, 0.0f, 0.5f);
    glClearDepth(1.0f);
    glEnable(GL_DEPTH_TEST);
    glEnable(GL_BLEND);
    glBlendFunc(GL_SRC_ALPHA, GL_ONE_MINUS_SRC_ALPHA);
    glDepthFunc(GL_LEQUAL);
    glHint(GL_PERSPECTIVE_CORRECTION_HINT, GL_NICEST);
}

void display(void) {
    glClear(GL_COLOR_BUFFER_BIT);
    glFlush();
}

bool GraphicalCore::Run(int ac, char **av, Options *options)
{
    glutInit(&ac, av);
    glutInitDisplayMode(GLUT_RGB | GLUT_DOUBLE);
    glutInitWindowPosition(0,0);
    glutInitWindowSize(options->width, options->height);
    glutCreateWindow(options->window_name.c_str());
    Init();
    glutIdleFunc(StarEngine::_Update);
    glutKeyboardFunc(GraphicalCore::_KeyboardHandle);
    glutDisplayFunc(&display);
    glutMainLoop();
    return (true);
}

void GraphicalCore::UpdateGl()
{
    glutSwapBuffers();
    glutPostRedisplay();
}

void GraphicalCore::KeyboardHandle(unsigned char key, int x, int y)
{
    switch (key)
    {
        case 'q' :
        case 27:
            //glutLeaveMainLoop();
            //glutDestroyWindow(key);
            exit(0);
            break;
        case 'w':
            break;
        case 's':
            break;
        default:
            return;
    }
}


GraphicalCore::GraphicalCore() = default;

GraphicalCore::~GraphicalCore() = default;