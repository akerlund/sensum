#-------------------------------------------------
#
# Project created by QtCreator 2017-04-19T20:29:28
#
#-------------------------------------------------

QT       += core gui
QT       += printsupport
QT       += serialport

greaterThan(QT_MAJOR_VERSION, 4): QT += widgets

TARGET = STM_Sensors
TEMPLATE = app


SOURCES  += main.cpp\
            mainwindow.cpp \
            qcustomplot.cpp \
            custom_plots.cpp \
    rx_unpacking.cpp

HEADERS  += mainwindow.h \
            qcustomplot.h \
            custom_plots.h \
    rx_unpacking.h

FORMS    += mainwindow.ui
