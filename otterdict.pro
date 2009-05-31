TEMPLATE = subdirs
SUBDIRS = src plugins

TARGET = otterdict
DEPENDPATH += . src
INCLUDEPATH += . src

# Add `make docs' target for Doxygen
dox.target = docs
dox.commands = doxygen Doxyfile
QMAKE_EXTRA_UNIX_TARGETS += dox
