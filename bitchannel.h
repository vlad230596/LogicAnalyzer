#ifndef BITCHANNEL_H
#define BITCHANNEL_H

#include "ichannel.h"



class BitChannel : public IChannel
{
private:
    //from IChannel
    bool findOffset(Info * infoData);
    bool findData(Info * infoData);
public:
    BitChannel(SmartDeviceManager * dev, QObject * parent = 0);

private:
    DataManager  * dataManager;
public slots:
    void getInfoForDrawing(int begin, int end);
};

#endif // BITCHANNEL_H
