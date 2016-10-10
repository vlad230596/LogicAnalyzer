#include "datamanager.h"

//bit 7 - logical value(0/1)
//bits 6:0 = value
#define MASK_FRAME (1 << 7)

Info * DataManager::decodeFrame(unsigned char frame)
{
    unsigned char bit = (frame & MASK_FRAME) >> 7;
    unsigned char value = frame & (~MASK_FRAME);
    return new Info(bit, value);
}

DataManager::DataManager(SmartDeviceManager *dev, uint channel, QObject *parent) : deviceManager(dev), numberChannel(channel)
{

}

void DataManager::decodeData()
{
    char  * source = deviceManager-> getSourceData(numberChannel);
    int i = 0;
    while(source[i])
    {
        Info * temp = decodeFrame(source[i]);
        if(decodedData.length() && decodedData.last()->type == temp->type)
            decodedData.last()->length += temp->length;
        else
            decodedData.push_back(temp);
        i++;
    }
    foreach (Info * item, decodedData)
    {
        qDebug() << item->type << item->length;
    }
}
