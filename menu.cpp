#include "menu.h"
#include "ui_menu.h"
#include <QColorDialog>
#include <QApplication>
#include <QDesktopWidget>
#include "myglwidget.h"
#include "maze.h"
#include "camera_widget.h"
#include <iostream>
#include "game.h"
using namespace std;


Menu::Menu(QWidget *parent) :
    QWidget(parent),
    ui(new Ui::Menu)
{
    setFixedSize(900, 450);
    move(QApplication::desktop()->screen()->rect().center() - rect().center());
    ui->setupUi(this);
    //setStyleSheet("Menu {background-image:url(../Projet_Labyrinthe/res/home.jpg)}");
    ui->title->setStyleSheet("QLabel {  color : red; }");
    ui->play->setStyleSheet("QPushButton{ background-color:red;}");
    // Fill the items of the ComboBox
       for(int i = 0; i < 20; i++)
       {
           ui->width_value->addItem(QString::number(i+1));
           ui->height_value->addItem(QString::number(i+1));
       }
      //set the default values in the combobox
      ui->width_value->setCurrentIndex(9);
      ui->height_value->setCurrentIndex(5);
      //set title of the window
      QWidget::setWindowTitle(tr("TELECOM MAZE"));
}

Menu::~Menu()
{
    delete ui;

}

void Menu::on_play_clicked()
{
    //method to start play
    QWidget::close();
    //get the values that were choosen by the user
    int width =(ui->width_value->currentText()).toInt();
    int height=(ui->height_value->currentText()).toInt();
    //Initialise new game widget
    Game* widget=new Game(width,height);
    //show game widget
    widget->show();



}
