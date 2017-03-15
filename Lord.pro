QT += core network
QT -= gui

CONFIG += c++11

TARGET = Lord
CONFIG += console
CONFIG -= app_bundle

TEMPLATE = app

SOURCES += main.cpp \
    lord.cpp \
    Libs/Locator/locator.cpp \
    Libs/Receivers/receiverbase.cpp \
    Libs/Receivers/receiverradio.cpp \
    Libs/Targets/targetbase.cpp \
    Libs/Targets/targetconstacceleration.cpp \
    Libs/Targets/targetconstspeed.cpp \
    Libs/TcpServer/server.cpp \
    Libs/TcpServer/tcpclient.cpp \
    Libs/Utils/config_handler/jsonparser.cpp \
    Libs/Utils/config_handler/paramsraw.cpp \
    Libs/Time/time.cpp \
    Libs/Writers/writerfile.cpp

# The following define makes your compiler emit warnings if you use
# any feature of Qt which as been marked deprecated (the exact warnings
# depend on your compiler). Please consult the documentation of the
# deprecated API in order to know how to port your code away from it.
DEFINES += QT_DEPRECATED_WARNINGS

# You can also make your code fail to compile if you use deprecated APIs.
# In order to do so, uncomment the following line.
# You can also select to disable deprecated APIs only up to a certain version of Qt.
#DEFINES += QT_DISABLE_DEPRECATED_BEFORE=0x060000    # disables all the APIs deprecated before Qt 6.0.0

HEADERS += \
    lord.h \
    Libs/Locator/locator.h \
    Libs/Receivers/receiverbase.h \
    Libs/Receivers/receiverradio.h \
    Libs/Receivers/receivers.h \
    Libs/Targets/targetbase.h \
    Libs/Targets/targetconstacceleration.h \
    Libs/Targets/targetconstspeed.h \
    Libs/TcpServer/server.h \
    Libs/TcpServer/tcpclient.h \
    Libs/Utils/config_handler/jsonparser.h \
    Libs/Utils/config_handler/paramsraw.h \
    Libs/Targets/targets.h \
    Libs/Time/time.h \
    Libs/Writers/writerfile.h \
    Libs/Writers/writers.h
