/** An implementation of Prim's algorithm for generating mazes.
 * from <http://weblog.jamisbuck.org/2011/1/10/maze-generation-prim-s-algorithm>
**/

#include<iostream>
#include <ctime>
#include "myglwidget.h"
#include "maze.h"
#include "corner.h"
#include "area.h"
#include <iostream>

#define PI 3.14159265
using namespace std;

//constructor
Maze::Maze(MyGLWidget* parent,int width, int height)
    : grid_(height,vector<Cell>(width)), width_(width), height_(height)
{
    //initialise the field myGlWidget
    myGlWidget_ = parent;
    //height and width of the maze
    this->height=height;
    this->width=width;
    //initialise the door of the maze
    door_ = new Door(height,width,myGlWidget_ ->getDoorTexture());
}

//destructor
Maze::~Maze()
{
    //delete differents created objects to free memory
    delete key_;
    delete sky_;
    delete door_;
    delete ground_;
    for (vector<Wall*>::iterator it = walls_.begin(); it != walls_.end(); ++it){
        delete *it;
    }
    for (vector<Corner*>::iterator it = corners_.begin(); it != corners_.end(); ++it){
        delete *it;
    }
    for (vector<vector<Cell>>::iterator it = grid_.begin(); it != grid_.end(); ++it){
        (*it).clear();
    }

    for (vector<QLineF*>::iterator it = lines_.begin(); it != lines_.end(); ++it){
        delete (*it);
    }
    lines_.clear();
    walls_.clear();
    corners_.clear();
    grid_.clear();


}

void Maze::initialize()
{
    grid_=vector<vector<Cell>>(height_,vector<Cell>(width_));
    delete key_;
    delete sky_;
    delete ground_;
    delete door_;
    walls_.clear();
    corners_.clear();
    grid_.clear();
    lines_.clear();
    door_ = new Door(height_,width_,texture_door);
    generate();
    //set booleans to false
    keyFound = false;
    doorFound = false;
}

void Maze::addFrontier(Point p, list<Point> &frontier)
{
    if (p.first>=0 && p.second>=0 && p.second<height_ && p.first<width_
            && grid_[p.second][p.first].getValue()==0) {
        grid_[p.second][p.first].setValue(Cell::FRONTIER);
        frontier.push_back(p);
    }
}


void Maze::mark(Point p, list<Point> &frontier)
{
    grid_[p.second][p.first].setValue(Cell::MARKED);
    addFrontier(Point(p.first-1, p.second),frontier);
    addFrontier(Point(p.first+1, p.second),frontier);
    addFrontier(Point(p.first, p.second-1),frontier);
    addFrontier(Point(p.first, p.second+1),frontier);
}


list<Point> Maze::neighbors(Point p)
{
    list<Point> n;
    if (p.first>0 && grid_[p.second][p.first-1].getValue()==Cell::MARKED)
        n.push_back(Point(p.first-1, p.second));
    if (p.first+1<width_ && grid_[p.second][p.first+1].getValue()==Cell::MARKED)
        n.push_back(Point(p.first+1, p.second));
    if (p.second>0 && grid_[p.second-1][p.first].getValue()==Cell::MARKED)
        n.push_back(Point(p.first, p.second-1));
    if (p.second+1<height_ && grid_[p.second+1][p.first].getValue()==Cell::MARKED)
        n.push_back(Point(p.first, p.second+1));
    return n;
}

/**
    @param two points
    @return a Cell:cell
*/
Cell::Direction Maze::direction(Point f, Point t)
{
    if (f.first<t.first) return Cell::E;
    else if (f.first>t.first) return Cell::W;
    else if (f.second<t.second) return Cell::S;
    else return Cell::N;
}

//function to check the position of the user and compare it to the position of walls in order to not
//cross walls
/**
     @param coordinates of cam , rotation and translation and the direction
    @return boolean flag to indicate if you can move or there is an obstacle
*/
bool Maze::check(float camX, float camZ, float rotation, float translation,int direction)
{   bool flag=true;
    // define a distance to stay away from the wall
    float distance =1.0f;
    float x;
    float z;
    switch (direction){
    //case of forward action
    case 1:
        x = camX + translation*cos(rotation*PI/180);
        z = camZ + translation*sin(rotation*PI/180);
        break;
    //case of backward action
    case 2:
        x = camX - translation*cos(rotation*PI/180);
        z = camZ - translation*sin(rotation*PI/180);
        break;
    }

    //this part is executed if the key is found by the user
    if(!keyFound
            && x >= key_->getCoordinates().first - 2*10.0f
            && x <= key_->getCoordinates().first + 2*10.0f
            && z >= key_->getCoordinates().second - 2*10.0f
            && z <= key_->getCoordinates().second + 2*10.0f){
        keyFound = true;
        return true;
    }

    //check for walls
    for (float i=0;i<walls_.size();i++){

        Point p1=walls_[i]->getXlimits();
        Point p2=walls_[i]->getZlimits();
        if (x>=p1.first-distance && x<=p1.second+distance && z>=p2.first-distance && z<p2.second+distance)
        {
            if(keyFound && door_->IsEqual(*walls_[i])){
                            doorFound = true;
                            }
            flag =false;
        }
      }
    //check for corners
    for (float i=0;i<corners_.size();i++){

        Point p1=corners_[i]->getXlimits();
        Point p2=corners_[i]->getZlimits();
        if (x>=p1.first-distance && x<=p1.second+distance && z>=p2.first-distance && z<p2.second+distance)
        {
            flag =false;
        }
      }
    return flag;
}
//this method displays the maze 3D , it calls all display methods of differents objects : key, door, wall...
void Maze::display(float time) const
{
    //display walls
    if (keyFound){
        for(vector<Wall*>::const_iterator it = walls_.begin(); it != walls_.end(); ++it){
            //display door
            if (door_->IsEqual(**it)) (door_)->display();
            else  (*it)->display();       }
    }
    else{
        for (float i=0;i<walls_.size();i++){
            walls_[i]->display();
           }
        }

    //display corners
    for (float i=0;i<corners_.size();i++){
        corners_[i]->display();
       }
    //display ground
    ground_->display_ground();

    //display sky
    sky_->display_sky();

    //display key
    if(!keyFound){
        key_->display(time);
    }
}

//the method generate implements algorithm of Prime
//Here we fill all objects that we need with the appropriate fields and coordinates
void Maze::generate()
{
    list<Point> frontier;

    // Initialize random generator
    srand (time(NULL));

    // Mark a random cell and add the frontier cells to the list
    mark(Point(rand() % width_, rand() % height_),frontier);

    while(!frontier.empty()) {

        // Take a random frontier cell f (from)
        auto randPos=frontier.begin();
        advance(randPos,rand() % frontier.size());
        Point f=*randPos;
        frontier.erase(randPos);

        // Take a random neighbor t (to) of that cell
        list<Point> n=neighbors(f);
        randPos=n.begin();
        advance(randPos,rand() % n.size());
        Point t=*randPos;

        // Carve a passage from f to t
        Cell::Direction d=direction(f,t);
        grid_[f.second][f.first].setFrontier(d,false);
        grid_[t.second][t.first].setFrontier(Cell::Direction((d+2)%4),false);

        // Mark the cell and add the frontier cells to the list
        mark(f,frontier);

    }
    //affect values to texture_variables
    texture_wall=myGlWidget_ ->getWallsTexture();
    texture_door=myGlWidget_ ->getDoorTexture();
    texture_key=myGlWidget_ ->getKeyTexture();
    texture_ground=myGlWidget_ ->getGroundTexture();
    texture_sky=myGlWidget_->getSkyTexture();
    texture_corner=myGlWidget_->getCornersTexture();
    door_->setTexture(texture_door);

    int i,j;
    string cell[3]={"..","  ","()"};
    // use "clear" under linux
    system("cls");

      /*
      Below , we create objects of the maze:
      we fill the list of walls
      we fill the list of corners
      we fill the list of lines (used for 2D maze)
      we create the skiy ,the ground and the key objects
      */


    // Print the first line
    for (j=0; j<width_; j++){
        cout<<"+--";
        //add to corners vector
        corners_.push_back(new Corner(j*w_width + j*w_depth,0.0f,texture_corner));
        //add to walls vector
        walls_.push_back(new Wall(j*w_width + (j+1)*w_depth,0.0f,Wall::Horizontal,texture_wall));
        //add to lines vector
        //lines here is for storing different qlines that will be used to draw the maze in 2D
        lines_.push_back(new QLineF(MAZE2D_POSITION+j*MAZE2D_SIZE,MAZE2D_POSITION,MAZE2D_POSITION+(j+1)*MAZE2D_SIZE,MAZE2D_POSITION));
        if (door_->IsEqual(*walls_.back()))
            door_->setLine(lines_.back());
    }
    cout<<'+'<<endl;
    corners_.push_back(new Corner(width_*w_width + width_*w_depth,0.0f,texture_corner));

    // Print other lines
    for (i=0;i<height_;i++) {
        // Beginning of line
        lines_.push_back(new QLineF(MAZE2D_POSITION,MAZE2D_POSITION+i*MAZE2D_SIZE,MAZE2D_POSITION,MAZE2D_POSITION+(i+1)*MAZE2D_SIZE));
        walls_.push_back(new Wall(w_depth, i*w_width + (i+1)*w_depth,Wall::Vertical,texture_wall));
        if (door_->IsEqual(*walls_.back()))
            door_->setLine(lines_.back());
        cout<<'|';
        // Print cells
        for (j=0;j<width_;j++) {
             cout<<cell[grid_[i][j].getValue()];
            if (grid_[i][j].isFrontier(Cell::E)) {
                walls_.push_back(new Wall((j+1)*w_width + (j+2)*w_depth,i*w_width + (i+1)*w_depth,Wall::Vertical,texture_wall));
                lines_.push_back(new QLineF(MAZE2D_POSITION+(j+1)*MAZE2D_SIZE,MAZE2D_POSITION+i*MAZE2D_SIZE,MAZE2D_POSITION+(j+1)*MAZE2D_SIZE,MAZE2D_POSITION+(i+1)*MAZE2D_SIZE));
                if (door_->IsEqual(*walls_.back()))
                    door_->setLine(lines_.back());
                cout<<'|';
            }
            else{
                cout<<' ';
            }
        }
        cout<<endl;
        // Beginning of line
        cout<<'+';
        corners_.push_back(new Corner(0.0f,(i+1)*w_width + (i+1)*w_depth,texture_corner));
        // Print horizontal frontier
        for (j=0;j<width_;j++) {
            if (grid_[i][j].isFrontier(Cell::S)){
                walls_.push_back(new Wall(j*w_width + (j+1)*w_depth,(i+1)*w_width + (i+1)*w_depth,Wall::Horizontal,texture_wall));
                lines_.push_back(new QLineF(MAZE2D_POSITION+j*MAZE2D_SIZE,MAZE2D_POSITION+(i+1)*MAZE2D_SIZE,MAZE2D_POSITION+(j+1)*MAZE2D_SIZE,MAZE2D_POSITION+(i+1)*MAZE2D_SIZE));
                if (door_->IsEqual(*walls_.back()))
                    door_->setLine(lines_.back());
                cout<<"--";
            }
            else{
                cout<<"  ";
            }
            cout<<'+';
            corners_.push_back(new Corner((j+1)*w_width + (j+1)*w_depth,(i+1)*w_width + (i+1)*w_depth,texture_corner));
        }
        cout<<endl;
    }
    //initialise the sky_object
    sky_ = new Area(height_,width_,texture_sky);
    //initialise the ground_object
    ground_ = new Area(height_,width_,texture_ground);
    //initialise the key_object
    key_ = new Key(rand()%height_,rand()%width_,texture_key);
}



