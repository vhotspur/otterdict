TEMPLATE = app
TARGET = otterdict
CONFIG += debug
QT += network
DEPENDPATH += . 
INCLUDEPATH += .
LIBS += -rdynamic

# Input
HEADERS += ActionZone.h DictionaryShelfPluginInterface.h Dictionary.h TranslationResultsViewer.h PluginManager.h
SOURCES += main.cpp ActionZone.cpp TranslationResultsViewer.cpp PluginManager.cpp


HEADERS += www/WebPage.h www/HtmlNode.h www/HtmlParser.h www/ParserSax.h www/tree.h
SOURCES += www/WebPage.cpp www/HtmlNode.cpp www/HtmlParser.cpp


OBJECTS_DIR = ../build
DESTDIR = ../build
MOC_DIR = ../build

