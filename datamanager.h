#ifndef DATAMANAGER_H
#define DATAMANAGER_H

#include <QObject>
#include <QArrayData>

#include <QDebug>

#include "smartdevicemanager.h"

struct DataLimit
{
    int type;// logical 0 or logical 1
    int start;
};

struct Info
{
    int type;// logical 0 or logical 1
    int length;
    Info(int type, int length)
    {
        this->type = type;
        this->length = length;
    }
};

class DataManager : public QObject
{
    Q_OBJECT
private:
    uint frameTime;//time one period conversion in STM
    uint endTime;
    QVector<Info *> decodedData;//data after decoding
    uint numberChannel;//number channel in device

    //manager for communication with STM
    SmartDeviceManager * deviceManager;

    Info * decodeFrame(unsigned char frame);

public:
    explicit DataManager(SmartDeviceManager * dev, uint channel , QObject *parent = 0);

    //get data for next conversion
    char * getDecodedData();
    void decodeData();
    uint getFrameTime();
    uint getEndTime();
    void setNumberChannel(uint value);

signals:

public slots:
};

#endif // DATAMANAGER_H
