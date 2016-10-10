#ifndef DEVICEMANAGER_H
#define DEVICEMANAGER_H

#include <QObject>
#include <QVector>

#define MAX_DURATION 0xFFFFFFFF

class DeviceManager : public QObject
{
    Q_OBJECT
    QString nameDevice;//COM1 ... COMN
    uint speedDevice;//baudrate
    uint durationConversion = MAX_DURATION;//for future
public:
    QVector <char *> sourceData;//for test
public:
    explicit DeviceManager(QString & deviceName, int speedDevice, QObject *parent = 0);

    //connecting with device
    bool connect();
    //load all data from channel
    bool loadData(uint channel);
    //try start session(send comand to STM)
    bool startSession();
    void setDuration(uint value);
    char * getSourceData(uint channel);
    uint getCountChannel();
signals:

public slots:
};

#endif // DEVICEMANAGER_H
