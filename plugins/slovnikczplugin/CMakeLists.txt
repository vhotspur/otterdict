###
#
# Slovnik.cz dictionary plugin
#

SET(
	my_slovnikczplugin_SOURCES
		SlovnikCzPlugin.cpp
		SlovnikCzDictionary.cpp
)
SET(
	my_slovnikczplugin_MOC_HEADERS
		SlovnikCzPlugin.h
		SlovnikCzDictionary.h
)

BUILD_DICTIONARY_PLUGIN(
	"slovnikczplugin" 
	"${my_slovnikczplugin_SOURCES}"
	"${my_slovnikczplugin_MOC_HEADERS}"
)
