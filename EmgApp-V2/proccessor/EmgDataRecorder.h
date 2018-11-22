#ifndef EMGDATARECORDER_H
#define EMGDATARECORDER_H

#include <QDir>
#include <QObject>
#include <QFile>
#include <QStandardPaths>
#include <QDebug>
#include <QDateTime>

class EmgDataRecorder : public QObject
{
    Q_OBJECT
public:
    static EmgDataRecorder* instance();

public slots:
    void onStartRecord();
    void onStopRecord();
    void onOrignalDataComming(QByteArray& data);

private:
    explicit EmgDataRecorder(QObject *parent = 0);

private:
    static EmgDataRecorder* m_instance;

private:
    QFile*   m_recordFile;
};

#endif // EMGDATARECORDER_H
