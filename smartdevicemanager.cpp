#include "smartdevicemanager.h"


SmartDeviceManager::SmartDeviceManager(QString &deviceName, int speedDevice, QObject *parent) : DeviceManager(deviceName, speedDevice, parent)
{
    isConnected = false;
}

bool SmartDeviceManager::connect()
{
    if(!isConnected)
        isConnected = DeviceManager::connect();
    return isConnected;
}

bool SmartDeviceManager::loadData(uint channel)
{
    bool flag = false;
    if(!isBusy)
    {
        isBusy = true;
        flag = DeviceManager::loadData(channel);
        isBusy = false;
    }
    return flag;
}

bool SmartDeviceManager::startSession()
{
    if(!isStartSession)
    {
        isStartSession = DeviceManager::startSession();
    }
    return isStartSession;
}

bool SmartDeviceManager::setDuration(uint value)
{
    if(!isBusy)
    {
       DeviceManager::setDuration(value);
       return true;
    }
    return false;
}

char *SmartDeviceManager::getSourceData(uint channel)
{
    char * temp = NULL;
    if(!isBusy)
    {
        isBusy = true;
        temp = DeviceManager::getSourceData(channel);
        isBusy = false;
    }
    return temp;
}
