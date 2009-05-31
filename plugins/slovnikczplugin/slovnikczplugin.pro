TEMPLATE = lib
CONFIG += plugin
QT += network
TARGET = slovnikczplugin
INCLUDEPATH += . ../../src/
# DEPENDPATH += . ../../src/

# Input
HEADERS += SlovnikCzPlugin.h
SOURCES += SlovnikCzPlugin.cpp

HEADERS += SlovnikCzDictionary.h
SOURCES += SlovnikCzDictionary.cpp

HEADERS += HtmlNode.h ParserSax.h HtmlParser.h
SOURCES += HtmlNode.cpp HtmlParser.cpp

OBJECTS_DIR = ../../build
DESTDIR = ../../build
MOC_DIR = ../../build
