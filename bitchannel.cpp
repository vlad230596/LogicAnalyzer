#include "bitchannel.h"

bool BitChannel::findOffset(Info *infoData)
{
    return true;
}

bool BitChannel::findData(Info *infoData)
{
    return true;
}

BitChannel::BitChannel(SmartDeviceManager *dev, QObject *parent) : IChannel(dev, parent)
{

}

void BitChannel::getInfoForDrawing(int begin, int end)
{
    QVector<DataLimit> limits;
    int startValue = debugData[0];
    int i;
    for(i = 1; debugData[i] < begin; ++i);
    int realValue = i % 2 ? startValue : 1 - startValue;
    int prev = begin;
    for(; i < lengthDebugData - 1 && debugData[i] < end; ++i)
    {
        DataLimit temp = {realValue, debugData[i] - prev};
        limits.push_back(temp);
        realValue = 1 - realValue;
        prev = debugData[i];
    }
    if(i == lengthDebugData - 1)//must be 0
    {
        DataLimit temp = {-1, end - prev};
        limits.push_back(temp);
    }
    else
    {
        DataLimit temp = {realValue, end - prev};
        limits.push_back(temp);
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
            Q_ARG(QVariant, QVariant::fromValue(1)),
            Q_ARG(QVariant, QVariant::fromValue(0)),
            Q_ARG(QVariant, QVariant::fromValue(begin)),
            Q_ARG(QVariant, QVariant::fromValue(end)),
            Q_ARG(QVariant, QVariant::fromValue(lenArr)),
            Q_ARG(QVariant, QVariant::fromValue(valueArr)));
}

