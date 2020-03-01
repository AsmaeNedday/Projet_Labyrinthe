#ifndef MENU_H
#define MENU_H

#include <QWidget>
/**
 *The start widget
 */

namespace Ui {
class Menu;
}

class Menu : public QWidget
{
    Q_OBJECT

public:
    explicit Menu(QWidget *parent = nullptr);
    ~Menu();

private slots:
    void on_play_clicked();

private:
    Ui::Menu *ui;
};

#endif // MENU_H
