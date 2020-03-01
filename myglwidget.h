#ifndef MYGLWIDGET_H
#define MYGLWIDGET_H
#include <QGLWidget>
#include <QMouseEvent>
#include <QWheelEvent>
#include <QKeyEvent>
#include <QTimer>
#include "maze.h"


/**
 * @brief The MyGLWidget class inherits from the QGLwidget, it's reponsible of displaying the maze in 3D format
 */
class MyGLWidget : public QGLWidget
{
    Q_OBJECT

//maze2D dimensions
const int MAZE2D_SIZE=17.0f;
const int MAZE2D_POSITION=45.0f;
public:

    MyGLWidget(int height,int width,QWidget * parent = nullptr);
    ~MyGLWidget();
    //get textures of the objects
    GLuint getWallsTexture(){return wallsTexture;};
    GLuint getGroundTexture(){return groundTexture;};
    GLuint getKeyTexture(){return keyTexture;};
    GLuint getSkyTexture(){return skyTexture;};
    GLuint getDoorTexture(){return doorTexture;};
    GLuint getCornersTexture(){return cornersTexture;};
    float getZ(){return (camZ - w_depth/2.0)/(w_width+ w_depth);};
    float getX(){return (camX - w_depth/2.0)/(w_width+ w_depth);};
    //get the orientation of the cam
    float getOrientation(){return orientation;};
    //connect face motions with motions in the maze
    void controlMotion();
    //restart the game
    void Restart();
    void draw_maze2d(QPainter *painter);
    void paint3D();
    void animate();
    void setTimer();



protected:

    void initializeGL();
    void paintEvent(QPaintEvent *event);
    void resizeGL(int width, int height);


private slots:
    //void handleControl(int flag);

private:
    float timeElapsed =0.0f;
    float show2D =1.5f;
    QTimer timer;
    Maze maze;
    GLuint wallsTexture;
    GLuint groundTexture;
    GLuint keyTexture;
    GLuint skyTexture;
    GLuint doorTexture;
    GLuint cornersTexture;
    QImage textures[6];
    GLuint* TextureID;
    QImage frame;
    float camX=10.0f;
    float camY=10.0f;
    float camZ=10.0f;
    float cible=200;
    float orientation = 40.0f;
    float rotation = 8.0f;
    float translation = 5.0f;

    //wall parameters
    float w_height = 40.0f;
    float w_width = 40.0f;
    float w_depth = 5.0f;

    //maze height and width
    int h;
    int w;

};

#endif // MYGLWIDGET_H
