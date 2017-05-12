TEMPLATE = app
CONFIG += console
CONFIG -= app_bundle
CONFIG -= qt
#LIBS += -lrt
LIBS+=-lpthread
SOURCES += main.c \
    fifo.c \
    threadpool.c

HEADERS += \
    fifo.h \
    threadpool.h
