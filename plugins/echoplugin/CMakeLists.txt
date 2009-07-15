###
#
# Testing echo plugin
#

SET(
	my_echoplugin_SOURCES
		EchoPlugin.cpp
		EchoDictionary.cpp
		ReverseDictionary.cpp
)
SET(
	my_echoplugin_MOC_HEADERS
		EchoPlugin.h
		EchoDictionary.h
		ReverseDictionary.h
)

BUILD_DICTIONARY_PLUGIN(
	"echoplugin" 
	"${my_echoplugin_SOURCES}"
	"${my_echoplugin_MOC_HEADERS}"
)
