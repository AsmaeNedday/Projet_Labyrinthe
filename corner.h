#ifndef PILLAR_H
#define PILLAR_H
#include <GL/gl.h>
#include <GL/glu.h>
#include <utility>
using namespace std;
using Point = pair<float,float>;
/**
 * @brief The Corner class represents the corner of the wall ,it has three principal fields : x,z : coordinates
 * of the corner , and texture of the corner.
 */
class Corner
{
public:
    Corner(float x,float z,GLuint texture);
    void display() const;
    float getX() const {return x;} ;
    float getZ() const {return z;};
    Point getXlimits() const {return make_pair(x,x + w_depth);};
    Point getZlimits() const {return make_pair(z,z+ w_depth);};


private:
    float x;
    float z;
    GLuint texture;
    //walls parameters
    float w_height = 40.0f;
    float w_width = 40.0f;
    float w_depth = 5.0f;
};

#endif // PILLAR_H
