#-------------------------------------------------
#
# Project created by QtCreator 2015-10-27T10:57:47
#
#-------------------------------------------------

QT       += core gui

greaterThan(QT_MAJOR_VERSION, 4): QT += widgets

TARGET = Qpwd
TEMPLATE = app


SOURCES += main.cpp\
        dialog.cpp \
    pwd_thread.cpp

HEADERS  += dialog.h \
    pwd_thread.h

FORMS    += dialog.ui
