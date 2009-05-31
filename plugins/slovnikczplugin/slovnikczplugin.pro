TEMPLATE = lib
CONFIG += plugin
TARGET = slovnikczplugin
INCLUDEPATH += . ../../src/
# DEPENDPATH += . ../../src/

# Input
HEADERS += SlovnikCzPlugin.h
SOURCES += SlovnikCzPlugin.cpp

HEADERS += SlovnikCzDictionary.h
SOURCES += SlovnikCzDictionary.cpp

OBJECTS_DIR = ../../build
DESTDIR = ../../build
MOC_DIR = ../../build
