#-------------------------------------------------
#
# Project created by QtCreator 2016-11-20T15:07:48
#
#-------------------------------------------------

QT       += core gui
QT		+= charts network

greaterThan(QT_MAJOR_VERSION, 4): QT += widgets

TARGET = exer03
TEMPLATE = app


SOURCES += main.cpp\
        mainwidget.cpp \
    dataworker.cpp \
    time_count.cpp

HEADERS  += mainwidget.h \
    dataworker.h \ 
    common.h \
    time_count.h

FORMS    += mainwidget.ui

RC_ICONS = logo.ico

RESOURCES += \
    resorce.qrc

DISTFILES += \
    ../../build-exer03-Desktop_Qt_5_9_3_MinGW_32bit-Release/release/flat_blue.qss
