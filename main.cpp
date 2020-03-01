/**
* from <http://weblog.jamisbuck.org/2011/1/10/maze-generation-prim-s-algorithm>
*
* C++ implementation 
**/

#include <iostream>
#include <QApplication>
#include <ctime>
#include "menu.h"
using namespace std;

int main(int argc, char *argv[])
{
    // Initialise the random numbers generator
    srand(time(nullptr));

    // Create Qt application
    QApplication app(argc, argv);

    //Creation of menu widget

    Menu menu;

    //show menu widget
    menu.show();

    // execute the QT application
    return app.exec();
}


/* Example of generated maze:

    +--+--+--+--+--+--+--+--+--+--+
    |        |     |  |     |     |
    +--+--+  +  +  +  +--+  +--+  +
    |     |  |  |  |  |        |  |
    +  +--+  +--+  +  +--+--+  +  +
    |           |     |  |        |
    +  +  +--+  +  +--+  +  +--+  +
    |  |  |  |  |     |        |  |
    +  +--+  +  +--+  +  +--+  +--+
    |  |  |              |        |
    +--+  +--+  +--+  +  +--+  +--+
    |           |     |  |        |
    +--+--+--+--+--+--+--+--+--+--+

*/
