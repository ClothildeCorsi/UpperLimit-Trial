#-------------------------------------------------
#
# Project created by QtCreator 2017-05-29T14:06:59
#
#-------------------------------------------------

QT       += core

QT       -= gui

QT       += widgets

TARGET = UpperLimit1
CONFIG   += console
CONFIG   -= app_bundle
CONFIG   += c++11

TEMPLATE = app


SOURCES += main.cpp \
    heliostat.cpp \
    sun.cpp \
    field.cpp \
    dniintegration.cpp \
    nrjintegration.cpp

HEADERS += \
    heliostat.h \
    sun.h \
    field.h \
    DEIntegrationConstants.h \
    DEIntegrator.h \
    dniintegration.h \
    nrjintegration.h
