#ifndef AREA_H
#define AREA_H
#include <GL/gl.h>
#include <GL/glu.h>

/**
 * @brief The Area class is for displaying the sky or the ground of the maze
 */
class Area
{
public:
    //constructor
    Area(int height, int width,GLuint texture);
    void display_sky() const;//to display the sky object
    void display_ground() const;//to display the ground object

private:
    //height and width of the maze
    int height;
    int width;
    //texture of the area
    GLuint texture;
    //wall parameters
    float w_height = 40.0f;
    float w_width = 40.0f;
    float w_depth = 5.0f;

};

#endif // AREA_H
