#include <QApplication>
#include <QQmlApplicationEngine>

#include <QObject>
#include <QQuickWindow>
#include <QQmlContext>


#include <QDebug>

#include "bitchannel.h"
#include "uartchannel.h"

#include <QtSerialPort/QSerialPortInfo>

#define CURRENT_PORT "COM3"
#define CURRENT_DEVICE_SPEED 115200

#define DEBUG_MAX_SIZE_DATA 4096
#define DEBUG_EXAMPLE_LIMIT 200

int main(int argc, char *argv[])
{
    QApplication app(argc, argv);


    QQmlApplicationEngine engine;
    engine.load(QUrl(QStringLiteral("qrc:/main.qml")));

    QObject *topLevel = engine.rootObjects().value(0);
    QQuickWindow *window = qobject_cast<QQuickWindow *>(topLevel);

    QVariantList listPorts;
    foreach (QSerialPortInfo item, QSerialPortInfo::availablePorts())
        listPorts << item.portName();
    QMetaObject::invokeMethod(window, "setPorts",
            Q_ARG(QVariant, QVariant::fromValue(listPorts)));

    QVariantList listBaudRates;
    foreach (qint32 item, QSerialPortInfo::standardBaudRates())
        listBaudRates << item;
    QMetaObject::invokeMethod(window, "setBaudRates",
            Q_ARG(QVariant, QVariant::fromValue(listBaudRates)));


    QString str(CURRENT_PORT);
    SmartDeviceManager dev(str, CURRENT_DEVICE_SPEED);

    BitChannel bitCh1(&dev);

    QFile file("C://test.txt");
    file.open(QFile::ReadOnly);
    QTextStream stream(&file);
    int testDataBit[DEBUG_MAX_SIZE_DATA];
    int value;
    int i = 0;
    while(!stream.atEnd())
    {
        stream >> value;
        testDataBit[i++] = value;
    }
    file.close();
    bitCh1.setDebugData(testDataBit, i);


    UARTChannel uartCh2(&dev);
    file.setFileName("C://testUart.txt");
    file.open(QFile::ReadOnly);
    stream.setDevice(&file);
    dataUART testDataUart[4096];
    int value1, value2;
    i = 0;
    while(!stream.atEnd())
    {
        stream >> value1 >> value2;
        dataUART temp = {value1, value2};
        testDataUart[i++] = temp;
    }
    uartCh2.setDebugData(testDataUart, i);



    bitCh1.setWidget(window);
    uartCh2.setWidget(window);
    bitCh1.getInfoForDrawing(0, DEBUG_EXAMPLE_LIMIT);
    uartCh2.getInfoForDrawing(0, DEBUG_EXAMPLE_LIMIT);

    // qml to c++
    QObject::connect(window, SIGNAL(getDrawingInfo(int, int)),
                         &bitCh1, SLOT(getInfoForDrawing(int, int)));
    QObject::connect(window, SIGNAL(getDrawingInfo(int, int)),
                         &uartCh2, SLOT(getInfoForDrawing(int, int)));


    file.close();
    return app.exec();
}
