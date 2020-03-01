#ifndef MAZE_H
/** An implementation of Prim's algorithm for generating mazes.
 * from <http://weblog.jamisbuck.org/2011/1/10/maze-generation-prim-s-algorithm>
**/

#define MAZE_H
#include <vector>
#include <list>
#include "cell.h"
#include "wall.h"
#include "key.h"
#include "door.h"
#include "area.h"
#include "corner.h"
#include <iostream>
#include "myglwidget.h"



/**
 *the class maze is reponsible of generating the random maze
 */
class MyGLWidget;
class Maze
{
//maze2D dimensions
const int MAZE2D_SIZE=17.0f;
const int MAZE2D_POSITION=45.0f;

private:

    MyGLWidget* myGlWidget_;
    void addFrontier(Point p,list<Point> & frontier);
    void mark(Point p,list<Point> & frontier);
    list<Point> neighbors(Point p);
    Cell::Direction direction(Point f, Point t);
    //texture
    GLuint texture_wall,texture_door,texture_key,texture_ground,texture_sky,texture_corner;
    vector<vector<Cell>> grid_;
    vector<Wall*> walls_;
    vector<Corner*> corners_;
    vector<QLineF*> lines_;
    Key* key_ = 0;
    Area* sky_ = 0;
    Area* ground_ = 0;
    Door* door_ = 0;
    int width_;
    int height_;
    bool keyFound = false;
    bool doorFound = false;
    //wall parameters
    float w_height = 40.0f;
    float w_width = 40.0f;
    float w_depth = 5.0f;

    int height;
    int width;

public:
    Maze(MyGLWidget* parent,int width,int height);
    ~Maze();
    void initialize();
    void display(float time) const;
    void generate();
    bool IsKeyFound(){return keyFound;};
    bool IsDoorFound(){return doorFound;};
    vector<QLineF*>* getLines(){return &lines_;};
    int getKeyX() {return key_->getX();};
    int getKeyZ(){return key_->getZ();};
    Door* getDoor(){return door_;};
    bool check(float camX, float camZ, float rotation, float translation,int direction);
    int getWidth(){return width;}
    int getHeight(){return height;}

};

#endif // MAZE_H
