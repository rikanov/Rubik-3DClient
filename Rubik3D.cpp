
#include <string.h>
#include<GL/glut.h>
#include<stdio.h>
#include"Rubik3D.h"

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
  graySides();
}
  
void Cube3D::graySides()
{
  front = (PosZ == 1) ? front : gray;
  up    = (PosY == 1) ? up    : gray;
  right = (PosX == 1) ? right : gray;
  left  = (PosX ==-1) ? left  : gray;
  back  = (PosY ==-1) ? back  : gray;
  down  = (PosZ ==-1) ? down  : gray;
}

void Cube3D::show() const
{
  facets(front,4,5,6,7);
  facets(up   ,2,3,7,6);
  facets(right,1,2,6,5);
  facets(left ,0,4,7,3);    
  facets(down ,0,1,5,4);
  facets(back ,0,3,2,1);
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
	const int X_coord=axisX+x;
	const int Y_coord=axisY+y;
	const int Z_coord=axisZ+z;
	;
      }
    }
  }
}