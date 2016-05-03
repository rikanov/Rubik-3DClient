
#include <string.h>
#include<GL/glut.h>
#include<stdio.h>
#include"Rubik3D.h"

#define FROM Cublets[X_from+1][Y_from+1][Z_from+1]
#define MOVE_TO Cublets[X_to+1][Y_to+1][Z_to+1]
  static GLfloat color[7][3]= 
  { // FURLDB
    {1.0,0.5,0.0}, //orange
    {0.0,0.0,1.0}, //blue
    {1.0,1.0,1.0}, //white
    {1.0,1.0,0.0}, //yellow
    {0.0,1.0,0.0}, //green
    {1.0,0.0,0.0}, //red
    {0.5,0.5,0.5}  // inner color: gray
  };
  static const int
    gray   =0,
    orange =1,
    blue   =2,
    white  =3,
    yellow =4,
    green  =5,
    red    =6;

    static inline int
    isZero(const int& z)
    {
      return z==0;
    }
    
    static inline int
    twist(const int & axis, const bool & inverse)
    {
      return axis*(inverse ? -1 : 1);
    }
void Cube3D::facets(const int& color_mark, const int& a1, const int& a2, const int& a3, const int& a4) const
{
  glColor3fv(color[color_mark]);
  glBegin(GL_POLYGON);
  glVertex3fv(Corners[a1]);
  glVertex3fv(Corners[a2]);
  glVertex3fv(Corners[a3]);
  glVertex3fv(Corners[a4]);
  glEnd();
  
  if(color_mark)
  {
    glColor3f(0,0,0); // black frame around the facets
    glLineWidth(3.0);
    glBegin(GL_LINE_LOOP);
    glVertex3fv(Corners[a1]);
    glVertex3fv(Corners[a2]);
    glVertex3fv(Corners[a3]);
    glVertex3fv(Corners[a4]);
    glEnd();
  }
}

Cube3D::Cube3D(const int& x, const int& y, const int& z):
  PosX(x),
  PosY(y),
  PosZ(z)
{
  for(int i=0;i<8;++i)
  {
    Corners[i][0]+=(x*2.0);
    Corners[i][1]+=(y*2.0);
    Corners[i][2]+=(z*2.0);
  }
  front = orange;
  up    = blue  ;
  right = white ;
  left  = yellow;
  back  = red   ;
  down  = green ;
  setSideColors();
}
  
void Cube3D::setSideColors()
{
  Front = (PosZ == 1) ? front : gray;
  Up    = (PosY == 1) ? up    : gray;
  Right = (PosX == 1) ? right : gray;
  Left  = (PosX ==-1) ? left  : gray;
  Back  = (PosY ==-1) ? back  : gray;
  Down  = (PosZ ==-1) ? down  : gray;
}

void Cube3D::show() const
{
  facets(Front,4,5,6,7);
  facets(Up   ,2,3,7,6);
  facets(Right,1,2,6,5);
  facets(Left ,0,4,7,3);    
  facets(Down ,0,1,5,4);
  facets(Back ,0,3,2,1);
}

//============================================

Rubik3D::Rubik3D()
{
  for(int x=-1;x<2;++x)
  {
    for(int y=-1;y<2;++y)
    {
      for(int z=-1;z<2;++z)
      {
	Cublets[x+1][y+1][z+1]=new Cube3D(x,y,z);
      }
    }
  }
}

Rubik3D::~Rubik3D()
{
  for(int x=-1;x<2;++x)
  {
    for(int y=-1;y<2;++y)
    {
      for(int z=-1;z<2;++z)
      {
	delete Cublets[x+1][y+1][z+1];
      }
    }
  }
}

void Rubik3D::rotate(const int& axisX, const int& axisY, const int& axisZ, const bool & inverse)
{
  for(int x=-isZero(axisX);x<=isZero(axisX);++x)
  {
    for(int y=-isZero(axisY);y<=isZero(axisY);++y)
    {
      for(int z=-isZero(axisZ);z<=isZero(axisZ);++z)
      {
	const int X_from=axisX+x;
	const int Y_from=axisY+y;
	const int Z_from=axisZ+z;
	;
	int X_to,Y_to,Z_to;
	if(twist(axisX, inverse)==1)
	{
	  X_to =   X_from;
	  Y_to =   Z_from;
	  Z_to = - Y_from;
	}
	else if(twist(axisY, inverse)==1)
	{
	  X_to = - Z_from;
	  Y_to =   Y_from;
	  Z_to =   X_from;
	}
	else if(twist(axisZ, inverse)==1)
	{
	  X_to =   Y_from;
	  Y_to = - X_from;
	  Z_to =   Z_from;
	}else if(twist(axisX, inverse)==-1)
	{
	  X_to =   X_from;
	  Y_to = - Z_from;
	  Z_to =   Y_from;
	}
	else if(twist(axisY, inverse)==-1)
	{
	  X_to =   Z_from;
	  Y_to =   Y_from;
	  Z_to = - X_from;
	}
	else if(twist(axisZ, inverse)==-1)
	{
	  X_to = - Y_from;
	  Y_to =   X_from;
	  Z_to =   Z_from;
	}
	
	// swap cube colors 
	
	if(axisX)
	{
	  MOVE_TO->up    = MOVE_TO->down = FROM->Right + FROM->Left ;
	  MOVE_TO->right = MOVE_TO->left = FROM->Up    + FROM->Down ;	  
	}
	else if(axisY)
	{
	  MOVE_TO->up   = MOVE_TO->down  = FROM->Front + FROM->Back ;
	  MOVE_TO->back = MOVE_TO->front = FROM->Up    + FROM->Down ;	  
	}
	else if(axisZ)
	{
	  MOVE_TO->right = MOVE_TO->left  = FROM->Front + FROM->Back ;
	  MOVE_TO->back  = MOVE_TO->front = FROM->Right + FROM->Left ; 	  
	}
      }
    }
  }
}
