﻿#ifndef EMGDATARECORDER_H
#define EMGDATARECORDER_H

#include <QDir>
#include <QObject>
#include <QFile>
#include <QStandardPaths>
#include <QDebug>
#include <QDateTime>
#include "Utils.h"

class EmgDataRecorder : public QObject
{
    Q_OBJECT
public:
    static EmgDataRecorder* instance();
    static void destroyInstance();
    ~EmgDataRecorder();

public slots:
    void onStartRecord();
    void onStopRecord();
    void onOrignalDataComming(QByteArray data);

private:
    explicit EmgDataRecorder(QObject *parent = nullptr);

private:
    static EmgDataRecorder* m_instance;

private:
    QFile*   m_recordFile;
};

#endif // EMGDATARECORDER_H
