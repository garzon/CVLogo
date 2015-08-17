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


SOURCES += \
    cds.cpp \
    ../pso_training/CostFunc/LeastSquareMethod.cpp \
    ../pso_training/CostFunc/SiftCost.cpp \
    ../pso_training/CostFunc/SiftCost_1.cpp \
    ../pso_training/CostFunc/SiftParams.cpp \
    ../pso_training/main.cpp

INCLUDEPATH += /usr/local/include/opencv /usr/local/include

LIBS += -L/usr/local/lib -lopencv_calib3d -lopencv_contrib -lopencv_core -lopencv_features2d -lopencv_flann -lopencv_gpu -lopencv_highgui -lopencv_imgproc -lopencv_legacy -lopencv_ml -lopencv_nonfree -lopencv_objdetect -lopencv_ocl -lopencv_photo -lopencv_stitching -lopencv_superres -lopencv_ts -lopencv_video -lopencv_videostab

HEADERS += \
    cds.h \
    ../pso_training/CostFunc/LeastSquareMethod.h \
    ../pso_training/CostFunc/SiftCost.h \
    ../pso_training/CostFunc/SiftCost_1.h \
    ../pso_training/CostFunc/SiftParams.h \
    ../pso_training/pso/icostfunction.h \
    ../pso_training/pso/IParams.h \
    ../pso_training/pso/particle.h \
    ../pso_training/pso/pso.h

CONFIG += c++11
