QT += core
QT -= gui

CONFIG += c++11

TARGET = Targets
CONFIG += console
CONFIG -= app_bundle

TEMPLATE = app

SOURCES += main.cpp \
    targetconstacceleration.cpp \
    targetconstspeed.cpp \
    ../Utils/distributions/distributions.cpp \
    targetbase.cpp

HEADERS += \
    targetconstacceleration.h \
    targetconstspeed.h \
    ../Utils/distributions/distributions.h \
    targets.h \
    targetbase.h
