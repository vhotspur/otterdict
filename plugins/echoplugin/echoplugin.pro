TEMPLATE = lib
CONFIG += plugin
TARGET = echoplugin
INCLUDEPATH += . ../../src/
# DEPENDPATH += . ../../src/

# Input
HEADERS += EchoDictionary.h ReverseDictionary.h EchoPlugin.h 
SOURCES += EchoDictionary.cpp ReverseDictionary.cpp EchoPlugin.cpp

OBJECTS_DIR = ../../build
DESTDIR = ../../build
MOC_DIR = ../../build
