QT += core
QT -= gui

CONFIG += c++11

TARGET = Locator
CONFIG += console
CONFIG -= app_bundle

TEMPLATE = app

SOURCES += main.cpp \
    locator.cpp \
    ../Utils/config_handler/jsonparser.cpp \
    ../Utils/config_handler/paramsraw.cpp

HEADERS += \
    locator.h \
    ../Utils/config_handler/jsonparser.h \
    ../Utils/config_handler/paramsraw.h
