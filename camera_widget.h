#ifndef CAMERA_WIDGET_H
#define CAMERA_WIDGET_H
#include <QWidget>
#include "opencv2/opencv.hpp"
#include <QPainter>
using namespace  std;

/**
 *
 * The camera_widget represents the widget that handles the webcam
 */
namespace Ui {
class Camera_widget;
}

class Camera_widget : public QWidget
{
    Q_OBJECT

public:
     //constructor
    explicit Camera_widget(QWidget *parent = nullptr);
    //destructor
    ~Camera_widget();

    //a static member to connect between face motion and motions in the maze
    static int Motion;
    static int getMotion(){return Motion;}


private:

    Ui::Camera_widget *ui;
    cv::VideoCapture * webCam_;
    int loop=0;
    cv::Mat frame1,frame2,frameRect1,frameRect2,frame1_gray,frame2_gray;
    vector <cv::Rect> faces,faces2;
    // to store the matchTemplate result
    cv::Mat resultImage;
    int result_cols ;
    int result_rows ;
    cv::Rect workingRect;
    int frameWidth=320;
    int frameHeight=240;
    QImage img;
    cv::Rect templateRect;
    cv::Point workingCenter;
    cv::CascadeClassifier face_cascade;
    QTimer *timer;
    int templateWidth=25;
    int templateHeight=25;



private slots:
    void capture();



};

#endif // CAMERA_WIDGET_H
