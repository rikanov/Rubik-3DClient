#ifdef __APPLE__
  #include <OpenGL/gl.h>
  #include <OpenGL/glu.h>
  #include <GLUT/glut.h>
#else
  #ifdef _WIN32
    #include <windows.h>
  #endif
  #include <GL/gl.h>
  #include <GL/glu.h>
  #include <GL/glut.h>
#endif

#include <iostream>
#include "Rubik3D.h"

Rubik3D rubik;

GLfloat p=0.0,q=0.0,r=0.0;
GLfloat ScreenColor[]={0.0,0.0,0.0};
bool moving=false;
int beginx=0, beginy=0;

void makeMenu()
{
  glutAddMenuEntry("Up                    U   ", 1);
  glutAddMenuEntry("Up Inv.           shift+U", 2);
  glutAddMenuEntry("Right                 R   ", 3);
  glutAddMenuEntry("Right Inv.       shift+R", 4);
  glutAddMenuEntry("Front                 F   ", 5);
  glutAddMenuEntry("Front Inv.       shift+F", 6);
  glutAddMenuEntry("Left                    L   ", 7);
  glutAddMenuEntry("Left Inv.          shift+L", 8);
  glutAddMenuEntry("Back                  B    ", 9);
  glutAddMenuEntry("Back Inv.       shift+B",10);
  glutAddMenuEntry("Down                 D   ",11);
  glutAddMenuEntry("Down Inv       shift+D",12);
  glutAddMenuEntry("Ask server...  shift+A",13);
  glutAddMenuEntry("Exit",14);
}
void mouse(int btn,int state,int x,int y)
{
  if(btn==GLUT_LEFT_BUTTON && state==GLUT_DOWN)
  {
    moving = 1;
    beginx = x;
    beginy = y;
  }
}
void motion(int x, int y)
{
  if (moving) 
  {
    q+= (x - beginx);
    beginx = x;
    p+= (y - beginy);
    beginy=y;
    glutPostRedisplay();
  }
}
void myreshape(int w,int h)
{
    glViewport(0,0,w,h);
    glMatrixMode(GL_PROJECTION);
    glLoadIdentity();
    if (w <= h)
    {
      glOrtho(-10.0,10.0,-10.0*(GLfloat)h/(GLfloat)w, 10.0*(GLfloat)h/(GLfloat)w,-10.0,10.0);
    }
    else
    {
      glOrtho(-10.0*(GLfloat)w/(GLfloat)h, 10.0*(GLfloat)w/(GLfloat)h,-10.0,10.0,-10.0,10.0);
      glMatrixMode(GL_MODELVIEW);
    }
}
void display()
{
    glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);
    glLoadIdentity();

    glColor3fv(ScreenColor);
 
    glPushMatrix();
    glRotatef(25.0+p,1.0,0.0,0.0);
    glRotatef(-30.0+q,0.0,1.0,0.0);
    glRotatef(0.0+r,0.0,0.0,1.0);   
    
    rubik.showCube();
    
    glFlush();
    glutSwapBuffers();
}

void keyboard(unsigned char key, int, int)
{
  int x=0,y=0,z=0;
  bool inv=(key & 32)==0;
  key |= 32;
  switch(key)
  {
    case 'l':
      x = -1;
      break;
    case 'r':
      x = 1;
      break;
    case 'd':
      y =-1;
      break;
    case 'u':
      y = 1;
      break;
    case 'b':
      z =-1;
      break;
    case 'f':
      z = 1;
      break;
    default:
      return;
  }
  rubik.twister(x,y,z,inv);
}

void mymenu(int z)
{
  ;
}
int main(int argc, char **argv) {
  glutInit(&argc, argv);
  glutInitDisplayMode (GLUT_DOUBLE | GLUT_RGB | GLUT_DEPTH);
  glutInitWindowSize (640, 600);
  glutCreateWindow ("RUBIK'S CUBE");
  myreshape(640,640);
  glutReshapeFunc (myreshape);
  glutIdleFunc(display);
  glutMouseFunc(mouse);
  glutMotionFunc(motion);
  glutCreateMenu(mymenu);
  makeMenu();
  glutAttachMenu(GLUT_RIGHT_BUTTON);
  glutKeyboardFunc(keyboard);
  glutDisplayFunc (display);
  glEnable(GL_DEPTH_TEST);
  glutMainLoop();
  return 0;
}
