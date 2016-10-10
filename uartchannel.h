#ifndef UARTCHANNEL_H
#define UARTCHANNEL_H

#include "ichannel.h"

struct dataUART
{
    int start;
    int value;
};

class UARTChannel : public IChannel
{
private:
    uint speed;//baudrate
    dataUART * debugData;
    QVector<int> defaultSpeedRange;
private:
    //from IChannel
    bool findOffset(Info * infoData);
    bool findData(Info * infoData);
public:
    UARTChannel(SmartDeviceManager * dev, QObject * parent = 0);
    bool findSpeed();//false - error with data

    void setDebugData(dataUART * debugData, int n);

    void setDefaultSpeedRange(const QVector<int> &value);

public slots:
    void getInfoForDrawing(int begin, int end);
};
#endif // UARTCHANNEL_H
