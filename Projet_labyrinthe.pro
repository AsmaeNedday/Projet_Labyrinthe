#-------------------------------------------------
#
# Project created by QtCreator 2016-04-13T15:06:48
#
#-------------------------------------------------

QT       += core gui multimedia multimediawidgets opengl widgets



TARGET = Projet_labyrinthe
TEMPLATE = app


SOURCES += main.cpp\
    area.cpp \
          camera_widget.cpp \
          corner.cpp \
    game.cpp \
    menu.cpp \
    door.cpp \
    key.cpp \
    maze.cpp \
    myglwidget.cpp \
    wall.cpp

HEADERS += \
    area.h \
           camera_widget.h \
           corner.h \
    cell.h \
    door.h \
    game.h \
    key.h \
    maze.h \
    menu.h \
    myglwidget.h \
    wall.h


FORMS  += \
          camera_widget.ui \
    game.ui \
    menu.ui


INCLUDEPATH +=$$(OPENCV_DIR)\..\..\include
# ajout des libs au linker
win32 {
    win32-msvc* {
        LIBS     += opengl32.lib glu32.lib
    } else {
        LIBS     += -lopengl32 -lglu32
    }
}
else {
        LIBS     += -lGL -lGLU
}


LIBS += -L$$(OPENCV_DIR)\lib \
    -lopencv_core420 \
    -lopencv_highgui420 \
    -lopencv_imgproc420 \
    -lopencv_imgcodecs420 \
    -lopencv_videoio420 \
    -lopencv_features2d420 \
    -lopencv_calib3d420 \
    -lopencv_objdetect420 \

RESOURCES +=




