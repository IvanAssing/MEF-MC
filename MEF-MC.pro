#-------------------------------------------------
#
# Project created by QtCreator 2013-01-22T10:10:34
#
#-------------------------------------------------

QT       += core gui

greaterThan(QT_MAJOR_VERSION, 4): QT += widgets

TARGET = MEF-MC
TEMPLATE = app


SOURCES += main.cpp\
        mainwindow.cpp \
    node.cpp \
    element.cpp \
    mesh.cpp \
    boundarynode.cpp \
    boundaryelement.cpp \
    polynomial1d.cpp \
    polynomial2d.cpp \
    functor2d.cpp

HEADERS  += mainwindow.h \
    node.h \
    element.h \
    mesh.h \
    boundarynode.h \
    boundaryelement.h \
    polynomial1d.h \
    polynomial2d.h \
    functor2d.h

FORMS    += mainwindow.ui
