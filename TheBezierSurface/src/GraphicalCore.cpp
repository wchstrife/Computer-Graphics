//
// Created by edai on 20/03/18.
//

#include <Engine.hpp>

GraphicalCore* GraphicalCore::instance = nullptr;

void GraphicalCore::Init()
{
    glHint(GL_PERSPECTIVE_CORRECTION_HINT, GL_NICEST);
    glShadeModel(GL_SMOOTH);
    glDepthFunc(GL_LEQUAL);
    glEnable(GL_DEPTH_TEST);
    glMatrixMode(GL_PROJECTION);
}

void display(void) {
    glClear(GL_COLOR_BUFFER_BIT);
    glFlush();
}

bool GraphicalCore::Run(int ac, char **av, Options *options)
{
    glutInit(&ac, av);
    glutInitDisplayMode(GLUT_RGB | GLUT_DOUBLE | GLUT_ALPHA | GLUT_DEPTH) ;
    glutInitWindowPosition(0,0);
    glutInitWindowSize(options->width, options->height);
    glutCreateWindow(options->window_name.c_str());
    Init();
    glutIdleFunc(Engine::_Update);
    glutReshapeFunc(GraphicalCore::Reshape);
    glutSpecialFunc(GraphicalCore::_SpecialKeyHandle);
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
        case 27:
            //glutLeaveMainLoop();
            exit(0);
            break;
        case 'r':
            Engine::smoothness[0] += 1;
            break;
        case 'f':
            Engine::smoothness[0] -= (Engine::smoothness[0] > 0 ? 1 : 0);
            break;
        case 't':
            Engine::smoothness[1] += 1;
            break;
        case 'g':
            Engine::smoothness[1] -= (Engine::smoothness[1] > 0 ? 1 : 0);
            break;
        case 'h' :
            Engine::text = !Engine::text;
            break;
        case '1':
            Engine::current_texture = 0;
            break;
        case '2':
            Engine::current_texture = 1;
            break;
        case '0':
            Engine::grid = !Engine::grid;
            break;
        case 'q':
        case 'a':
            Engine::bezier_points[Engine::ptr[0]][Engine::ptr[1]][0] += (key == 'q' ? 0.1f : -0.1f);
            break;
        case 'w':
        case 's':
            Engine::bezier_points[Engine::ptr[0]][Engine::ptr[1]][1] += (key == 'w' ? 0.1f : -0.1f);
            break;
        case 'e':
        case 'd':
            Engine::bezier_points[Engine::ptr[0]][Engine::ptr[1]][2] += (key == 'e' ? 0.1f : -0.1f);
            break;
        default:
            return;
    }
}

void GraphicalCore::SpecialKeyHandle(int key, int x, int y)
{
    switch (key)
    {
        case GLUT_KEY_UP:
            if (Engine::ptr[0] - 1 >= 0)
                Engine::ptr[0] -= 1;
            glutPostRedisplay();
            break;
        case GLUT_KEY_DOWN:
            if (Engine::ptr[0] + 1 < 5)
                Engine::ptr[0] += 1;
            glutPostRedisplay();
            break;
        case GLUT_KEY_LEFT:
            if (Engine::ptr[1] - 1 >= 0)
                Engine::ptr[1] -= 1;
            glutPostRedisplay();
            break;
        case GLUT_KEY_RIGHT:
            if (Engine::ptr[1] + 1 < 5)
                Engine::ptr[1] += 1;
            glutPostRedisplay();
            break;
        default:
            break;
    }
}

void GraphicalCore::Reshape(int w, int h)
{

}

GraphicalCore::GraphicalCore() = default;

GraphicalCore::~GraphicalCore() = default;