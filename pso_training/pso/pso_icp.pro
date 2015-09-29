TEMPLATE = app
CONFIG += console
CONFIG -= app_bundle
CONFIG -= qt

SOURCES += main.cpp \
    pso_icp.cpp \
    particle.cpp \
    costfunctiondemo.cpp

HEADERS += \
    pso_icp.h \
    particle.h \
    icostfunction.h \
    costfunctiondemo.h

LIBS += /usr/local/lib/*.so

CONFIG += c++11
