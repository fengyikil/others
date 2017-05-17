#-------------------------------------------------
#
# Project created by QtCreator 2017-04-07T11:33:54
#
#-------------------------------------------------


QT       += core gui

greaterThan(QT_MAJOR_VERSION, 4): QT += widgets

TARGET = 978_focusing
TEMPLATE = app

DESTDIR =$$PWD/../../Win32/Debug


# The following define makes your compiler emit warnings if you use
# any feature of Qt which as been marked as deprecated (the exact warnings
# depend on your compiler). Please consult the documentation of the
# deprecated API in order to know how to port your code away from it.
DEFINES += QT_DEPRECATED_WARNINGS

# You can also make your code fail to compile if you use deprecated APIs.
# In order to do so, uncomment the following line.
# You can also select to disable deprecated APIs only up to a certain version of Qt.
#DEFINES += QT_DISABLE_DEPRECATED_BEFORE=0x060000    # disables all the APIs deprecated before Qt 6.0.0

INCLUDEPATH+=$$PWD/src
INCLUDEPATH+=$$PWD/../../App978/3rdparty/src/halcon/include
INCLUDEPATH+=$$PWD/../../App978/3rdparty/src/halcon/include/halconcpp
INCLUDEPATH+=$$PWD/../../App978/BmCamV1
INCLUDEPATH+=$$PWD/../../App978/3rdparty/BmCameraInterface/include

LIBS += -L$$PWD/../../App978/3rdparty/src/halcon/lib/x86sse2-win32 -lhalconcpp -lhalcon
LIBS += -L$$PWD/../../App978/3rdparty/BmCameraInterface/lib -lBmCameraInterface

RESOURCES += \
    myqrc.qrc

FORMS += \
    src/focusing.ui

HEADERS += \
    src/MeasureDistance.h \
    src/picview.h \
    src/focusing.h

SOURCES += \
    src/main.cpp \
    src/MeasureDistance.cpp \
    src/picview.cpp \
    src/focusing.cpp


