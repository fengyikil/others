QT += core
QT -= gui
QT += network
CONFIG += c++11

TARGET = ns_file
CONFIG += console
CONFIG -= app_bundle

TEMPLATE = app

SOURCES += main.cpp \
    mytcpsocket.cpp \
    mytcpserver.cpp

HEADERS += \
    mytcpsocket.h \
    mytcpserver.h
INCLUDEPATH += "./co"
INCLUDEPATH += "/usr/local/include/canfestival"
LIBS += -L/usr/local/lib/ -lcanfestival -lcanfestival_unix -lcanfestival_can_socket -lrt
