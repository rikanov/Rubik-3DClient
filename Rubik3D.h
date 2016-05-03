class Cube3D
{ 
  int Colorize[3][3][3]={}; // to be valid exactly one of the coordinates must differ from 1
  
  int& /* sides */
    front = Colorize[1][1][2],
    up    = Colorize[1][2][1],
    right = Colorize[2][1][1],
    left  = Colorize[0][1][1],
    down  = Colorize[1][0][1],
    back  = Colorize[1][1][0];

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
  void graySides();
  
public:
  
  Cube3D(const int& x, const int& y, const int& z);
  void show() const;
};
  
class Rubik3D
{
  Cube3D * Cublets[3][3][3];
  
public:
  Rubik3D();
  ~Rubik3D();
  void rotate(const int& axisX, const int& axisY, const int& axisZ, const bool& inverse); // to be valid exactly one of the coordinates must differ from zero!
};