#include "door.h"
#include <GL/gl.h>
#include <GL/glu.h>

//the object door stocks informations about which wall would be removed if the user won
Door::Door(int height, int width,GLuint texture)
{
    this->texture=texture;
    int random = rand()%4;
    float x,z=0;
    int i,j;
    if (random==0){ j = rand()%width;i = 0;x = j*w_width + (j+1)*w_depth;z = 0.0; type = Wall::Horizontal;
    }else if (random==1){j = 0;i = rand()%height;x = w_depth;z = i*w_width + (i+1)*w_depth;type = Wall::Vertical;}
        else if (random==2){j = rand()%width;i = height-1;x = j*w_width + (j+1)*w_depth;z = (i+1)*w_width + (i+1)*w_depth;type = Wall::Horizontal; }
            else if (random ==4){j = width-1;i = rand()%height;x = (j+1)*w_width + (j+2)*w_depth;z = i*w_width + (i+1)*w_depth;type = Wall::Vertical;
            }

    this->x=x;
    this->z=z;

}
//the display method is similar of the method display wall
void Door::display() const
{
    glMatrixMode(GL_MODELVIEW);
    glPushMatrix();

    glTranslatef(x, 0, z);
    if(type == Wall::Vertical)
        glRotated(90, 0, -1, 0);

    //define the ambient and diffuse lights
    GLfloat colorAmbiant[4] = {1,1,1, 1.0};
    glMaterialfv(GL_FRONT_AND_BACK, GL_AMBIENT, colorAmbiant);
    //add tecture to the door
    glBindTexture(GL_TEXTURE_2D,texture);
    glBegin(GL_QUADS);

    //face in front
    glNormal3f(0.0, 0.0, -1.0);
    glTexCoord2f(0.0f,0.0f);
    glVertex3f(0.0f,0.0f,0.0f);
    glTexCoord2f(1.0f,0.0f);
    glVertex3f(w_width,0.0f,0.0f);
    glTexCoord2f(1.0f,1.0f);
    glVertex3f(w_width,w_height,0.0f);
    glTexCoord2f(0.0f,1.0f);
    glVertex3f(0.0f,w_height,0.0f);
    //face in back
    glNormal3f(0.0, 0.0, 1.0);
    glTexCoord2f(0.0f,0.0f);
    glVertex3f(0.0f,0.0f,w_depth);
    glTexCoord2f(1.0f,0.0f);
    glVertex3f(w_width,0.0f,w_depth);
    glTexCoord2f(1.0f,1.0f);
    glVertex3f(w_width,w_height,w_depth);
    glTexCoord2f(0.0f,1.0f);
    glVertex3f(0.0f,w_height,w_depth);
    //face in left
    glNormal3f(-1.0, 0.0, 0.0);
    glTexCoord2f(0.0f,0.0f);
    glVertex3f(0.0f,0.0f,0.0f);
    glTexCoord2f(1.0f,0.0f);
    glVertex3f(0.0f,0.0f,w_depth);
    glTexCoord2f(1.0f,1.0f);
    glVertex3f(0.0f,w_height,w_depth);
    glTexCoord2f(0.0f,1.0f);
    glVertex3f(0.0f,w_height,0.0f);
    //face in right
    glNormal3f(1.0, 0.0, 0.0);
    glTexCoord2f(0.0f,0.0f);
    glVertex3f(w_width,0.0f,0.0f);
    glTexCoord2f(1.0f,0.0f);
    glVertex3f(w_width,0.0f,w_depth);
    glTexCoord2f(1.0f,1.0f);
    glVertex3f(w_width,w_height,w_depth);
    glTexCoord2f(0.0f,1.0f);
    glVertex3f(w_width,w_height,0.0f);
    //face below
    glNormal3f(0.0, -1.0, 0.0);
    glTexCoord2f(0.0f,0.0f);
    glVertex3f(0.0f,0.0f,0.0f);
    glTexCoord2f(1.0f,0.0f);
    glVertex3f(w_width,0.0f,0.0f);
    glTexCoord2f(1.0f,1.0f);
    glVertex3f(w_width,0.0f,w_depth);
    glTexCoord2f(0.0f,1.0f);
    glVertex3f(0.0f,0.0f,w_depth);
    //face above
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
