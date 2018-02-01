QT       -= gui

TARGET = test
TEMPLATE = lib
#目标输出目录
DESTDIR = "D:\program\zerobrane\bin"

DEFINES += TRANSCTION_LIBRARY


DEFINES += QT_DEPRECATED_WARNINGS

INCLUDEPATH +=$$PWD/lib/lua/lua-5.3.4/src
LIBS += -L$$PWD/lib/lua/ -llua53

HEADERS += \
    test.h

SOURCES += \
    test.cpp
