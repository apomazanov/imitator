QT += core
QT -= gui

CONFIG += c++11

TARGET = Targets
CONFIG += console
CONFIG -= app_bundle

TEMPLATE = app

SOURCES += main.cpp \
    basetarget.cpp \
    targetconstacceleration.cpp \
    targetconstspeed.cpp \
    ../Utils/distributions/distributions.cpp

HEADERS += \
    basetarget.h \
    targetconstacceleration.h \
    targetconstspeed.h \
    ../Utils/distributions/distributions.h
