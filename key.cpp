#include "key.h"
#include <GL/gl.h>
#include <GL/glu.h>


Key::Key(int x, int z,GLuint texture)
{
    //x and y stores the start coordinates of the key
    //coordinates stores the coordinations of the key taking in consideration the size of the key
    coordinates = make_pair((z+0.5)*w_width+(z+1)*w_depth,(x+1)*w_depth+(x+0.5)*w_width);
    this->texture=texture;
}

//method to diplay the key
void Key::display(float time) const
{
    glMatrixMode(GL_MODELVIEW);
    glPushMatrix();

    glTranslatef(coordinates.first,10.0f, coordinates.second);
    glPushMatrix();
    //rotate the sphere
    glRotated((60)*time, 0, 1, 0);

    //add ambient and diffuse lights  to the sphere
    GLfloat color[4] = {255,255,255,1};
    glMaterialfv(GL_FRONT_AND_BACK, GL_AMBIENT,color);
    glMaterialfv(GL_FRONT_AND_BACK, GL_DIFFUSE,color);

    GLUquadric* quadric = gluNewQuadric();
    //activate texture
    gluQuadricTexture(quadric,GL_TRUE);
    //add texture
    glBindTexture(GL_TEXTURE_2D,texture);
    //draw the sphere using gluSphere
    gluSphere(quadric,3.0f, 20, 20);
    gluDeleteQuadric(quadric);
    gluQuadricTexture(quadric,GL_FALSE);

    glPopMatrix();


}
