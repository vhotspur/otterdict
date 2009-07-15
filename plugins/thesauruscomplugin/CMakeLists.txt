###
#
# Thesaurus.com dictionary plugin
#

SET(
	my_thesauruscomplugin_SOURCES
		ThesaurusComPlugin.cpp
		ThesaurusComDictionary.cpp
)
SET(
	my_thesauruscomplugin_MOC_HEADERS
		ThesaurusComPlugin.h
		ThesaurusComDictionary.h
)

BUILD_DICTIONARY_PLUGIN(
	"thesauruscomplugin" 
	"${my_thesauruscomplugin_SOURCES}"
	"${my_thesauruscomplugin_MOC_HEADERS}"
)
