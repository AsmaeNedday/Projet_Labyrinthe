#ifndef WALL_H
#define WALL_H
#include <GL/gl.h>
#include <GL/glu.h>
#include <utility>
using namespace std;
using Point = pair<float,float>;
/**
 * @brief The Wall class has 4 principal fields : x and z are the start coordinates of the wall , its type :horizontal
 * or vetical wall , and its texture
 */
class Wall
{
public:
    enum Type {Horizontal,Vertical};
    Wall(float x,float z,Type type,GLuint texture_w);
    void display() const;
    Type getType(){return type;};
    Point getXlimits() const;
    Point getZlimits() const;
    float getX() const {return x;} ;
    float getZ() const {return z;};


private:

    float x,z;
    Type type;
    GLuint texture;
    //wall parameters
    float w_height = 40.0f;
    float w_width = 40.0f;
    float w_depth = 5.0f;

};

#endif // WALL_H
