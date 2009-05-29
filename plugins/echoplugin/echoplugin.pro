TEMPLATE = lib
CONFIG += plugin
TARGET = echoplugin
INCLUDEPATH += . ../../src/
# DEPENDPATH += . ../../src/

# Input
HEADERS += EchoDictionary.h EchoPlugin.h 
SOURCES += EchoDictionary.cpp EchoPlugin.cpp

OBJECTS_DIR = ../../build
DESTDIR = ../../build
MOC_DIR = ../../build
