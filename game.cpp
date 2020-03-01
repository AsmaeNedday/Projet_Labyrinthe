#include "game.h"
#include "ui_game.h"
#include "camera_widget.h"
#include "myglwidget.h"
#include <QApplication>
#include <QDesktopWidget>
#include <iostream>
#include "menu.h"
using namespace std;

Game::Game(int width,int height,QWidget *parent) :
    QWidget(parent),
    ui(new Ui::Game)
{
    setFixedSize(900, 450);
    //center screen
    move(QApplication::desktop()->screen()->rect().center() - rect().center());
    ui->setupUi(this);
    //add MyGLWidget to the game widget
    maze_widget=new MyGLWidget(height,width);
    ui->grid->addWidget(maze_widget);
    //set the title of the window
    QWidget::setWindowTitle(tr("TELECOM MAZE"));
}

//destructor
Game::~Game()
{
    delete ui;
    delete maze_widget;

}

//if clicked on restart button
void Game::on_restart_clicked()
{
 maze_widget->Restart();

}
//if clicked on home button
void Game::on_home_clicked()
{
    QWidget::close();
    Menu *menu =new Menu();
    menu->show();
}
