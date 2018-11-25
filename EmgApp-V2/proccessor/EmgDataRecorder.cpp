#include "EmgDataRecorder.h"

EmgDataRecorder* EmgDataRecorder::m_instance = NULL;

EmgDataRecorder::EmgDataRecorder(QObject *parent)
    : QObject(parent),
      m_recordFile(NULL)
{

}

EmgDataRecorder *EmgDataRecorder::instance()
{
    if (!m_instance) {
        m_instance = new EmgDataRecorder;
    }
    return m_instance;
}

EmgDataRecorder::~EmgDataRecorder()
{
    onStopRecord();

    qDebug() << "~EmgDataRecorder() called.";
}

void EmgDataRecorder::onOrignalDataComming(QByteArray data)
{
    if (m_recordFile) {
        m_recordFile->write(data);
    } else {
        qWarning() << "Data is comming while record file is not exist.";
    }
}

void EmgDataRecorder::onStartRecord()
{
    QDir recordFileDir;
    recordFileDir.mkpath(Utils::getAppHomeDir()+ "/save/");
    QString recordFilePath = QString(Utils::getAppHomeDir() + "/save/" + "emg-%1").arg(QDateTime::currentDateTime().toString("yyyy-MM-dd-hh-mm-ss") + ".dat");
    qDebug() << "Create a new record file, path:" << recordFilePath;

    m_recordFile = new QFile(recordFilePath);
    if (!m_recordFile->open(QIODevice::WriteOnly | QIODevice::Truncate)) {
        qWarning() << "Fail to Open record file.";
        m_recordFile = NULL;
        return;
    }
}

void EmgDataRecorder::onStopRecord()
{
    if (m_recordFile) {
        m_recordFile->close();
        m_recordFile = NULL;
    } else {
        qWarning() << "To stop record while record file is not exist.";
    }
}
