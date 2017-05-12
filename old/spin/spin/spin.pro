#-------------------------------------------------
#
# Project created by QtCreator 2015-06-27T15:16:34
#
#-------------------------------------------------

QT       += core gui

greaterThan(QT_MAJOR_VERSION, 4): QT += widgets

TARGET = spin
TEMPLATE = app


SOURCES += main.cpp\
        mainmenu.cpp \
    modbus_thread.cpp \
    ui/soft_keyboard/myinputpanelcontext.cpp \
    ui/soft_keyboard/myinputpanel.cpp \
    ui/menu/menu_top.cpp \
    ui/menu/samplevalue.cpp \
    ui/menu/editbt.cpp \
    ui/menu/head.cpp

HEADERS  += mainmenu.h \
    modbus_thread.h \
    type.h \
    ui/soft_keyboard/myinputpanelcontext.h \
    ui/soft_keyboard/myinputpanel.h \
    ui/menu/menu_top.h \
    ui/menu/samplevalue.h \
    ui/menu/editbt.h \
    ui/menu/head.h

FORMS    += mainmenu.ui
LIBS +=-lmodbus
