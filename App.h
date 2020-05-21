#ifndef App_h
#define App_h
#include <vector>
#include <math.h>

#include "GlutApp.h"
#include "Rect.h"
#include "SnowMan.h"
#include "Camera.h"



class App: public GlutApp {
    float angle;    //this needs to be part of triangle object
    float red;
    float green;
    float blue;

    //menus
    int mainMenu;
    int shrinkMenu;
    int colorMenu;
    int fillMenu;

    Camera* camera;
    float deltaMove;
    float deltaAngle;
    int xOrigin = -1;

    SnowMan* snowMan;

public:
    
    App(int argc, char** argv, int width, int height, const char* title);

    static void createPopupMenus();

    static void createMenus();

    static void changeColor(int option);

    static void processMainMenu(int option);

    static void processColorMenu(int option);

    static void processShrinkMenu(int option);
    
    static void processFillMenu(int option);
    
    void draw() const;

    void leftMouseDown(float x, float y);

    void leftMouseUp(float x, float y);

    void drag(float x, float y);

    void mouseButton(int button, int state, int x, int y);
    
    void mouseMove(int x, int y);

    void keyDown(unsigned char key, float x, float y);

    void keyUp(unsigned char key, float x, float  y);

    void specialKeyDown(unsigned char key, float x, float y);
    
    void drag(float, float) const;

    void idle();
    
    ~App();
};

#endif
