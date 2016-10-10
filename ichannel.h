#ifndef ICHANNEL_H
#define ICHANNEL_H

#include <QObject>
#include <QVector>
#include <QVariant>
#include <QVariantList>
#include <QQuickWindow>


#include <QDebug>
#include "datamanager.h"

class IChannel : public QObject
{
    Q_OBJECT
protected:
    int *  debugData;
    int     lengthDebugData;
    SmartDeviceManager * device;
    QQuickWindow *widget;//for qml method
protected:
    virtual bool findOffset(Info * infoData);
    virtual bool findData(Info * infoData);
public:
    explicit IChannel(SmartDeviceManager * dev, QObject *parent = 0);
    void setWidget(QQuickWindow * window);

    //decode info from array to protocol
    //return false, when error occured
    bool decodeInfo(Info * infoData);

    void setDebugData(int * debugData, int length);

signals:
    void createdInfoForDrawing(QVariant a, QVariant b);
public slots:
    //get primitive for drawing in UI
    //@param begin   - start point
    //@param end     -   end point
    virtual void getInfoForDrawing(int begin, int end);
};

#endif // ICHANNEL_H
