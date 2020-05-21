#include <iostream>
#include "App.h"

#define RED 1
#define GREEN 2
#define BLUE 3
#define ORANGE 4
#define SHRINK 5
#define NORMAL 6
#define FILL 7
#define LINE 8

static App* singleton;

App::App(int argc, char** argv, int width, int height, const char* title): GlutApp(argc, argv, width, height, title){
    singleton = this;

    angle = 0;  //initialize rotation of triangle
    red = .9;  //set default color to white
    blue = .9;
    green = .9;

    camera = new Camera(0.0f, 5.0f, 0.0f, -1.0f, 0.0);
    deltaAngle = 0.0f;
    deltaMove = 0;

    snowMan = new SnowMan();

    createMenus();
    createPopupMenus();

}

void App::draw() const {
    //Clear color and depth buffers
    glClear(GL_COLOR_BUFFER_BIT| GL_DEPTH_BUFFER_BIT);

    //reset transformations
    glLoadIdentity();

    //set the camera
    gluLookAt(  camera->x, 1.0f, camera->z,
                camera->x+camera->lx, 1.0f, camera->z + camera->lz,
                0.0f, 1.0f, 0.0f);


    //Draw the ground **Make Ground Objects**
    glColor3f(red,blue,green);
    glBegin(GL_QUADS);
        glVertex3f(-100.0f, 0.0f, -100.0f);
        glVertex3f(-100.0f, 0.0f, 100.0f);
        glVertex3f(100.0f, 0.0f, 100.0f);
        glVertex3f(100.0f, 0.0f, -100.0f);
    glEnd();

    //Draw 36 SnowMen (just using Snoman object to draw 36)
    //When making game, each snowman should be its own game object **greate game object**
    for (int i = -3; i < 3; i++){
        for (int j=-3; j<3; j++){
            glPushMatrix();
            glTranslatef(i * 10.0, 0, j * 10.0);
            snowMan->Draw();
            glPopMatrix();
        }
    }

    glutSwapBuffers();
}

//infinite loop used to update current state
void App::idle(){

    //Clear color and depth buffers
    glClear(GL_COLOR_BUFFER_BIT| GL_DEPTH_BUFFER_BIT);

    //reset transformations
    glLoadIdentity();

    //set the camera
    gluLookAt(  camera->x, 1.0f, camera->z,
                camera->x+camera->lx, 1.0f, camera->z + camera->lz,
                0.0f, 1.0f, 0.0f);


    //Draw the ground **Make Ground Objects**
    glColor3f(red,green,blue);
    glBegin(GL_QUADS);
        glVertex3f(-100.0f, 0.0f, -100.0f);
        glVertex3f(-100.0f, 0.0f, 100.0f);
        glVertex3f(100.0f, 0.0f, 100.0f);
        glVertex3f(100.0f, 0.0f, -100.0f);
    glEnd();

    //Draw 36 SnowMen (just using Snoman object to draw 36)
    //When making game, each snowman should be its own game object **greate game object**
    for (int i = -3; i < 3; i++){
        for (int j=-3; j<3; j++){
            glPushMatrix();
            glTranslatef(i * 10.0, 0, j * 10.0);
            snowMan->Draw();
            glPopMatrix();
        }
    }
    glutSwapBuffers();

    //check if camera should move
    if (deltaMove){
        //move camera
        camera->Move(deltaMove);
    }

    //check if camera should turn
    if(deltaAngle){
        //turn camera
        angle += deltaAngle;
        camera->ChangeAngle(angle);
    }
}


//creating sub menus
void App::createPopupMenus(){
    //first menu
    singleton->shrinkMenu = glutCreateMenu(processShrinkMenu);
    glutAddMenuEntry("Shrink", SHRINK);
    glutAddMenuEntry("Normal", NORMAL);

    //another menu
    singleton->fillMenu = glutCreateMenu(processFillMenu);
    glutAddMenuEntry("Fill", FILL);
    glutAddMenuEntry("Line", LINE);

    //another menu
    singleton->colorMenu = glutCreateMenu(processColorMenu);
    glutAddMenuEntry("Red", RED);
    glutAddMenuEntry("Green", GREEN);
    glutAddMenuEntry("Blue", BLUE);
    glutAddMenuEntry("Orange", ORANGE);

    //main menu that contains the other menus as entries
    singleton->mainMenu = glutCreateMenu(processMainMenu);
    glutAddSubMenu("Polygon Mode", singleton->fillMenu);
    glutAddSubMenu("Color", singleton->colorMenu);
    glutAddSubMenu("ShrinkMenu", singleton->shrinkMenu);

    glutAttachMenu(GLUT_RIGHT_BUTTON);
}

//callback for main menu
void App::processMainMenu(int option){

}

//callback for shrink menu
void App::processShrinkMenu(int option){
    changeColor(option);
}

//callback for fill menu
void App::processFillMenu(int option){

}

void App::createMenus(){
    int menu = glutCreateMenu(processColorMenu);

    //Add entries to menu
    glutAddMenuEntry("Red", RED);
    glutAddMenuEntry("Green", GREEN);
    glutAddMenuEntry("Blue", BLUE);
    glutAddMenuEntry("Orange", ORANGE);

    //Atttach the menu to the right button
    glutAttachMenu(GLUT_RIGHT_BUTTON);

}


//call back for color menu
void App::processColorMenu(int option){
    changeColor(option);
}


//changes color of floor
void App::changeColor(int option){
    switch (option)
    {
    case RED:
        singleton->red = 1.0f;
        singleton->blue = 0.0f;
        singleton->green = 0.0f;
        break;
    case BLUE:
        singleton->red = 0.0f;
        singleton->blue = 1.0f;
        singleton->green = 0.0f;
        break;
    case GREEN:
        singleton->red = 0.0f;
        singleton->blue = 0.0f;
        singleton->green = 1.0f;
        break;
    case ORANGE:
        singleton->red = 1.0f;
        singleton->blue = 0.5f;
        singleton->green = 0.5f;
        break;
    default:
        break;
    }
}

//Used for holding down mouse and "dragging" the mouse
void App::drag(float x, float y){
    deltaAngle = (x - xOrigin) * camera->GetLookSpeed();

    camera->ChangeAngle(angle + deltaAngle);
}

//Movement
void App::keyDown(unsigned char key, float x, float y){
    switch(key){
        case 27:    //exit
            exit(0);
            break;
        case 'f':  //full screen
            toggleFullScreen();
            break;
        //WASD camera movement    
        case 'a':   
            deltaAngle = -0.01f;
            break;
        case 'd':
            deltaAngle = 0.01f;
            break;
        case 'w':
            deltaMove = 0.5f;
            break;
        case 's':
            deltaMove = -0.5f;
            break;        
        default:
            break;
    }
}

void App::keyUp(unsigned char key, float x, float  y){
    switch (key)
    {
        case 'a':
        case 'd':
            deltaAngle = 0.0f;
            break;
        case 'w':
        case 's':
            deltaMove = 0;
            break;        
        default:
            break;
    }
}

//This is not working (something with input to computer.. working in vm)
void App::specialKeyDown(unsigned char key, float x, float y){
    switch (key)
    {
    case GLUT_KEY_LEFT:
        angle -= 0.01f;
        camera->ChangeAngle(angle);
        break;
    case GLUT_KEY_RIGHT:
        angle += 0.01f;
        camera->ChangeAngle(angle);
        break;
    case GLUT_KEY_UP:
        camera->MoveUp();
        break;
    case GLUT_KEY_DOWN:
        camera->MoveDown();
        break;
    default:
        break;
    }
    redraw();
}

void App::leftMouseDown(float x, float y){
    xOrigin = x;
}

void App::leftMouseUp(float x, float y){
    xOrigin = -1;

    deltaAngle = 0;
}

App::~App(){    
    std::cout << "Exiting..." << std::endl;
}
