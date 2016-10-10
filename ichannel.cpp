#include "ichannel.h"

void IChannel::setWidget(QQuickWindow * window)
{
    widget = window;
}


bool IChannel::findOffset(Info *infoData)
{
    return true;
}

bool IChannel::findData(Info *infoData)
{
    return true;
}

IChannel::IChannel(SmartDeviceManager *dev, QObject *parent) : QObject(parent)
{
    device = dev;
}


bool IChannel::decodeInfo(Info * infoData)
{
    if(findOffset(infoData))
        return findData(infoData);
    return false;
}

void IChannel::getInfoForDrawing(int begin, int end)
{
    //empty; released in children
}

void IChannel::setDebugData(int * data, int length)
{
    debugData = data;
    lengthDebugData = length;
}


