#include "corner.h"
#include <GL/gl.h>
#include <GL/glu.h>


Corner::Corner(float x,float z,GLuint texture)
{
   this->x=x;
   this->z=z;
   this->texture=texture;
}

//The function display a corner according to its coordinates and adds texture using the texture field in
//the constructor of the corner

void Corner::display() const
{
    glMatrixMode(GL_MODELVIEW);
    glPushMatrix();
    //make translation in order to put the corner in the right place according to its coordinates
    glTranslatef(getX(),0,getZ());
    //define rgb colors
    float r = 132;
    float g = 46;
    float b = 27;

    //define the ambient and diffuse lights
    GLfloat ambiant[4] = {r,g, b, 1.0};
    GLfloat diffuse[4] = {r, g, b, 1.0};
    //add the ambient and diffuse lights to the material
    glMaterialfv(GL_FRONT_AND_BACK, GL_AMBIENT, ambiant);
    glMaterialfv(GL_FRONT_AND_BACK, GL_DIFFUSE,diffuse);

    glBindTexture(GL_TEXTURE_2D,texture);
    glColor3f(r, g, b);
    glBegin(GL_QUADS);
    // face in the front
    glNormal3f(0.0, 0.0, -1.0);
    glTexCoord2f(0.0f,0.0f);
    glVertex3f(0.0f,0.0f,0.0f);
    glTexCoord2f(1.0f,0.0f);
    glVertex3f(w_depth,0.0f,0.0f);
    glTexCoord2f(1.0f,1.0f);
    glVertex3f(w_depth,w_height,0.0f);
    glTexCoord2f(0.0f,1.0f);
    glVertex3f(0.0f,w_height,0.0f);
    //face in the back
    glNormal3f(0.0, 0.0, 1.0);
    glTexCoord2f(0.0f,0.0f);
    glVertex3f(0.0f,0.0f,w_depth);
    glTexCoord2f(1.0f,0.0f);
    glVertex3f(w_depth,0.0f,w_depth);
    glTexCoord2f(1.0f,1.0f);
    glVertex3f(w_depth,w_height,w_depth);
    glTexCoord2f(0.0f,1.0f);
    glVertex3f(0.0f,w_height,w_depth);
    //face  in left
    glNormal3f(-1.0, 0.0, 0.0);
    glTexCoord2f(0.0f,0.0f);
    glVertex3f(0.0f,0.0f,0.0f);
    glTexCoord2f(1.0f,0.0f);
    glVertex3f(0.0f,0.0f,w_depth);
    glTexCoord2f(1.0f,1.0f);
    glVertex3f(0.0f,w_height,w_depth);
    glTexCoord2f(0.0f,1.0f);
    glVertex3f(0.0f,w_height,0.0f);
    // face right
    glNormal3f(1.0, 0.0, 0.0);
    glTexCoord2f(0.0f,0.0f);
    glVertex3f(w_depth,0.0f,0.0f);
    glTexCoord2f(1.0f,0.0f);
    glVertex3f(w_depth,0.0f,w_depth);
    glTexCoord2f(1.0f,1.0f);
    glVertex3f(w_depth,w_height,w_depth);
    glTexCoord2f(0.0f,1.0f);
    glVertex3f(w_depth,w_height,0.0f);
    // face above
    glNormal3f(0.0, -1.0, 0.0);
    glTexCoord2f(0.0f,0.0f);
    glVertex3f(0.0f,0.0f,0.0f);
    glTexCoord2f(1.0f,0.0f);
    glVertex3f(w_depth,0.0f,0.0f);
    glTexCoord2f(1.0f,1.0f);
    glVertex3f(w_depth,0.0f,w_depth);
    glTexCoord2f(0.0f,1.0f);
    glVertex3f(0.0f,0.0f,w_depth);
    // face below
    glNormal3f(0.0, 1.0, 0.0);
    glTexCoord2f(0.0f,0.0f);
    glVertex3f(0.0f,w_height,0.0f);
    glTexCoord2f(1.0f,0.0f);
    glVertex3f(w_depth,w_height,0.0f);
    glTexCoord2f(1.0f,1.0f);
    glVertex3f(w_depth,w_height,w_depth);
    glTexCoord2f(0.0f,1.0f);
    glVertex3f(0.0f,w_height,w_depth);

    glEnd();

    glPopMatrix();

}


