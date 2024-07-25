#-------------------------------------------------
#
# Project created by QtCreator 2024-07-16T14:29:12
#
#-------------------------------------------------

QT       += core gui axcontainer printsupport widgets
CONFIG   += qaxcontainer
QMAKE_CXXFLAGS+=-std=c++0x

CONFIG+=c++11

greaterThan(QT_MAJOR_VERSION, 4): QT += widgets

TARGET = Software_618_Project
TEMPLATE = app


SOURCES += main.cpp\
        mainwindow.cpp \
    userinterface.cpp \
    qcustomplot.cpp \
    excelread.cpp \
    configuredialog.cpp \
    simplegraph.cpp \
    asynchronousonebufferedai.cpp

HEADERS  += mainwindow.h \
    userinterface.h \
    qcustomplot.h \
    excelread.h \
    configuredialog.h \
    simplegraph.h \
    asynchronousonebufferedai.h \
    Worker.h

FORMS    += mainwindow.ui \
    userinterface.ui \
    configuredialog.ui \
    asynchronousonebufferedai.ui

#msvc {
#    QMAKE_CFLAGS += /utf-8
#    QMAKE_CXXFLAGS += /utf-8
#}
#QMAKE_CXXFLAGS += /utf-8

unix:win32: LIBS += -lbiodaq

RESOURCES += \
    Resources/software_618_project.qrc
