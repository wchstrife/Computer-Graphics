

#include <Engine.hpp>

GraphicalCore* GraphicalCore::instance = nullptr;
int GraphicalCore::old_t = 0;
int GraphicalCore::speedFactor = 1;
std::list<Mesh> GraphicalCore::meshes = *(new std::list<Mesh>());

void GraphicalCore::Init()
{
    glShadeModel(GL_SMOOTH);
    glEnable(GL_NORMALIZE);
    old_t = glutGet(GLUT_ELAPSED_TIME);
}

void display(void) {
    glClear(GL_COLOR_BUFFER_BIT);
    glFlush();
}

bool GraphicalCore::Run(int ac, char **av, Options *options)
{
    try
    {
        glutInit(&ac, av);
        glutInitDisplayMode(GLUT_RGB | GLUT_DOUBLE | GLUT_ALPHA | GLUT_DEPTH) ;
        glutInitWindowPosition(WINDOWPOS_X, WINDOWPOS_Y);
        glutInitWindowSize(options->width, options->height);
        glutCreateWindow(options->window_name.c_str());
        //glewExperimental = GL_TRUE;
        // GLuint err = glewInit();
        // if (err != GLEW_OK)
        //     return (false);
        Init();
        glutIdleFunc(GraphicalCore::Update);
        glutReshapeFunc(GraphicalCore::Reshape);
        glutSpecialFunc(GraphicalCore::SpecialKeyHandle);
        glutKeyboardFunc(GraphicalCore::KeyboardHandle);
        glutMouseFunc(GraphicalCore::MouseButton);
        glutMotionFunc(GraphicalCore::MouseMove);
        GraphicalCore::CreateMenu();
        glutDisplayFunc(&display);
        glutMainLoop();
        return (true);
    }
    catch (std::string &e)
    {
        std::cerr << "An error occurred : " << e << " !" << std::endl;
        exit(0);
        //glutLeaveMainLoop();
        return (false);
    }
    catch (...)
    {
        std::cerr << "An unknown error occurred !" << std::endl;
        exit(0);
        //glutLeaveMainLoop();
        return (false);
    }
}

void GraphicalCore::Update()
{
    int t = glutGet(GLUT_ELAPSED_TIME);
    float dt = (t - old_t) / 1000.0f;

    old_t = t;
    dt = dt * speedFactor;
    glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);

    Engine::Instance()->Update(dt);
    glutSwapBuffers();
}

void GraphicalCore::KeyboardHandle(unsigned char key, int, int)
{
    switch (key) {
        case 'w':
            Engine::Instance()->mainCamera->Move(Camera::CameraDirection::FORWARD);
            break;
        case 'a':
            Engine::Instance()->mainCamera->Move(Camera::CameraDirection::LEFT);
            break;
        case 's':
            Engine::Instance()->mainCamera->Move(Camera::CameraDirection::BACK);
            break;
        case 'd':
            Engine::Instance()->mainCamera->Move(Camera::CameraDirection::RIGHT);
            break;
        case 27:
            //glutLeaveMainLoop();
            exit(0);
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
            speedFactor += 1;
            break;
        case GLUT_KEY_DOWN:
            if (speedFactor > 1)
                speedFactor -= 1;
            break;
        case GLUT_KEY_LEFT:
            break;
        case GLUT_KEY_RIGHT:
            break;
        default:
            break;
    }
}

void GraphicalCore::Reshape(int w, int h)
{
    Engine::Instance()->mainCamera->SetViewport(w, h);
}

void GraphicalCore::Menu(int value)
{
    glutPostRedisplay();
}

void GraphicalCore::CreateMenu()
{
//    glutCreateMenu(GraphicalCore::Menu);
//    glutAttachMenu(GLUT_RIGHT_BUTTON);
}


void GraphicalCore::MouseButton(int button, int state, int x, int y)
{
    Engine::Instance()->mainCamera->SetPos(button, state, x, y);
}

void GraphicalCore::MouseMove(int x, int y)
{
    Engine::Instance()->mainCamera->Rotate(x, y);
}

GraphicalCore::GraphicalCore() = default;

GraphicalCore::~GraphicalCore() = default;