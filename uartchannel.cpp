#include "uartchannel.h"


void UARTChannel::setDefaultSpeedRange(const QVector<int> &value)
{
    defaultSpeedRange = value;
}

bool UARTChannel::findOffset(Info *infoData)
{
    return true;
}

bool UARTChannel::findData(Info *infoData)
{
    return true;
}

UARTChannel::UARTChannel(SmartDeviceManager *dev, QObject *parent) : IChannel(dev, parent)
{

}


void UARTChannel::setDebugData(dataUART *data, int n)
{
    debugData = data;
    lengthDebugData = n;
}

void UARTChannel::getInfoForDrawing(int begin, int end)
{
    QVector<DataLimit> limits;
    int i;
    const int size = 40;//test
    int nextStart = 0;
    //ToDo
    for(i = 0; i < lengthDebugData - 1 && debugData[i].start < end; ++i)
    {
        if( debugData[i].start >= begin )
        {
            if(debugData[i].start != nextStart && nextStart != 0)
            {
                DataLimit temp = {0, debugData[i].start - nextStart};
                limits.push_back(temp);
            }
            DataLimit temp = {debugData[i].value, size};
            limits.push_back(temp);
            nextStart = debugData[i].start + size;
        }
    }

    //converting to qml
    QVariantList lenArr;
    QVariantList valueArr;
    foreach(DataLimit item, limits)
    {
        qDebug() << item.start << (int)item.type;
        lenArr << item.start;
        valueArr << item.type;
    }
    /*updateDrawingInfo(numCh, type, beginSample, endSample, lenArr, valueArr)*/
    QMetaObject::invokeMethod(widget, "updateDrawingInfo",
            Q_ARG(QVariant, QVariant::fromValue(2)),
            Q_ARG(QVariant, QVariant::fromValue(1)),
            Q_ARG(QVariant, QVariant::fromValue(begin)),
            Q_ARG(QVariant, QVariant::fromValue(end)),
            Q_ARG(QVariant, QVariant::fromValue(lenArr)),
            Q_ARG(QVariant, QVariant::fromValue(valueArr)));

}


