# Makefile for OtterDict
PROJECTNAME=otterdict
VERSION=0.1
DISTNAME=$(PROJECTNAME)-$(VERSION)
DISTARCHIVE=$(DISTNAME).tar.gz
BUILDDIR=build

QMAKE=qmake
QMAKECMD=$(QMAKE) -unix -o $(MAKEFILE)
MAKEFILE=Makefile
MAKEARCHIVE=tar -czf

RM=rm -f
RM_R=rm -Rf
MKDIR=mkdir -p
CP=cp

all: compiledict compileplugins

compiledict: src/$(MAKEFILE)
	cd src && $(MAKE)

compileplugins: plugins/$(MAKEFILE)
	cd plugins && $(MAKE)

src/$(MAKEFILE): src/src.pro
	cd src; $(QMAKECMD) src.pro
plugins/$(MAKEFILE): plugins/plugins.pro
	cd plugins; $(QMAKECMD) plugins.pro
	
clean:
	cd $(BUILDDIR) && $(RM) *

dist:
	$(MKDIR) $(DISTNAME)
	$(CP) Makefile Doxyfile otterdict.ottproj $(DISTNAME)
	
	$(MKDIR) $(DISTNAME)/src
	$(CP) \
		src/*.cpp \
		src/*.h \
		src/src.pro \
		src/*.xpm \
		$(DISTNAME)/src
	
	$(MKDIR) $(DISTNAME)/src/www
	$(CP) \
		src/www/*.cpp \
		src/www/*.h \
		$(DISTNAME)/src/www
	
	
	$(MKDIR) $(DISTNAME)/plugins
	$(CP) plugins/plugins.pro $(DISTNAME)/plugins
	
	$(MKDIR) $(DISTNAME)/plugins/echoplugin
	$(CP) \
		plugins/echoplugin/*.cpp \
		plugins/echoplugin/*.h \
		plugins/echoplugin/echoplugin.pro \
		$(DISTNAME)/plugins/echoplugin
	
	$(MKDIR) $(DISTNAME)/plugins/slovnikczplugin
	$(CP) \
		plugins/slovnikczplugin/*.cpp \
		plugins/slovnikczplugin/*.h \
		plugins/slovnikczplugin/slovnikczplugin.pro \
		$(DISTNAME)/plugins/slovnikczplugin
	
	$(MKDIR) $(DISTNAME)/plugins/thesauruscomplugin
	$(CP) \
		plugins/thesauruscomplugin/*.cpp \
		plugins/thesauruscomplugin/*.h \
		plugins/thesauruscomplugin/thesauruscomplugin.pro \
		$(DISTNAME)/plugins/thesauruscomplugin
	
	
	$(MAKEARCHIVE) $(DISTARCHIVE) $(DISTNAME)
	
	$(RM_R) $(DISTNAME)


docs:
	@which doxygen 1>/dev/null
	doxygen Doxyfile



