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
#include <string.h>
#include"Rubik3D.h"

#define OUT(x) std::cout<<x<<' ';
#define OUT_(x) std::cout<<x<<std::endl;
#define FROM Cublets[X_from+1][Y_from+1][Z_from+1]
#define MOVE_TO Cublets[X_to+1][Y_to+1][Z_to+1]
  static GLfloat color[7][3]= 
  { // FURLDB
    {0.5,0.5,0.5}, // inner color: gray
    {1.0,0.5,0.0}, //orange
    {0.0,0.0,1.0}, //blue
    {1.0,1.0,1.0}, //white
    {1.0,1.0,0.0}, //yellow
    {0.0,1.0,0.0}, //green
    {1.0,0.0,0.0}  //red
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
    
    static inline int
    reverter(const bool & R)
    {
      return R ? -1 : 1;
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
  
  glColor3f(0,0,0); // black frame around the facets
  glLineWidth(2.0);
  glBegin(GL_LINE_LOOP);
  glVertex3fv(Corners[a1]);
  glVertex3fv(Corners[a2]);
  glVertex3fv(Corners[a3]);
  glVertex3fv(Corners[a4]);
  glEnd();
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
  Down  = (PosY ==-1) ? down  : gray;
  Back  = (PosZ ==-1) ? back  : gray;
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

Rubik3D::Rubik3D(const int & H):
  axisX(0),
  axisY(0),
  axisZ(0),
  inverse(false),
  theta(0),
  haste(H)
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

void Rubik3D::rotate()
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
	  MOVE_TO->left  = FROM->Left;
	  MOVE_TO->right = FROM->Right;
	  MOVE_TO->up    = MOVE_TO->down = FROM->Front + FROM->Back ;
	  MOVE_TO->front = MOVE_TO->back = FROM->Up    + FROM->Down ;	  
	}
	else if(axisY)
	{
	  MOVE_TO->down = FROM->Down;
	  MOVE_TO->up   = FROM->Up;
	  MOVE_TO->left = MOVE_TO->right = FROM->Front + FROM->Back ;
	  MOVE_TO->back = MOVE_TO->front = FROM->Left  + FROM->Right ;	  
	}
	else if(axisZ)
	{
	  MOVE_TO->back  = FROM->Back;
	  MOVE_TO->front = FROM->Front;
	  MOVE_TO->right = MOVE_TO->left = FROM->Up   + FROM->Down ;
	  MOVE_TO->up    = MOVE_TO->down = FROM->Right + FROM->Left ; 	  
	}
      }
    }
  }
  setColors();
}

void Rubik3D::setColors()
{
  for(int x=-1;x<2;++x)
  {
    for(int y=-1;y<2;++y)
    {
      for(int z=-1;z<2;++z)
      {
	Cublets[x+1][y+1][z+1]->setSideColors();
      }
    }
  }
}

void Rubik3D::showCube() 
{
  for(int x=-1;x<2;++x)
  {
    for(int y=-1;y<2;++y)
    {
      for(int z=-1;z<2;++z)
      {
	if( theta==0 ||
	  ( axisX && (axisX!=x)) ||
	  ( axisY && (axisY!=y)) ||
	  ( axisZ && (axisZ!=z))
	)
	{
	  Cublets[x+1][y+1][z+1]->show();
	}
      }
    }
  }
  
  // Rotate sides
  
 
  if(theta)
  {
    glRotatef(reverter(inverse)*(90-theta),-axisX,-axisY,-axisZ);
    for(int x=-1;x<2;++x)
    {
      for(int y=-1;y<2;++y)
      {
	for(int z=-1;z<2;++z)
	{
	  if( 
	    ( axisX && (axisX==x)) ||
	    ( axisY && (axisY==y)) ||
	    ( axisZ && (axisZ==z))
	  )
	  {
	    Cublets[x+1][y+1][z+1]->show();
	  }
	}
      }
    }
    if(theta == haste)
    {
      rotate();
      axisX=0;
      axisY=0;
      axisZ=0;
    }
    theta -= haste;
  }
}

void Rubik3D::twister(const int & X, const int & Y, const int & Z, const bool & inv)
{
  if(theta)
  {
    return; // waiting for finishing former action
  }
  axisX=X;
  axisY=Y;
  axisZ=Z;
  inverse=inv;
  theta=90;
}
