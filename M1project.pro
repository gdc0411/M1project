#-------------------------------------------------
#
# Project created by QtCreator 2016-01-13T10:46:06
#
#-------------------------------------------------

QT       += core gui

greaterThan(QT_MAJOR_VERSION, 4): QT += widgets

TARGET = M1project
TEMPLATE = app


SOURCES +=\
        mainwindow.cpp \
    dialog1.cpp \
    main.cpp

HEADERS  += mainwindow.h \
    dialog1.h

FORMS    += mainwindow.ui \
    dialog1.ui

INCLUDEPATH += C:/opencv/build/include

win32:CONFIG(debug, debug|release): {
LIBS += -LC:\opencv\build\x64\vc12\lib \
-lopencv_world310d
} else:win32:CONFIG(release, debug|release): {
LIBS += -LC:\opencv\build\x64\vc12\lib \
-lopencv_world310
}
