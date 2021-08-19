//SPENCER MOORE
// This program is from the OpenGL Programming Guide. It shows a robot.
// This program is a modified version of the original source codes
// This program runs well under the settings you have done for the Assignment1. Please go
#define GL_SILENCE_DEPRECATION
#include <GLUT/glut.h>
#include <stdio.h>
#include <math.h>
#include <time.h>
#include <iostream>

#define BODY_WIDTH 2
#define BODY_HEIGHT 4
#define BODY_DEPTH 1



static int shoulderAngle = 0, elbowAngle = 0;
static int hipAngle = 0, kneeAngle = 0;
bool isWire = false;
float lx = 0.0f, lz = -1.0f , ly = 1.0f;
float x = 0.0f, z = 5.0f, y = 0.0f;
int arr[10];
int carr[10];
int flipper = 1;
int n;

float red;
float blue;
float green;
float angle = 0.0f;

float currentXPos = 5;
float currentZPos = -13;
float finalXPos = 5;
float finalZPos = -13;;
float bodyAngle = 0;

bool isPath = true;
int path_type = 0;
bool isAxis = false;
int counter = 0;
bool isAnimate = true;
bool bLegs = false;
bool animReverse = false;
int phase = 0;
int drag_x_origin;
int drag_y_origin;
int dragging = 0;

//--------------------------
//        SEED
//--------------------------
//Create 3 random rgb values and seed random
void seed()
{
    srand (time(0));
    red = static_cast <float> (rand()) / static_cast <float> (RAND_MAX);
    blue = static_cast <float> (rand()) / static_cast <float> (RAND_MAX);
    green = static_cast <float> (rand()) / static_cast <float> (RAND_MAX);
}

//--------------------------
//        INITIALIZE
//--------------------------
void init()
{
    seed();
    glShadeModel(GL_FLAT);
    glMatrixMode(GL_MODELVIEW);
    glLoadIdentity();
    gluLookAt(1, 2, 8, 0, 0, 0, 0, 1, 0);
}

//--------------------------
//        WIRE BOX
//--------------------------
//INPUT: HEIGHT WIDTH AND DEPTH OF THE BOX
void wireBox(GLdouble width, GLdouble height, GLdouble depth) {
    glPushMatrix();
    glScalef(width, height, depth);
    glutWireCube(1.0);
    glPopMatrix();
}

//--------------------------
//         SOLID BOX
//--------------------------
//INPUT: HEIGHT WIDTH AND DEPTH OF THE BOX
void solidBox(GLdouble width, GLdouble height, GLdouble depth) {
    glPushMatrix();
    glScalef(width, height, depth);
    glutSolidCube(1.0);
    glPopMatrix();
}
//--------------------------
//        DRAW AXIS
//--------------------------
void drawAxis()
{
    glPushMatrix();
    glBegin(GL_LINES);
    glColor3f(1, 0, 0); glVertex3f(0, 0, 0); glVertex3f(5, 0, 0);
    glColor3f(0, 1, 0); glVertex3f(0, 0, 0); glVertex3f(0, 5, 0);
    glColor3f(0, 0, 1); glVertex3f(0, 0, 0); glVertex3f(0, 0, 5);
    glEnd();
    glPopMatrix();
}

//--------------------------
//         DRAW BODY
//--------------------------
void drawBody()
{
    glColor3f(0.737, 0.561, 0.561);
    if(isWire ==  true)
        glColor3f(0.0, 0.0, 1.0);
    else
        glColor3f(red, green, blue);
    
    //HEAD
    glPushMatrix();
    glTranslatef(0.0, 3.0, 0.0);//(X, Y, Z)
    glRotatef((GLfloat)180, 0.0, 1.0, 0.0); //(3) then rotate shoulder

        //glColor3f(1.0, 0.0, 0.0); // R=1,G=0,B=0 -> red color
        
    if(isWire == true)
        glutWireSphere (1, 20, 20);
    else
        glutSolidSphere (1, 20, 20);
    
    glPopMatrix();
    
    //BODY
    glPushMatrix();
    if(isWire == true)
        
        wireBox(BODY_WIDTH, BODY_HEIGHT, BODY_DEPTH);
    else
        solidBox(BODY_WIDTH, BODY_HEIGHT, BODY_DEPTH);
    //RIGHT ARM
    glTranslatef(1.4, 1.7, 0.0); // (4) move to the right end of the upper body
    glRotatef((GLfloat)90, 0.0, 0.0, -1.0); //(3) then rotate shoulder
    glRotatef((GLfloat)shoulderAngle, 0.0, -1.0, 0.0); //(3) then rotate shoulder
    glTranslatef(1.0, 0.0, 0.0); // (2) shift to the right on the x axis to have the
    if(isWire == true)
        wireBox(2.0, 0.4, 1.0);
    else
        solidBox(2.0, 0.4, 1.0);
    
    glTranslatef(1.0, 0.0, 0.0); // (4) move to the right end of the upper arm
    glRotatef((GLfloat)elbowAngle, 0.0, -1.0, 0.0); // (3) rotate
    glTranslatef(1.0, 0.0, 0.0); // (2) shift to the right on the x axis to have the
    if(isWire == true)
        wireBox(2.0, 0.4, 1.0); // (1) draw the lower arm
    else
        solidBox(2.0, 0.4, 1.0);
    glPopMatrix();
    
    //LEFT ARM
    glPushMatrix();
    glTranslatef(-1.4, 1.7, 0.0); // (4) move to the right end of the upper body
    glRotatef((GLfloat)180, 0.0, 0.0, 1.0); //(3) then rotate shoulder
    glRotatef((GLfloat)90, 0.0, 0.0, 1.0); //(3) then rotate shoulder
    glRotatef((GLfloat)shoulderAngle, 0.0, 1.0, 0.0); //(3) then rotate shoulder
    glTranslatef(1.0, 0.0, 0.0); // (2) shift to the right on the x axis to have the
    if(isWire == true)
        wireBox(2.0, 0.4, 1.0); // (1) draw the lower arm
    else
        solidBox(2.0, 0.4, 1.0);
    glTranslatef(1.0, 0.0, 0.0); // (4) move to the right end of the upper arm
    //glRotatef((GLfloat)180, 0.0, 0.0, 1.0); //(3) then rotate shoulder
    glRotatef((GLfloat)elbowAngle, 0.0, -1.0, 0.0); // (3) rotate
    
    glTranslatef(1.0, 0.0, 0.0); // (2) shift to the right on the x axis to have the
    if(isWire == true)
        wireBox(2.0, 0.4, 1.0); // (1) draw the lower arm
    else
        solidBox(2.0, 0.4, 1.0);
    glPopMatrix();
    
    //RIGHT LEG
    glPushMatrix();
    glTranslatef(0.8, -2, 0.0); // (4) move to the right end of the upper body
    glRotatef((GLfloat)180, 0.0, 0.0, 1.0); //(3) then rotate shoulder
    glRotatef((GLfloat)90, 0.0, 0.0, 1.0); //(3) then rotate shoulder
    glRotatef((GLfloat)hipAngle, 0.0, 1.0, 0.0); //(3) then rotate shoulder
    glTranslatef(1.0, 0.0, 0.0); // (2) shift to the right on the x axis to have the
    if(isWire == true)
        wireBox(2.0, 0.4, 1.0); // (1) draw the lower arm
    else
        solidBox(2.0, 0.4, 1.0);
    glTranslatef(1.0, 0.0, 0.0); // (4) move to the right end of the upper arm
    //glRotatef((GLfloat)180, 0.0, 0.0, 1.0); //(3) then rotate shoulder
    glRotatef((GLfloat)kneeAngle, 0.0, 1.0, 0.0); // (3) rotate
    
    glTranslatef(1.0, 0.0, 0.0); // (2) shift to the right on the x axis to have the
    if(isWire == true)
        wireBox(2.0, 0.4, 1.0); // (1) draw the lower arm
    else
        solidBox(2.0, 0.4, 1.0);
    glPopMatrix();
    
    
    //LEFT LEG
    glPushMatrix();
    glTranslatef(-0.8, -2, 0.0); // (4) move to the right end of the upper body
    glRotatef((GLfloat)180, 0.0, 0.0, 1.0); //(3) then rotate shoulder
    glRotatef((GLfloat)90, 0.0, 0.0, 1.0); //(3) then rotate shoulder
    glRotatef((GLfloat)hipAngle, 0.0, -1.0, 0.0); //(3) then rotate shoulder
    glTranslatef(1.0, 0.0, 0.0); // (2) shift to the right on the x axis to have the
    if(isWire == true)
        wireBox(2.0, 0.4, 1.0); // (1) draw the lower arm
    else
        solidBox(2.0, 0.4, 1.0);
    glTranslatef(1.0, 0.0, 0.0); // (4) move to the right end of the upper arm
    //glRotatef((GLfloat)180, 0.0, 0.0, 1.0); //(3) then rotate shoulder
    glRotatef((GLfloat)kneeAngle, 0.0, 1.0, 0.0); // (3) rotate
    
    glTranslatef(1.0, 0.0, 0.0); // (2) shift to the right on the x axis to have the
    if(isWire == true)
        wireBox(2.0, 0.4, 1.0); // (1) draw the lower arm
    else
        solidBox(2.0, 0.4, 1.0);
    glPopMatrix();
}

//--------------------------
//         PATH
//--------------------------
//INPUT: TYPE OF PATH
void path(int type)//0 = straight | 1 = square
{
    if(type == 0) //[LINE PATH]
    {
        //~~~~~~~~DRAW PATH~~~~~~~~
        if(isPath == true)
        {
            glPushMatrix();
            glBegin(GL_LINES);
            glColor3f(0, 0, 1); glVertex3f(-3, -1, 0); glVertex3f(1.5, -1, 0);
            glEnd();
            glPopMatrix();
        }
        
        //--------MOVEMENT----------
        //MOVE FROM RIGHT TO LEFT
        if((currentXPos > 4.9 )&&(phase == 0))
        {
            bodyAngle = 270;
            phase = 1;
            finalXPos = -10;
            finalZPos = -13;
        }
        //MOVE FROM LEFT TO RIGHT
        if((currentXPos < -9.9)&&(phase == 1))
        {
            bodyAngle = 90;
            finalXPos = 5;
            finalZPos = -13;
            phase = 0;
        }
    }
    
    if(type == 1) // [SQUARE PATH]
    {
        //~~~~~~~~DRAW PATH~~~~~~~~
        if(isPath == true)
        {
            glPushMatrix();
            glBegin(GL_LINES);
            glColor3f(1, 0, 0); glVertex3f(-3, -1, 0); glVertex3f(1.5, -1, 0);
            glColor3f(1, 0, 0); glVertex3f(3, -3, 0); glVertex3f(1.5, -1, 0);
            glColor3f(1, 0, 0); glVertex3f(-3, -1, 0); glVertex3f(-4.5, -3, 0);
            glColor3f(1, 0, 0); glVertex3f(3, -3, 0); glVertex3f(-4.5, -3, 0);
            glEnd();
            glPopMatrix();
        }
        //--------MOVEMENT----------
        //MOVE FROM DOWN RIGHT TO UP RIGHT
        if((currentXPos > 4.9)&&(phase == 0))
        {
            bodyAngle = 180;
            phase = 1;
            finalXPos = 5;
            finalZPos = -13;
        }
        //MOVE FROM UP RIGHT TO UP LEFT
        if((currentZPos < -12.9)&&(phase == 1))
        {
            bodyAngle = 270;
            phase = 2;
            finalXPos = -10;
            finalZPos = -13;
        }
        //MOVE FROM UP LEFT TO DOWN LEFT
        if((currentXPos < -9.9)&&(phase == 2))
        {
            bodyAngle = 0;
            finalXPos = -10;
            finalZPos = -5;
            phase = 3;
        }
        //MOVE FROM DOWN LEFT TO DOWN RIGHT
        if((currentZPos > -5.1)&&(phase == 3))
        {
            bodyAngle = 90;
            phase = 0;
            finalXPos = 5;
            finalZPos = -5;
        }
    }
}

//--------------------------
//         ANIMATE
//--------------------------
void animate()
{
    //INCREMENT ANGLES
    if(animReverse == false)
    {
        if(elbowAngle <= 90)
            elbowAngle += 5;
        if(kneeAngle <= 90)
            kneeAngle += 5;
        if(shoulderAngle <= 90)
            shoulderAngle += 5;
        if(hipAngle <= 90)
            hipAngle += 5;
        else
            animReverse = true;
    }
    //DECREMEMNT ANGLES
    if(animReverse == true)
    {
        if(elbowAngle >= 0)
            elbowAngle -= 5;
        if(kneeAngle >= 0)
            kneeAngle -= 5;
        if(shoulderAngle >= -90)
            shoulderAngle -= 5;
        if(hipAngle >= -90)
            hipAngle -= 5;
        else
            animReverse = false;
    }
        
}

//--------------------------
//         DISPLAY
//--------------------------
void display()
{
    glMatrixMode(GL_MODELVIEW);
    glFlush();
}

//--------------------------
//      RENDER SCENE
//--------------------------
void renderScene(void)
{
    glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);
    glLoadIdentity();
    gluLookAt(x, 1.0f, z, x + lx, y + ly, z + lz, 0.0f,1.0f, 0.0f);
    
    // Draw the ground (a plane)
    glColor3f(0.9f, 0.9f, 0.9f);
    glBegin(GL_QUADS);
        glVertex3f(-100.0f, 0.0f, -100.0f);
        glVertex3f(-100.0f, 0.0f, 100.0f);
        glVertex3f(100.0f, 0.0f, 100.0f);
        glVertex3f(100.0f, 0.0f, -100.0f);
    glEnd();
    
    if(isAxis)
        drawAxis();
    if(isAnimate)
        animate();
    
    ++counter;

    glPushMatrix();
        path(path_type);
        glTranslatef(currentXPos, 0,currentZPos);
        glRotatef((GLfloat)bodyAngle, 0.0, 1.0, 0.0); //(3) then rotate shoulder
        drawBody();
    glPopMatrix();
    
    //ADJUST X POSITION
    if(currentXPos != finalXPos)
    {
        if(currentXPos < finalXPos)
            currentXPos += 0.1; //INCREMENT IF LESS THAN DESTINATION
        if(currentXPos > finalXPos)
            currentXPos -= 0.1; //DECREMENT IF GREATER THAN DESTINATION
    }
    //ADJUST Z POSITION
    if(currentZPos != finalZPos)
    {
        if(currentZPos < finalZPos)
            currentZPos += 0.1; //INCREMENT IF LESS THAN DESTINATION
        if(currentZPos > finalZPos)
            currentZPos -= 0.1; //DECREMENT IF GREATER THAN DESTINATION
    }
       
    glutSwapBuffers(); // for double buffer display
}

//--------------------------
//        RESHAPE
//--------------------------
//INPUT: VIEWPORT HEIGHT h AND WIDTH w
void reshape(GLint w, GLint h)
{
    glViewport(0, 0, w, h);
    glMatrixMode(GL_PROJECTION);
    glLoadIdentity();
    gluPerspective(65.0, GLfloat(w) / GLfloat(h), 1.0, 20.0);
}

//--------------------------
//          KEYS
//--------------------------
void keys(unsigned char key, int x, int y)
{
    if(key == '1') //TURN BODY WIREFRAME
    {
        isWire = true;
    }
    else if(key == '2') //TURN BODY SOLID
    {
        seed();
        isWire = false;
    }
    else if(key == '3') //TOGGLE AXIS
    {
        if(isAxis == false)
            isAxis = true;
        else
            isAxis = false;
    }
    else if(key == '4') //TOGGLE VISIBLE PATH
    {
        if(isPath == false)
            isPath = true;
        else
            isPath = false;
    }
    else if(key == 'r') //RESET BODY
    {
        phase = 0;
        currentXPos = 5;
        currentZPos = -13;
    }
    else if(key == 'a') //ANIMATION TOGGLE
    {
        if(isAnimate == false)
            isAnimate = true;
        else
            isAnimate = false;
    }
    else if(key == 'p') //CHANGE TYPE OF PATH
    {
        if(path_type == 0)
        {
            path_type = 1;
        }
        else if(path_type == 1)
        {
            path_type = 0;
        }
    }
    else if(key == 27) //ESCAPE KEY QUIT
    {
        exit(0);
    }
    glutPostRedisplay();
}
void mouse_click(int button, int state, int x, int y)
{
    if(button == GLUT_LEFT_BUTTON)
    {
        if(state == GLUT_DOWN)
        {
            dragging = 1; //BUTTON IS BEING HELD
            drag_x_origin = x;
            drag_y_origin = y;
        }
        else
            dragging = 0; //BUTTON RELEASED
    }
}
void mouse_move(int x, int y) {
    if(dragging) {
        ly += ( (y - drag_y_origin) / 100);
        lx += ( (x - drag_x_origin) / 100);
        drag_x_origin = x;
        drag_y_origin = y;
    }
}
int main(int argc, char** argv)
{
    seed();
    printf("\n\
-----------------------------------------------------------------------\n\
OpenGL Sample Program for a robot:\n\
- '1': set robot body to wireframe \n\
- '2': set robot body to solid \n\
- '3': toggle on off to draw axes \n\
- '4': toggle on off to draw path \n\
- 'r': reset robot to starting position \n\
- 'a': toggle on off to animation \n\
- 'p': change type of path \n\
- ESC to quit\n\
-----------------------------------------------------------------------\n");
    glutInit(&argc, argv);
    glutInitDisplayMode(GLUT_SINGLE | GLUT_RGB);
    glutInitWindowPosition(80, 80);
    glutInitWindowSize(1000, 1000);
    glutCreateWindow("Spencer Moore Assignment 3");
    glutDisplayFunc(display);
    glutReshapeFunc(reshape);
    glutIdleFunc(renderScene);
    glutMouseFunc(mouse_click);
    glutMotionFunc(mouse_move);
    glutKeyboardFunc(keys);
    init();
    glutMainLoop();
}


