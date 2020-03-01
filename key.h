#ifndef KEY_H
#define KEY_H
#include <GL/gl.h>
#include <GL/glu.h>
#include <utility>
#include <math.h>
using namespace std;
using Point = pair<float,float>;

/**
 * @brief The Key class has two principal fields : its coordinates and its texture
 */
class Key
{
public:
    Key(int x, int z,GLuint texture);
    void display(float time) const;
    Point getCoordinates() const {return coordinates;};
    int getX() const {return (coordinates.second - w_depth - 0.5*w_width)/(w_depth +w_width);};
    int getZ() const {return (coordinates.first - w_depth- 0.5*w_width)/(w_depth + w_width);};


private:
    // coordinates of the key "the sphere with the logo of telecom"
    Point coordinates;
    GLuint texture;
    //wall parameters
    float w_height = 40.0f;
    float w_width = 40.0f;
    float w_depth = 5.0f;

};

#endif // KEY_H
