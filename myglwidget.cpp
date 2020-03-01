#include "myglwidget.h"
#include <QApplication>
#include <QDesktopWidget>
#include <thread>
#include "camera_widget.h"
#define PI 3.14159265


// Screen dimensions
const unsigned int WIN_WIDTH  = 620;
const unsigned int WIN_HEIGHT = 450;


MyGLWidget::MyGLWidget(int height,int width,QWidget * parent) : QGLWidget(parent),
    maze(this,width,height)
{
    //height and width of the maze
    this->h=height;
    this->w=width;
    //set width and height for the widget of class MyGLWidget
    setFixedSize(WIN_WIDTH,WIN_HEIGHT);
    move(QApplication::desktop()->screen()->rect().center() - rect().center());
    connect(&timer,  &QTimer::timeout, [&] { timeElapsed += 0.1f;show2D += 0.1f;animate();});
    setTimer();
    setAutoFillBackground(false);
    setWindowTitle(tr("TELECOM MAZE"));
}
//destructor
MyGLWidget::~MyGLWidget()
{
    delete[] TextureID;
}

/**
    @param none
    @return none
    to initialize the scene
*/
void MyGLWidget::initializeGL()
{
    // Charging the images and textures
    textures[0] = QGLWidget::convertToGLFormat(QImage("../Projet_Labyrinthe/res/texture_wall.jpg"));
    textures[1] = QGLWidget::convertToGLFormat(QImage("../Projet_Labyrinthe/res/texture_ground.jpg"));
    textures[2] = QGLWidget::convertToGLFormat(QImage("../Projet_Labyrinthe/res/texture_key.jpg"));
    textures[3] = QGLWidget::convertToGLFormat(QImage("../Projet_Labyrinthe/res/sky_texture.jpg"));
    textures[4] = QGLWidget::convertToGLFormat(QImage("../Projet_Labyrinthe/res/door_texture.jpg"));
    textures[5] = QGLWidget::convertToGLFormat(QImage("../Projet_Labyrinthe/res/texture_corner.jpg"));

    TextureID = new GLuint[5];
    glGenTextures(6,TextureID);

    //Binding textures
    for(int i=0; i<6; i++){
        glBindTexture( GL_TEXTURE_2D, TextureID[i] );
        glTexImage2D( GL_TEXTURE_2D, 0, 4, textures[i].width(),textures[i].height(), 0, GL_RGBA, GL_UNSIGNED_BYTE, textures[i].bits());
        glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MIN_FILTER, GL_LINEAR);
        glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MAG_FILTER, GL_LINEAR);
    }

    wallsTexture = TextureID[0];
    groundTexture = TextureID[1];
    keyTexture = TextureID[2];
    skyTexture = TextureID[3];
    doorTexture =TextureID[4];
    cornersTexture =TextureID[5];

    // Generating the maze
    maze.generate();
}
/**
    @param none
    @return none
    It sets the timer
*/
void MyGLWidget::setTimer(){
   //set a timer
   timer.setTimerType(Qt::PreciseTimer);
   //set the intervall of the timer
   timer.setInterval(100);
   //start the timer
   timer.start();
}

/**
    @param none
    @return none
    It is used to paint in the scene
*/
void MyGLWidget::paintEvent(QPaintEvent *event)
{
    glClearColor(0.5f, 0.5f, 0.5f, 0.0f);

    // Activation of zbuffer
    glEnable(GL_DEPTH_TEST);
    //Activation of light
    glEnable(GL_LIGHTING);
    //Activation of texture
    glEnable(GL_TEXTURE_2D);

    //Defining the ambient and diffuse lights
    GLfloat colorAmbient_tab0[] = {1.0, 1.0, 1.0, 1.0};
    glLightfv(GL_LIGHT0, GL_AMBIENT, colorAmbient_tab0);

    GLfloat colorDiffuse_tab0[] = {1.0, 1.0, 1.0, 1.0};
    glLightfv(GL_LIGHT0, GL_DIFFUSE, colorDiffuse_tab0);

    glEnable(GL_LIGHT0);
    //clear buffers
    glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);

    glMatrixMode(GL_MODELVIEW);
    glLoadIdentity();
    //the position of the camera
    gluLookAt(camX,camY,camZ,camX +cible*cos(orientation*PI/180), camY, camZ + cible*sin(orientation*PI/180), 0, 1, 0);

    //Define position of the camera
    GLfloat light_position[] = {camX,camY,camZ, 1.0f};
    glLightfv(GL_LIGHT0, GL_POSITION, light_position);
    glEnable(GL_LIGHT0);

    maze.display(timeElapsed);
    //To control motions in the maze using face
    controlMotion();

    glMatrixMode(GL_MODELVIEW);
    glPopMatrix();

    //QPainter is used to paint the maze 2D
    QPainter painter(this);
    painter.setRenderHint(QPainter::Antialiasing);
    draw_maze2d(&painter);
    painter.end();
}

/**
    @param none
    @return none
    It resizes the scene
*/
void MyGLWidget::resizeGL(int width, int height)
{
     //fixing the view port
     glViewport(0, 0, width, height);
     glMatrixMode(GL_PROJECTION);
     glLoadIdentity();
     if(width != 0){
         GLdouble znear=0.1f;
         GLdouble zfar=sqrt(pow(w*w_width +
                                (w+1)*w_depth,2)
                                +pow(h*w_width +
                                (h+1)*w_depth,2));
         //set parameters for the camera
         gluPerspective(80.0f,((float)width)/height,znear,zfar);}
     glMatrixMode(GL_MODELVIEW);
}

/**
    @param none
    @return none
    It sets a new position according to the return of the static function Camera_widget::getMotion()
*/
void MyGLWidget::controlMotion(){

    switch (Camera_widget::getMotion()){

    case 1:
    {
        orientation += rotation;
        if (orientation >= 360)
             orientation -= 360;
        if (orientation < 0)
             orientation += 360;
        break;
       }
    case 2:
       { orientation -= rotation;
        if (orientation >= 360)
            orientation -= 360;
        if (orientation < 0)
            orientation += 360;
        break;}
    case 3:
        if(maze.check(camX,camZ,orientation,translation,1)){
            camX += translation*cos(orientation*PI/180);
            camZ += translation*sin(orientation*PI/180);
            show2D= 0.0f;//don't show the maze 2D
        }
        break;
    case 4:
        if(maze.check(camX,camZ,orientation,translation,2)){
            camX -= translation*cos(orientation*PI/180);
            camZ -= translation*sin(orientation*PI/180);
            show2D = 0.0f;//don't show the maze 2D
        }
        break;


}
}

/**
    @param none
    @return none
    It  stops the animation of the timer if the door is found
*/
void MyGLWidget::animate()
{
    update();
    if(maze.IsDoorFound()){
        timer.stop();
    }

}
/**
    @param QPainter*
    @return none
    It  draws the maze 2D with the coordinations of the user and the key
    It draws also the message of end of game
*/
void MyGLWidget::draw_maze2d(QPainter *painter)
{
    if(!maze.IsDoorFound()){
        //function to draw maze 2D
        int time= floor(timeElapsed);
        const char* timeElapsed = (((time/60>=10) ? (to_string(time/60)) : ("0" + to_string(time/60)))
                                 + ":" + ((time%60>=10) ? (to_string(time%60)) : ("0" + to_string(time%60))) ).c_str();

        //draw the rect that will display the time
        QString text = tr(timeElapsed);
        QRect rect = QRect(0, 0,40,height());
        painter->fillRect (rect,Qt::red );
        painter->drawRect( rect );
        painter->drawText( rect, Qt::AlignCenter,text);


        // Draw the maze 2D on the screen
        if(show2D >= 1.5f)
        {
            painter->setPen(QPen(QColor(0,0,0,100), 2, Qt::SolidLine, Qt::SquareCap));

            if (!maze.IsKeyFound()){
                for(vector<QLineF*>::iterator it = maze.getLines()->begin(); it != maze.getLines()->end(); ++it){
                    painter->drawLine(*(*it));
                }
            }
            else{
                for(vector<QLineF*>::iterator it = maze.getLines()->begin(); it != maze.getLines()->end(); ++it){
                    if(*it != maze.getDoor()->getLine())
                        painter->drawLine(*(*it));
                }
            }

            QRect rectangle;

            // Drawing the key on the map
            painter->setPen(QPen(QColor(0,1,0,255), 2, Qt::SolidLine, Qt::SquareCap));
            painter->setBrush(QBrush(QColor(0,255,0, 255)));

            if(!maze.IsKeyFound()){
                rectangle = QRect(MAZE2D_POSITION+(maze.getKeyZ() + 0.5 - 1/8.0)*MAZE2D_SIZE,
                                  MAZE2D_POSITION+(maze.getKeyX() + 0.5 - 1/8.0)*MAZE2D_SIZE,
                                 MAZE2D_SIZE/4.0,
                                 MAZE2D_SIZE/4.0);
                painter->drawEllipse(rectangle);
            }

            // Drawing the position of the man on the maze
            painter->setPen(QPen(Qt::red, 2, Qt::SolidLine, Qt::SquareCap));
            painter->setBrush(QBrush(Qt::white));

            rectangle = QRect(MAZE2D_POSITION+(getX()-1/12.0)*MAZE2D_SIZE,
                              MAZE2D_POSITION+(getZ()-1/12.0)*MAZE2D_SIZE,
                             MAZE2D_SIZE/6.0,
                             MAZE2D_SIZE/6.0);
            painter->drawEllipse(rectangle);

            QLineF orientationLine(MAZE2D_POSITION+(getX())*MAZE2D_SIZE,
                                   MAZE2D_POSITION+(getZ())*MAZE2D_SIZE,
                                   MAZE2D_POSITION+(getX())*MAZE2D_SIZE + cos(
                                       getOrientation()*PI/180)*MAZE2D_SIZE/5.0,
                                   MAZE2D_POSITION+(getZ())*MAZE2D_SIZE + sin(
                                      getOrientation()*PI/180)*MAZE2D_SIZE/5.0);
            painter->drawLine(orientationLine);
        }

    }else{
        //function to draw the end of game
        int timeElapsedInt = floor(timeElapsed);
        const char* timeElapsed = ("Time spent: "+((timeElapsedInt/60>=10) ? (to_string(timeElapsedInt/60))
                   : ("0" + to_string(timeElapsedInt/60))) + ":" +((timeElapsedInt%60>=10) ? (to_string(timeElapsedInt%60)) : ("0" + to_string(timeElapsedInt%60)))  ).c_str();
        QString timeSpent = timeElapsed;
        QRect rect = QRect(0, 0, width(), height());

        QFont font = painter->font();
        font.setPixelSize(30);
        painter->setFont(font);

        rect = QRect(0, height()/2.0 + 70, width(), 50);
        painter->setPen(Qt::red);
        painter->drawText(rect, Qt::AlignCenter | Qt::TextWordWrap, timeSpent);

    }


}
/**
    @param none
    @return none
    It restarts playing the maze
*/
void MyGLWidget::Restart()
{
 timer.stop();
 //initialize maze parameters
 maze.initialize();
 //initialize camera parameters
 camX=10.0f;
 camY=10.0f;
 camZ=10.0f;
 cible=200;
 orientation = 40.0f;
 rotation = 8.0f;
 translation = 5.0f;
 //initialise time
 timeElapsed = 0.0f;
 update();
 //start animation of the time
 timer.start();


}


