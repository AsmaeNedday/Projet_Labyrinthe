#include "area.h"
#include <GL/gl.h>
#include <GL/glu.h>

Area::Area(int height, int width,GLuint texture)
{
    this->height = height;
    this->width = width;
    this->texture=texture;

}

void Area::display_sky() const
{

    glMatrixMode(GL_MODELVIEW);
    glPushMatrix();

    GLfloat colorAmbiant[4] = {1.0, 1.0, 1.0, 1.0};
    glMaterialfv(GL_FRONT_AND_BACK, GL_AMBIENT_AND_DIFFUSE, colorAmbiant);

    glBindTexture(GL_TEXTURE_2D,texture);
    glBegin(GL_QUADS);
    glNormal3f(0.0, -1.0, 0.0);
    glColor3f(1.0, 1.0, 1.0);
    glTexCoord2f(0.0f,0.0f);
    glVertex3f(0.0f,w_height,0.0f);
    glTexCoord2f(1.0f,0.0f);
    glVertex3f(width*w_width + (width+1)*w_depth,w_height,0.0f);
    glTexCoord2f(1.0f,1.0f);
    glVertex3f(width*w_width + (width+1)*w_depth,w_height,height*w_width + (height+1)*w_depth);
    glTexCoord2f(0.0f,1.0f);
    glVertex3f(0.0f,w_height,height*w_width + (height+1)*w_depth);
    glEnd();

    glPopMatrix();

}
void Area::display_ground() const
{

    glBindTexture(GL_TEXTURE_2D,texture);
    glMatrixMode(GL_MODELVIEW);
    glPushMatrix();

    GLfloat colorAmbiant[4] = {1.0, 1.0, 1.0, 1.0};
    glMaterialfv(GL_FRONT_AND_BACK, GL_AMBIENT_AND_DIFFUSE, colorAmbiant);

    glBegin(GL_QUADS);
    glNormal3f(0.0, -1.0, 0.0);
    glColor3f(1.0, 1.0, 1.0);
    glTexCoord2f(0.0f,0.0f);
    glVertex3f(0.0f,0.0f,0.0f);
    glTexCoord2f(1.0f,0.0f);
    glVertex3f(width*w_width + (width+1)*w_depth,0.0f,0.0f);
    glTexCoord2f(1.0f,1.0f);
    glVertex3f(width*w_width + (width+1)*w_depth,0.0f,height*w_width + (height+1)*w_depth);
    glTexCoord2f(0.0f,1.0f);
    glVertex3f(0.0f,0.0f,height*w_width + (height+1)*w_depth);
    glEnd();

    glPopMatrix();

}
