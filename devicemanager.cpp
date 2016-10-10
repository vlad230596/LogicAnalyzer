#include "devicemanager.h"



DeviceManager::DeviceManager(QString &deviceName, int speedDevice, QObject *parent) : QObject(parent)
{
    //open port
}

bool DeviceManager::connect()
{
    //send test command
}

bool DeviceManager::loadData(uint channel)
{
    //recieve data from stm32
}

bool DeviceManager::startSession()
{
    //send command stm32
    return false;
}

void DeviceManager::setDuration(uint value)
{
    durationConversion = value;
}

char *DeviceManager::getSourceData(uint channel)
{
    return sourceData.at(channel);
}

uint DeviceManager::getCountChannel()
{
    return sourceData.length();
}

