#ifndef GAME_H
#define GAME_H

#include <QWidget>
#include "myglwidget.h"

/**
 *The game widget gathers the camera_widget and the maze widget (myglwidget)
 */
namespace Ui {
class Game;
}

class Game : public QWidget
{
    Q_OBJECT

public:
    explicit Game(int width,int height,QWidget *parent = nullptr);
    ~Game();

private slots:
    void on_restart_clicked();

    void on_home_clicked();

private:
    Ui::Game *ui;
    MyGLWidget* maze_widget;
};

#endif // GAME_H
