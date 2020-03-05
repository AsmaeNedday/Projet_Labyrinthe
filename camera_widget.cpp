#include "opencv2/opencv.hpp"
#include "camera_widget.h"
#include "ui_camera_widget.h"
#include <stdlib.h>
#include <QString>
#include <QTimer>
#include <QKeyEvent>
#include <QEvent>
#include <thread>

using namespace cv;
using namespace std::this_thread;

int Camera_widget::Motion;

Camera_widget::Camera_widget(QWidget *parent) :
    QWidget(parent),
    ui(new Ui::Camera_widget)
{
    //fix the size of the screen
    setFixedSize(280,450);
    ui->setupUi(this);
    //add the background color
    ui->widget->setStyleSheet("background-color:red;");
    //start video
    webCam_=new VideoCapture(0);
    webCam_->set(CAP_PROP_FRAME_WIDTH,frameWidth);
    webCam_->set(CAP_PROP_FRAME_HEIGHT,frameHeight);
    if(!webCam_->isOpened())  // check if we succeeded
    {
        ui->infoLabel_->setText("Error openning the default camera !");
    }
    else
    {
        ui->infoLabel_->setText(QString("Video ok"));
    }
    //initialise a timer who will execute the slot capture each 100
    timer = new QTimer(this);
    //connect timer to the slot
    connect(timer, SIGNAL(timeout()), this, SLOT(capture()));
    //start timer
    timer->start(100);

}

//destructor
Camera_widget::~Camera_widget()
{
    delete ui;
    delete webCam_;
    delete timer;


}

//slot capture
void Camera_widget::capture()
{

        if( !face_cascade.load( "../Projet_labyrinthe/res/haarcascade_frontalface_alt.xml" ) )
           {
                   std::cout<<"error"<<loop<<std::endl;
                   exit(0);
         }
        if (this->loop==0){
        if (faces.size()==0)
        {
        // Get frame1
        webCam_->read(frame1);
        // Mirror effect
        cv::flip(frame1,frame1,1);
        cv::cvtColor(frame1,frame1_gray,COLOR_BGR2GRAY);
        //-- Detect faces
        face_cascade.detectMultiScale( frame1_gray, faces, 1.1, 4, 0, Size(60, 60) );
        // Display frame1
        img= QImage((const unsigned char*)(frame1.data),frame1.cols,frame1.rows,QImage::Format_RGB888);
        // Display on label
        ui->imageLabel_->setPixmap(QPixmap::fromImage(img));
        // Resize the label to fit the image
        ui->imageLabel_->resize(ui->imageLabel_->pixmap()->size());
        }

        //Part 1
        if (faces.size()>0){
         //increment loop in order to not execute this part again if faces were detected
         loop++;
         //workingRect stores the face
         workingRect=faces[0];

         templateRect.x=(workingRect.width-templateWidth)/2;
         templateRect.y=(workingRect.height-templateHeight)/2;
         templateRect.width=templateWidth;
         templateRect.height=templateHeight;
         //the center of the workingRect
         workingCenter.x=workingRect.x+workingRect.width/2;
         workingCenter.y=workingRect.y+workingRect.height/2;

         // Extract rect1 and convert to gray
         cv::cvtColor(Mat(frame1,workingRect),frameRect1,COLOR_BGR2GRAY);

        // Create the matchTemplate image result
        result_cols =  frame1.cols-templateWidth  + 1;
        result_rows = frame1.rows-templateHeight + 1;
        resultImage.create( result_cols, result_rows, CV_32FC1 );}
         }

         //Part 2 is executed when face is already detected
        // Part 2
           if (this->loop>0)
         {
        // Get frame2
        webCam_->read(frame2);
        // Mirror effect
        cv::flip(frame2,frame2,1);
        cv::cvtColor(frame2,frame2_gray,COLOR_BGR2GRAY);
        // Equalize graylevels
        // equalizeHist( frame_gray, frame_gray );
        //-- Detect faces
        face_cascade.detectMultiScale( frame2_gray, faces2, 1.1, 4, 0, Size(60, 60) );

         // Extract working rect in frame2 and convert to gray
         cv::cvtColor(Mat(frame2,workingRect),frameRect2,COLOR_BGR2GRAY);
         Mat templateImage(frameRect1,templateRect);

        // Do the Matching between the working rect in frame2 and the templateImage in frame1
        matchTemplate( frameRect2, templateImage, resultImage, TM_CCORR_NORMED );
        // Localize the best match with minMaxLoc
        double minVal; double maxVal; cv::Point minLoc; cv::Point maxLoc;
        minMaxLoc( resultImage, &minVal, &maxVal, &minLoc, &maxLoc);
        // Compute the translation vector between the origin and the matching rect
        cv::Point vect(maxLoc.x-templateRect.x,maxLoc.y-templateRect.y);

        // Draw green rectangle and the translation vector
        rectangle(frame2,workingRect,Scalar( 0, 255, 0),2);

        cv::Point p(workingCenter.x+vect.x,workingCenter.y+vect.y);
        circle(frame2, workingCenter,5, Scalar( 0, 255, 0),1,8,0) ;

        //handle motion
        if (faces2[0].x-faces[0].x>17 || faces[0].x-faces2[0].x>17
           ||faces2[0].y-faces[0].y>17 || faces[0].y-faces2[0].y>17
           ||faces2[0].width-faces[0].width>4 || faces[0].width-faces2[0].width>4
           ||faces2[0].height-faces[0].height>4 || faces[0].height-faces2[0].height>4
              )
        {
            Motion=0;
            putText(frame2, "Visage not detected !! to your position ", Point2f(1,8),FONT_HERSHEY_PLAIN ,0.65,  Scalar(255,0,0),0,4 , false);
       }
        else
        {
             putText(frame2, "Visage detected ", Point2f(1,8),FONT_HERSHEY_PLAIN ,0.65,  Scalar(0,255,0),0,4 , false);
             arrowedLine(frame2,workingCenter,p,Scalar(255,255,255),2);
             //the rotation is the dominant motion
             if (abs(workingCenter.x-p.x)>abs(workingCenter.y-p.y))
             {
                if (workingCenter.x-p.x<0 && abs(workingCenter.x-p.x)>1)
                 {
                     cout<<"rotation droite"<<endl;
                     Motion=1;}

                 if (workingCenter.x-p.x>0 && abs(workingCenter.x-p.x)>1)  {

                     cout<<"rotation gauche"<<endl;
                     Motion=2;}
             }
             //the translation is the dominant motion
            else{

             if (workingCenter.y-p.y<0 && abs(workingCenter.y-p.y)>1 )
             {
                 cout<<"translation vers bas"<<endl;
                 Motion=4;

             }
             if (workingCenter.y-p.y>0 && abs(workingCenter.y-p.y)>1)
             {
                 cout<<"translation vers haut"<<endl;
                 Motion=3;
             }
             else
             {
                 cout<<"position neutre"<<endl;
                 Motion=0;
             }
             }
        }


        // Display frame2
        img = QImage((const unsigned char*)(frame2.data),frame2.cols,frame2.rows,QImage::Format_RGB888);
        // Display on label
        ui->imageLabel_->setPixmap(QPixmap::fromImage(img));

}
}


