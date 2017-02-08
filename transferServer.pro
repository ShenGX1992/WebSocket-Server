#-------------------------------------------------
#
# Project created by QtCreator 2016-11-25T13:46:02
#
#-------------------------------------------------

QT       += core websockets
QT       += core gui

greaterThan(QT_MAJOR_VERSION, 4): QT += widgets

TARGET = transferServer
TEMPLATE = app


SOURCES += main.cpp\
        transferserver.cpp

HEADERS  += transferserver.h

FORMS    += transferserver.ui
