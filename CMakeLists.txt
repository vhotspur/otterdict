###
#
# OtterDict application.
#
#
PROJECT(otterdict)

# cmake settings
CMAKE_MINIMUM_REQUIRED(VERSION 2.4.2)
SET(CMAKE_COLOR_MAKEFILE ON)
SET(CMAKE_VERBOSE_MAKEFILE OFF)
SET(CMAKE_INCLUDE_CURRENT_DIR TRUE)

# we required Qt and nothing else
SET(QT_MIN_VERSION "4.5.0")
FIND_PACKAGE(Qt4 REQUIRED)


###
# Common variables setup.
#
# application sources (e.g. not plugin sources)
SET(my_SOURCE_DIR ${CMAKE_CURRENT_SOURCE_DIR}/src)
# directory with dictionary interface header files
SET(my_INCLUDE_DIR_DICTIONARY_CLASSES ${my_SOURCE_DIR})
# directory with web helpers header files
SET(my_INCLUDE_DIR_WEB_HELPER_CLASSES ${my_SOURCE_DIR}/www)
# remove the ending slash in CMAKE_INSTALL_PREFIX path
STRING(REGEX REPLACE "/$" "" CMAKE_INSTALL_PREFIX "${CMAKE_INSTALL_PREFIX}")
# directory where plugins would be installed
SET(my_INSTALLED_PLUGINS_DIR "lib/${PROJECT_NAME}/plugins")


###
# config.h setup
# 
# set path to plugins
SET(my_CONFIG_PLUGINS_PATH "${CMAKE_INSTALL_PREFIX}/${my_INSTALLED_PLUGINS_DIR}")
# generate configh.
CONFIGURE_FILE(${CMAKE_CURRENT_SOURCE_DIR}/src/config.h.cmake ${CMAKE_CURRENT_BINARY_DIR}/src/config.h)

###
#
# Macro to build dictionary plugin.
# @param arg_NAME Name of the plugin.
# @param arg_SOURCES List of source files.
# @param arg_MOC_HEADERS List of (typically) header files that must be
#                        run through moc(1).
#
MACRO(BUILD_DICTIONARY_PLUGIN arg_NAME arg_SOURCES arg_MOC_HEADERS)
	INCLUDE(${QT_USE_FILE})
	# we must pass extra -I option to allow interface header file 
	# inclusion
	QT4_WRAP_CPP(
		my_plugin_MOC_SOURCES 
			${arg_MOC_HEADERS} 
		OPTIONS 
			-I${my_INCLUDE_DIR_DICTIONARY_CLASSES}
	)
	# all files that must be compiled
	SET(my_plugin_ALL_SOURCES ${my_plugin_MOC_SOURCES} ${arg_SOURCES})
	# set include directories
	INCLUDE_DIRECTORIES(
		${QT_INCLUDE_DIR}
		${QT_QTNETWORK_INCLUDE_DIR}
		${my_INCLUDE_DIR_DICTIONARY_CLASSES}
		${my_INCLUDE_DIR_WEB_HELPER_CLASSES}
	)
	# set libraries to link against
	LINK_LIBRARIES(
		${QT_LIBRARIES}
		${QT_QTNETWORK_LIBRARIES}
	)
	
	# these definitions are needed when building Qt plugin
	ADD_DEFINITIONS(${QT_DEFINITIONS})
	ADD_DEFINITIONS(-DQT_PLUGIN)
	ADD_DEFINITIONS(-DQT_NO_DEBUG)
	ADD_DEFINITIONS(-DQT_SHARED)

	# and finally, we build the plugin
	ADD_LIBRARY(${arg_NAME} MODULE ${my_plugin_ALL_SOURCES})
	
	# and we also install it
	INSTALL(
		TARGETS 
			${arg_NAME}
		LIBRARY 
			DESTINATION "${my_INSTALLED_PLUGINS_DIR}"
	)
ENDMACRO(BUILD_DICTIONARY_PLUGIN)


# set up packaging
SET(CPACK_GENERATOR TGZ)
SET(CPACK_SOURCE_GENERATOR TGZ)
SET(CPACK_SOURCE_PACKAGE_FILE_NAME "otterdict-0.1")
SET(CPACK_SOURCE_IGNORE_FILES ".svn/;moc_.*;gendocs/;build;.ignore")
INCLUDE(CPack)

# install the executable, plugins are installed automatically
INSTALL(
	PROGRAMS ${CMAKE_CURRENT_BINARY_DIR}/src/otterdict
	DESTINATION bin
)


# first, compile the plugins...
FOREACH(
	i_PLUGIN_DIRECTORY 
		# plugins/echoplugin 
		plugins/slovnikczplugin 
		plugins/thesauruscomplugin
	)
	ADD_SUBDIRECTORY(${i_PLUGIN_DIRECTORY})
ENDFOREACH(i_PLUGIN_DIRECTORY)

# ...and the the application itself
ADD_SUBDIRECTORY(src)


# that's all
