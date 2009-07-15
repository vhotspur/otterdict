INCLUDE(${QT_USE_FILE})

SET(
	my_SOURCES
		ActionZone.cpp
		PluginManager.cpp
		TranslationResultsViewer.cpp
		main.cpp
		www/HtmlNode.cpp
		www/HtmlParser.cpp
		www/WebPage.cpp
)

SET(
	my_MOC_HEADERS
		ActionZone.h
		TranslationResultsViewer.h
		www/WebPage.h
)
QT4_WRAP_CPP(my_MOC_SOURCES ${my_MOC_HEADERS} OPTIONS -DMY_DEF)

SET(
	my_ALL_SOURCES 
		${my_MOC_SOURCES}
		${my_SOURCES}
)


INCLUDE_DIRECTORIES(
	${QT_INCLUDE_DIR}
	${QT_QTNETWORK_INCLUDE_DIR}
)

LINK_LIBRARIES(
	${QT_LIBRARIES}
	${QT_QTNETWORK_LIBRARIES}
)

# this is need to include class WebPage etc. even if they are not
# used (well, it is not very good description of the problem but it
# took me several hours to find out that this switch solves problem
# when loading plugins)
ADD_DEFINITIONS(-rdynamic)

ADD_EXECUTABLE(otterdict ${my_ALL_SOURCES})
