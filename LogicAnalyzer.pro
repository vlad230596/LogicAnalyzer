TEMPLATE = app

QT += qml quick widgets
QT += serialport

CONFIG += c++11
QT_LABS_CONTROLS_STYLE=material
SOURCES += main.cpp \
    bitchannel.cpp \
    datamanager.cpp \
    devicemanager.cpp \
    i2cchannel.cpp \
    ichannel.cpp \
    uartchannel.cpp \
    smartdevicemanager.cpp

RESOURCES += qml.qrc

# Additional import path used to resolve QML modules in Qt Creator's code model
QML_IMPORT_PATH =

# Default rules for deployment.
include(deployment.pri)

HEADERS += \
    bitchannel.h \
    datamanager.h \
    devicemanager.h \
    i2cchannel.h \
    ichannel.h \
    uartchannel.h \
    smartdevicemanager.h

DISTFILES +=
