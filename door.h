#ifndef DOOR_H
#define DOOR_H
#include <GL/gl.h>
#include <GL/glu.h>
#include <utility>
#include <QLine>
using namespace std;
using Point = pair<float,float>;
#include "wall.h"
/**
 * @brief The Door class has three principal fields : x,z : coordinates of the door and its texture
 */

class Door
{
public:
    //height and width are height and width of the maze
    Door(int height, int width,GLuint texture);
    void setLine(QLineF* line){this->line = line;};
    void display() const;
    void setTexture(GLuint texture_d){texture=texture_d;}
    bool IsEqual(Wall& wall){return (this->x == wall.getX()  && this->z == wall.getZ() && this->type == wall.getType());};
    QLineF* getLine() {return line;};
private:
    float x,z;
    Wall::Type type;
    QLineF* line;
    GLuint texture;
    //walls parameters
    float w_height = 40.0f;
    float w_width = 40.0f;
    float w_depth = 5.0f;

};

#endif // DOOR_H
