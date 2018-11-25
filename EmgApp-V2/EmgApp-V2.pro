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
    proccessor/EmgDataReceiver.cpp \
    proccessor/EmgDataRecorder.cpp \
    ui/PlotWidget.cpp \
    ui/RunningControlBtn.cpp \
    Application.cpp \
    util/Utils.cpp \
    AppContext.cpp \
    ui/CustomShadowEffect.cpp \
    ui/SettingDlg.cpp \
    log/Logger.cpp \
    ui/MenuControlBtn.cpp \
    ui/FullscreenControlBtn.cpp

HEADERS  += \
    ui/MainWindow.h \
    ui/QCustomPlot.h \
    ui/StartDlg.h \
    Defines.h \
    proccessor/EmgDataReceiver.h \
    proccessor/EmgDataRecorder.h \
    ui/PlotWidget.h \
    ui/RunningControlBtn.h \
    Application.h \
    util/Utils.h \
    AppContext.h \
    ui/CustomShadowEffect.h \
    ui/SettingDlg.h \
    log/Logger.h \
    ui/MenuControlBtn.h \
    ui/FullscreenControlBtn.h

FORMS    += \
    ui/MainWindow.ui \
    ui/StartDlg.ui \
    ui/SettingDlg.ui
    ui/MainWindow.ui


INCLUDEPATH += \
    ui/ \
    proccessor/ \
    util/ \
    log/

DISTFILES += \
    EmgApp-V2.pro.user

#DEFINES += QCUSTOMPLOT_USE_OPENGL
