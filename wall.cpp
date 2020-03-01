#include "wall.h"

Wall::Wall(float x,float z,Type type,GLuint texture)
{
    this->x=x;
    this->z=z;
    this->type = type;
    this->texture=texture;

}

void Wall::display() const
{
    glMatrixMode(GL_MODELVIEW);
    glPushMatrix();

    glTranslatef(x, 0, z);
    if(type == Vertical)
        glRotated(90, 0, -1, 0);

    float r = 132.0f;
    float g = 46.0f;
    float b = 27.0f;


    GLfloat Ambiant[4] = {r,g, b, 1.0};
    GLfloat Diffuse[4] = {r, g, b, 1.0};
    glMaterialfv(GL_FRONT_AND_BACK, GL_AMBIENT, Ambiant);
    glMaterialfv(GL_FRONT_AND_BACK, GL_DIFFUSE,Diffuse);

    glBindTexture(GL_TEXTURE_2D,texture);
    glColor3f(r, g, b);
    glBegin(GL_QUADS);

    //la face avant du parralélipipède
    glNormal3f(0.0, 0.0, -1.0);
    glTexCoord2f(0.0f,0.0f);
    glVertex3f(0.0f,0.0f,0.0f);
    glTexCoord2f(1.0f,0.0f);
    glVertex3f(w_width,0.0f,0.0f);
    glTexCoord2f(1.0f,1.0f);
    glVertex3f(w_width,w_height,0.0f);
    glTexCoord2f(0.0f,1.0f);
    glVertex3f(0.0f,w_height,0.0f);
    //la face derrière du parralélipipède
    glNormal3f(0.0, 0.0, 1.0);
    glTexCoord2f(0.0f,0.0f);
    glVertex3f(0.0f,0.0f,w_depth);
    glTexCoord2f(1.0f,0.0f);
    glVertex3f(w_width,0.0f,w_depth);
    glTexCoord2f(1.0f,1.0f);
    glVertex3f(w_width,w_height,w_depth);
    glTexCoord2f(0.0f,1.0f);
    glVertex3f(0.0f,w_height,w_depth);
    // face gauche
    glNormal3f(-1.0, 0.0, 0.0);
    glTexCoord2f(0.0f,0.0f);
    glVertex3f(0.0f,0.0f,0.0f);
    glTexCoord2f(1.0f,0.0f);
    glVertex3f(0.0f,0.0f,w_depth);
    glTexCoord2f(1.0f,1.0f);
    glVertex3f(0.0f,w_height,w_depth);
    glTexCoord2f(0.0f,1.0f);
    glVertex3f(0.0f,w_height,0.0f);
    //face droite
    glNormal3f(1.0, 0.0, 0.0);
    glTexCoord2f(0.0f,0.0f);
    glVertex3f(w_width,0.0f,0.0f);
    glTexCoord2f(1.0f,0.0f);
    glVertex3f(w_width,0.0f,w_depth);
    glTexCoord2f(1.0f,1.0f);
    glVertex3f(w_width,w_height,w_depth);
    glTexCoord2f(0.0f,1.0f);
    glVertex3f(w_width,w_height,0.0f);
    //face au dessous
    glNormal3f(0.0, -1.0, 0.0);
    glTexCoord2f(0.0f,0.0f);
    glVertex3f(0.0f,0.0f,0.0f);
    glTexCoord2f(1.0f,0.0f);
    glVertex3f(w_width,0.0f,0.0f);
    glTexCoord2f(1.0f,1.0f);
    glVertex3f(w_width,0.0f,w_depth);
    glTexCoord2f(0.0f,1.0f);
    glVertex3f(0.0f,0.0f,w_depth);
    //face au dessus
    glNormal3f(0.0, 1.0, 0.0);
    glTexCoord2f(0.0f,0.0f);
    glVertex3f(0.0f,w_height,0.0f);
    glTexCoord2f(1.0f,0.0f);
    glVertex3f(w_width,w_height,0.0f);
    glTexCoord2f(1.0f,1.0f);
    glVertex3f(w_width,w_height,w_depth);
    glTexCoord2f(0.0f,1.0f);
    glVertex3f(0.0f,w_height,w_depth);

    glEnd();
    glPopMatrix();

}
/**
     @param none
    @return point
*/
Point Wall::getXlimits() const
{
    if (type == Horizontal)
        return make_pair(x,x + w_width);
    else
        return make_pair(x-w_depth,x);
}
/**
    @param none
    @return point
*/
Point Wall::getZlimits() const
{
    if (type == Horizontal)
        return make_pair(z,z +w_depth);
    else
        return make_pair(z,z + w_width);
}
