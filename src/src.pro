TEMPLATE = app
TARGET = otterdict
CONFIG += debug
DEPENDPATH += . 
INCLUDEPATH += .

# Input
HEADERS += ActionZone.h DictionaryShelfPluginInterface.h Dictionary.h TranslationResultsViewer.h PluginManager.h
SOURCES += main.cpp ActionZone.cpp TranslationResultsViewer.cpp PluginManager.cpp

OBJECTS_DIR = ../build
DESTDIR = ../build
MOC_DIR = ../build

