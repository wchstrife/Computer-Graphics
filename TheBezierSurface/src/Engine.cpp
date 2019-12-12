

#include <sstream>
#include "Engine.hpp"

Engine *Engine::instance = nullptr;

GLfloat Engine::bezier_points[5][5][3] = {
        {{ -1.5, 2.0, -1.0}, { -0.5, 1.1, 1.5}, {0.0, 2.5, -2.5}, {0.5, 1.5, 0.5}, {2.5, 1.5, -0.5}},
        {{ -1.5, 0.5, 1.0}, { -0.5, 0.5, -0.5}, {0.0, 1.5, -0.5}, {0.5, 0.5, -1.5}, {3.0, 0.5, -0.5}},
        {{ -1.5, 2.0, 0.0}, { -0.5, 0.0, -1.0}, {0.15, 1.0, -2.0}, {0.5, 0.0, -1.0}, {1.0, 0.5, -0.5}},
        {{ -1.0, -1.0, -0.5}, { -0.5, 0.0, 3.0}, {0.0, -0.5, -0.5}, {0.5, -0.5, 0.75}, {2.0, -0.5, -0.5}},
        {{ -1.5, -1., -0.5}, { -0.5, -1.5, -0.5}, {0.0, -2.0, -0.5}, {0.5, -1.0, 1.5}, {2.5, -1.25, -0.5}}
};

int Engine::ptr[2] = {0, 0};
int Engine::smoothness[2] = {3, 15};
int Engine::current_texture = 0;
bool Engine::grid = false;
bool Engine::text = true;

Engine::~Engine() = default;

Engine::Engine()
{
    InitTextures();
    InitLights();
    glEnable(GL_MAP2_TEXTURE_COORD_2);
    glEnable(GL_MAP2_VERTEX_3);
    glEnable(GL_DEPTH_TEST);
    glEnable(GL_AUTO_NORMAL);
    glEnable(GL_NORMALIZE);
    glShadeModel(GL_SMOOTH);
}

void Engine::InitLights()
{
    GLfloat light_ambient[] = { 1.0, 1.0, 1.0, 1.0 };
    GLfloat light_diffuse[] = { 1.0, 1.0, 1.0, 1.0 };
    GLfloat light_specular[] = {1.0, 1.0, 1.0, 1.0 };
    GLfloat light_position[] = {5.0, 5.5, -5.0, 1.0 };
    GLfloat mat_diffuse[] = {0.9, 0.9, 0.9, 1.0};
    GLfloat mat_specular[] = {1.0, 1.0, 1.0, 1.0};
    GLfloat mat_shininess[] = {120.0};

    glLightfv(GL_LIGHT0, GL_AMBIENT, light_ambient);
    glLightfv(GL_LIGHT0, GL_DIFFUSE, light_diffuse);
    glLightfv(GL_LIGHT0, GL_SPECULAR, light_specular);
    glLightfv(GL_LIGHT0, GL_POSITION, light_position);
    glMaterialfv(GL_FRONT_AND_BACK, GL_DIFFUSE, mat_diffuse);
    glMaterialfv(GL_FRONT_AND_BACK, GL_SPECULAR, mat_specular);
    glMaterialfv(GL_FRONT_AND_BACK, GL_SHININESS, mat_shininess);

}
void Engine::InitTextures()
{
    std::vector<std::string> *names = new std::vector<std::string>({TEXTURES_NAMES});
    textures = new std::vector<GLuint>();
    for (auto &s : *names)
        textures->push_back(SOIL_load_OGL_texture(s.c_str(), SOIL_LOAD_AUTO, SOIL_CREATE_NEW_ID, SOIL_FLAG_NTSC_SAFE_RGB | SOIL_FLAG_MULTIPLY_ALPHA));

    glBindTexture(GL_TEXTURE_2D, (*textures)[current_texture]);
    glTexEnvf(GL_TEXTURE_ENV, GL_TEXTURE_ENV_MODE, GL_MODULATE);
    glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_WRAP_S, GL_ADD);
    glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_WRAP_T, GL_ADD);
    glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MAG_FILTER, GL_NEAREST);
    glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MIN_FILTER, GL_NEAREST);
}

void Engine::RenderBitmapString(float x, float y, void *font, std::string s)
{
    const char *c;

    glRasterPos2f(x, y);
    for (c = s.c_str(); *c != '\0'; c++)
        glutBitmapCharacter(font, *c);
}

void Engine::PrintInformation()
{
    std::stringstream fmt;

    glColor3f(1.0, 1.0, 1.0);
    fmt << "You are currently on the control point (" << Engine::ptr[0] << ", " << Engine::ptr[1] << ")" << \
    " with the values (" << Engine::bezier_points[Engine::ptr[0]][Engine::ptr[1]][0] << ", " << \
    Engine::bezier_points[Engine::ptr[0]][Engine::ptr[1]][1] << ", " << \
    Engine::bezier_points[Engine::ptr[0]][Engine::ptr[1]][2] <<   ") "  << std::endl;
    RenderBitmapString(-0.95f, -0.75f, GLUT_BITMAP_TIMES_ROMAN_24, fmt.str()); fmt.str("");
    fmt << "There are 5x5 control points. Current smoothness (u, v) = (" << Engine::smoothness[0] << ", " << Engine::smoothness[1] << ")";
    fmt << "There are 5x5 control points. Current smoothness (u, v) = (" << Engine::smoothness[0] << ", " << Engine::smoothness[1] << ")";
    RenderBitmapString(-0.95f, -0.80f, GLUT_BITMAP_TIMES_ROMAN_24, fmt.str());fmt.str("");
    fmt.str("");
    fmt << "Press Q/A, W/S, E/D to modify respectively the x, y or z values\n";
    RenderBitmapString(-0.95f, -0.85f, GLUT_BITMAP_TIMES_ROMAN_24, fmt.str());fmt.str("");
    fmt.str("");
    fmt << "Press 0 to show the Grid. Press 1 or 2 to change the texture image";
    RenderBitmapString(-0.95f, -0.90f, GLUT_BITMAP_TIMES_ROMAN_24, fmt.str());
    fmt.str("");
    fmt << "Press R/F, T/G to change the smoothness of u and v. Press H to hide the text. ";
    RenderBitmapString(-0.95f, -0.95f, GLUT_BITMAP_TIMES_ROMAN_24, fmt.str());
}

void Engine::InitUpdate()
{
    glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);
}

void Engine::EndUpdate()
{
    glDisable(GL_LIGHTING);
    glDisable(GL_LIGHT0);
    glDisable(GL_TEXTURE_2D);
}

void Engine::Update()
{
    static GLfloat pts[2][2][2] = {{{0.0, 0.0}, {1.0, 0.0}},
                                   {{0.0, 1.0}, {1.0, 1.0}}};

    glLoadIdentity();
    if (text)
        //PrintInformation();
    glEnable(GL_LIGHTING);
    glEnable(GL_LIGHT0);
    glScalef(0.3f, 0.3f, 1.0f);
    if (!grid)
    {
        glEnable(GL_TEXTURE_2D);
        glBindTexture(GL_TEXTURE_2D, (*textures)[current_texture]);
        glMap2f(GL_MAP2_TEXTURE_COORD_2, 0, 1, 2, 2,
                0, 1, 4, 2, &pts[0][0][0]);
    }
    glMap2f(GL_MAP2_VERTEX_3, 0, 1, smoothness[0], 5,
            0, 1, smoothness[1], 5, &bezier_points[0][0][0]);
    glMapGrid2f(25, 0.0, 1.0, 25, 0.0, 1.0);
    glColor3f(1.0, 1.0, 1.0);
    glEvalMesh2(grid ? GL_LINE : GL_FILL, 0, 25, 0, 25);
}

