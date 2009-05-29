TEMPLATE = app
TARGET = otterdict
DEPENDPATH += . 
INCLUDEPATH += .

# Input
HEADERS += ActionZone.h DictionaryShelfPluginInterface.h Dictionary.h TranslationResultsViewer.h PluginManager.h
SOURCES += main.cpp PluginManager.cpp

OBJECTS_DIR = ../build
DESTDIR = ../build
MOC_DIR = ../build

