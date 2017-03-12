QT += core
QT -= gui

CONFIG += c++11

TARGET = config_handler
CONFIG += console
CONFIG -= app_bundle

TEMPLATE = app

SOURCES += main.cpp \
    jsonparser.cpp \
    paramsraw.cpp

HEADERS += \
    jsonparser.h \
    paramsraw.h
