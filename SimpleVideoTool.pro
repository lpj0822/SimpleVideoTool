#-------------------------------------------------
#
# Project created by QtCreator 2016-05-14T09:34:06
#
#-------------------------------------------------

QT       += core gui
QT       += multimedia
QT       += multimediawidgets

CONFIG   += c++11

greaterThan(QT_MAJOR_VERSION, 4): QT += widgets

TARGET = SimpleVideoTool
TEMPLATE = app

include(utility/utility.pri)
include(save_data/save_data.pri)


SOURCES += main.cpp\
    controlwindow.cpp \
    frompicturetovideowindow.cpp \
    fromvideotopicturewindow.cpp \
    fromvideotoscreenshotwindow.cpp \
    videocroppingwindow.cpp \
    croppingvideothread.cpp \
    imagesamplesmakewindow.cpp \
    imagesamplesmakethread.cpp \
    qcamerawindow.cpp \
    imageconverterthread.cpp \
    imageconverterwindow.cpp

HEADERS  += controlwindow.h \
    frompicturetovideowindow.h \
    fromvideotopicturewindow.h \
    fromvideotoscreenshotwindow.h \
    videocroppingwindow.h \
    croppingvideothread.h \
    imagesamplesmakewindow.h \
    imagesamplesmakethread.h \
    qcamerawindow.h \
    imageconverterthread.h \
    imageconverterwindow.h

RESOURCES += \
    style.qrc

RC_ICONS = appico.ico

INCLUDEPATH+= D:\opencv\build\include\
              D:\opencv\build\include\opencv\
              D:\opencv\build\include\opencv2


LIBS+=D:\opencv\build\x64\vc12\lib\opencv_world310d.lib
LIBS+=D:\opencv\build\x64\vc12\lib\opencv_world310.lib

