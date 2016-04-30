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
    main.cpp \
    AbstractHumanStepSolver.cpp \
    CornerFace.cpp \
    EdgeFace.cpp \
    ElementaryMoveDictionary.cpp \
    Face.cpp \
    HumanSolver.cpp \
    MiddleFace.cpp \
    Robot.cpp \
    RobotController.cpp \
    RobotSolver.cpp \
    RobotState.cpp \
    Rubik.cpp \
    RubikColor.cpp \
    TestCampaign.cpp \
    mylabel.cpp

HEADERS  += mainwindow.h \
    dialog1.h \
    AbstractHumanStepSolver.h \
    AbstractSolver.h \
    CornerFace.h \
    EdgeFace.h \
    ElementaryMoves.h \
    Face.h \
    HumanSolver.h \
    IndexOutOfBoundsException.h \
    MiddleFace.h \
    ResolutionException.h \
    Robot.h \
    RobotController.h \
    RobotPositionException.h \
    RobotSolver.h \
    RobotState.h \
    Rubik.h \
    RubikColor.h \
    TestCampaign.h \
    Utils.h \
    mylabel.h

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
