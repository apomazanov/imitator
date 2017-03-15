QT += core
QT -= gui

CONFIG += c++11

TARGET = Receiver
CONFIG += console
CONFIG -= app_bundle

TEMPLATE = app

SOURCES += main.cpp \
    ../Utils/config_handler/jsonparser.cpp \
    ../Utils/config_handler/paramsraw.cpp \
    receiverbase.cpp \
    receiverradio.cpp

HEADERS += \
    ../Utils/config_handler/jsonparser.h \
    ../Utils/config_handler/paramsraw.h \
    receiverbase.h \
    ../Targets/targets.h \
    receivers.h \
    receiverradio.h
