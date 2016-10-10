#ifndef SMARTDEVICEMANAGER_H
#define SMARTDEVICEMANAGER_H
#include "devicemanager.h"

/*
 *   bool connect();
    //load all data from channel
    bool loadData(uint channel);
    //try start session(send comand to STM)
    bool startSession();
    void setDuration(uint value);
    char * getSourceData(uint channel);
    uint getCountChannel();
*/

class SmartDeviceManager : public DeviceManager
{
private:
    bool isBusy;
    bool isConnected;
    bool isStartSession;
public:
    SmartDeviceManager(QString & deviceName, int speedDevice, QObject *parent = 0);
    bool connect();
       //load all data from channel
    bool loadData(uint channel);
       //try start session(send comand to STM)
    bool startSession();
    bool setDuration(uint value);
    char * getSourceData(uint channel);
};

#endif // SMARTDEVICEMANAGER_H
