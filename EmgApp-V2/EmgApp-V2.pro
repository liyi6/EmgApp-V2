#-------------------------------------------------
#
# Project created by QtCreator 2018-11-22T16:15:25
#
#-------------------------------------------------

QT       += core gui network printsupport

greaterThan(QT_MAJOR_VERSION, 4): QT += widgets

CONFIG += debug_and_release
CONFIG(debug, debug|release){
    DESTDIR = $$PWD/bin/debug
} else {
    DESTDIR = $$PWD/bin/release
}

TARGET = EmgApp-V2
TEMPLATE = app


SOURCES += main.cpp\
    ui/MainWindow.cpp \
    ui/QCustomPlot.cpp \
    ui/StartDlg.cpp \
    proccessor/EmgDataReceiver.cpp

HEADERS  += \
    ui/MainWindow.h \
    ui/QCustomPlot.h \
    ui/StartDlg.h \
    Defines.h \
    proccessor/EmgDataReceiver.h

FORMS    += \
    ui/MainWindow.ui \
    ui/StartDlg.ui
    ui/MainWindow.ui


INCLUDEPATH += \
    ui/ \
    processor/

DISTFILES += \
    EmgApp-V2.pro.user
