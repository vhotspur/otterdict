TEMPLATE = lib
CONFIG += plugin
QT += network
TARGET = thesauruscomplugin
INCLUDEPATH += . ../../src/
# DEPENDPATH += . ../../src/

# Input
HEADERS += ThesaurusComPlugin.h
SOURCES += ThesaurusComPlugin.cpp

HEADERS += ThesaurusComDictionary.h
SOURCES += ThesaurusComDictionary.cpp

HEADERS += HtmlNode.h ParserSax.h HtmlParser.h
SOURCES += HtmlNode.cpp HtmlParser.cpp

OBJECTS_DIR = ../../build
DESTDIR = ../../build
MOC_DIR = ../../build
