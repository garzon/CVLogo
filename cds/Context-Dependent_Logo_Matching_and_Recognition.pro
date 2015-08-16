#-------------------------------------------------
#
# Project created by QtCreator 2015-07-29T07:42:42
#
#-------------------------------------------------

QT       += core

QT       -= gui

TARGET = Context-Dependent_Logo_Matching_and_Recognition
CONFIG   += console
CONFIG   -= app_bundle

TEMPLATE = app


SOURCES += main.cpp \
    cds.cpp

INCLUDEPATH += /usr/local/include/opencv /usr/local/include

LIBS += -L/usr/local/lib -lopencv_calib3d -lopencv_contrib -lopencv_core -lopencv_features2d -lopencv_flann -lopencv_gpu -lopencv_highgui -lopencv_imgproc -lopencv_legacy -lopencv_ml -lopencv_nonfree -lopencv_objdetect -lopencv_ocl -lopencv_photo -lopencv_stitching -lopencv_superres -lopencv_ts -lopencv_video -lopencv_videostab

HEADERS += \
    cds.h
