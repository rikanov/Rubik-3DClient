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

class Cube3D
{ 
  friend class Rubik3D;
  int Colorize[3][3][3]={}; // to be valid exactly one of the coordinates must differ from 1
  
  int& /* side colours references */
    Front = Colorize[1][1][2],
    Up    = Colorize[1][2][1],
    Right = Colorize[2][1][1],
    Left  = Colorize[0][1][1],
    Down  = Colorize[1][0][1],
    Back  = Colorize[1][1][0];  
    
  int /* sides temporarily colours */
    front,
    up,
    right,
    left,
    down,
    back;


  const int PosX,PosY,PosZ;
  GLfloat Corners[8][3]=
  { 
    {-1.0,-1.0,-1.0},
    { 1.0,-1.0,-1.0},
    { 1.0, 1.0,-1.0},
    {-1.0, 1.0,-1.0}, 
    {-1.0,-1.0, 1.0},
    { 1.0,-1.0, 1.0},
    { 1.0, 1.0, 1.0},
    {-1.0, 1.0, 1.0}
  };
    
  void facets(const int & color_mark,const int & a1,const int & a2,const int & a3,const int & a4) const;
  void setSideColors();
  
public:
  
  Cube3D(const int& x, const int& y, const int& z);
  void show() const;
};
  
class Rubik3D
{
  Cube3D * Cublets[3][3][3];
  int axisX, axisY, axisZ;
  bool inverse;
  int theta;
  
public:
  Rubik3D();
  ~Rubik3D();
  void twister(const int& X, const int& Y, const int& Z, const bool& inv);
  void rotate(); // to be valid exactly one of the coordinates must differ from zero!
  void setColors();
  void showCube();  
};