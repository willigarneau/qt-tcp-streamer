#-------------------------------------------------
#
# Project created by QtCreator 2017-04-22T14:25:25
#
#-------------------------------------------------

QT       += core gui network

greaterThan(QT_MAJOR_VERSION, 4): QT += widgets

TARGET = TheStreamer-client
TEMPLATE = app


SOURCES += main.cpp\
        streamerclient.cpp \
    streamerthread.cpp

HEADERS  += streamerclient.h \
    streamerthread.h

FORMS    += streamerclient.ui
