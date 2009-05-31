TEMPLATE = lib
CONFIG += plugin
QT += network
TARGET = thesauruscomplugin
INCLUDEPATH += . ../../src/ ../../src/www/
# DEPENDPATH += . ../../src/

# Input
HEADERS += ThesaurusComPlugin.h
SOURCES += ThesaurusComPlugin.cpp

HEADERS += ThesaurusComDictionary.h
SOURCES += ThesaurusComDictionary.cpp


OBJECTS_DIR = ../../build
DESTDIR = ../../build
MOC_DIR = ../../build
