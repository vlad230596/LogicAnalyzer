#ifndef I2CCHANNEL_H
#define I2CCHANNEL_H

#include "ichannel.h"

class I2CChannel : public IChannel
{
    uint frameInterval;//frame in protocol
private:
    //from IChannel
    bool findOffset(Info * infoData);
    bool findData(Info * infoData);
public:
    I2CChannel(SmartDeviceManager * dev, QObject *parent = 0);
    bool findInterval();//false - error with data
    uint getInterval();


public slots:
    void getInfoForDrawing(int begin, int end);
};

#endif // I2CCHANNEL_H
