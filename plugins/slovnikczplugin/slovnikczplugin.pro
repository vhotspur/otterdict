TEMPLATE = lib
CONFIG += plugin
QT += network
TARGET = slovnikczplugin
INCLUDEPATH += . ../../src/ ../../src/www
# DEPENDPATH += . ../../src/

# Input
HEADERS += SlovnikCzPlugin.h
SOURCES += SlovnikCzPlugin.cpp

HEADERS += SlovnikCzDictionary.h
SOURCES += SlovnikCzDictionary.cpp

OBJECTS_DIR = ../../build
DESTDIR = ../../build
MOC_DIR = ../../build
