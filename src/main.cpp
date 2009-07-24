#include <QtGui>
#include <QIcon>
#include <QSettings>
#include "ActionZone.h"
#include "PluginManager.h"
#include "www/WebPage.h"
#include "flag.xpm"
#include "config.h"

/**
 * @mainpage
 * 
 * OtterDict is a Qt-based application that serves as an interface to
 * dictionaries available on-line.
 *
 * @section extending Extending OtterDict
 * 
 * There are two ways to extend OtterDict. 
 * You may extend the base program 
 * (such as adding some eye-candy or reorganizing the layout of the 
 * input fields and the result area) 
 * or add new dictionaries.
 * This section covers the latter.
 * 
 * To add a dictionary do OtterDict, you need to write your plugin
 * that is then loaded into OtterDict (thus you do not have to recompile
 * OtterDict in order to add a dictionary).
 * As OtterDict is Qt based and Qt alone offers framework for creating
 * dynamically loaded plugins, the tedious part of the job is already
 * created for you. 
 * Also, OtterDict itself offers several useful classes that may 
 * simplify your job.
 * 
 * Okay, enough of salesman pep-talk. 
 * Let's do some real job.
 * 
 *
 * @subsection extending_pluginorganization Instead of introduction
 * 
 * Before reading on, please, make sure that you know the basics of
 * how plugins are implemented using Qt.
 * The absolute minimum is the knowledge that each plugin must be
 * represented by a C++ class with no attributes (i.e. interface).
 * If you are new to this part of Qt, I would recommend reading
 * <a href="...">FIXME</a>.
 * 
 * Before going into details, a short note on naming must be mentioned.
 * Real-world equivalent to a plugin is not a dictionary (the book) but
 * a whole shelf of them.
 * That means that each plugin may provide more than one dictionary
 * if it makes sense to have more dictionaries together 
 * (usually because their backend is the same).
 * This also explains why the plugin class is named 
 * DictionaryShelfPluginInterface and why the dictionary itself 
 * (the Dictionary class)
 * does not form the plugin
 * The DictionaryShelfPluginInterface serves as a factory that only
 * creates instances of the dictionaries - descendants of Dictionary
 * class.
 *
 *
 * @subsection extending_creatingnewplugin Creating a plugin
 * 
 * This section will guide you through the process of creating your
 * very own plugin.
 * However, to simplify the matter, we will create a simple off-line
 * dictionary that merely copies the input word (i.e. echo service).
 * On the other hand, to show how to have more dictionaries, we will
 * also provide a more sophisticated dictionary that reverses the
 * order of letters and the echos the word.
 * To see job done, explore the <code>plugins/echoplugin/</code>
 * directory.
 * 
 * For start, create new directory under the <code>plugins</code>
 * directory.
 * In our example, it would be <code>echoplugin</code>.
 * You probably noticed, that this directory already exists - either
 * remove it (if you prefer to do everything on your own) or simply
 * use existing files only to skim through the manual.
 * 
 * @subsubsection prepare_cmake Prepare build for CMake
 * OtterDict uses <a href="http://">cmake - FIXME</a> for generating
 * Makefiles so the very first file we create is @c CMakeLists.txt.
 * There is already prepared macro that does @e all the job.
 * After all, see for yourself
 * @include echoplugin/CMakeLists.txt
 * There is one more thing that needs to be done - we need to enable
 * the plugin in the main CMake configuration file.
 * There is a for-cycle near the end of the main @c CMakeLists.txt
 * that iterates over existing plugins - add there plugin directory
 * and from CMake point of view, everything is done.
 * 
 * @subsubsection mainpluginclass The main plugin class
 *
 * By convention, the main plugin class is named as the plugin itself
 * with the word @c plugin appended.
 * The dictionary classes have the word @c dictionary appended.
 * 
 * The main plugin class has only two methods - one to get the name
 * of the plugin (DictionaryShelfPluginInterface::getName) and
 * factory method DictionaryShelfPluginInterface::getDictionaries
 * to create the dictionaires.
 * Dictionaries are created as a vector of pointers to the dictionary
 * instances and these instances are deleted by the application
 * (do not remember pointers to them and never try to delete them 
 * in the desctructor).
 * For completeness, here are @c EchoPlugin.h and @c EchoPlugin.cpp
 * (please, notice the plugin registration via call to Q_EXPORT_PLUGIN2):
 * @include echoplugin/EchoPlugin.h
 * @include echoplugin/EchoPlugin.cpp
 * 
 *
 * @subsubsection implementing Implementing the dictionary
 * Now comes the more interesting point - implementation of the actual
 * dictionary.
 * First, let's have a look at the header file:
 * @include echoplugin/EchoDictionary.h
 * 
 * First interesting member function is the virtual 
 * Dictionary::clone that has to clone the current instance.
 * That is because currently for each search a new dictionary is
 * instanceidzed (see below for explanation).
 * Also, ditionary is never directly deleted but always through
 * call to Dictionary::destroy which allows you to postpone the
 * actual desctruction (e.g. because of opened HTTP connection).
 * Our plugin does not reimplement this method as the default
 * implemention - calling <code>delete this</code> - is just
 * fine.
 * 
 * The Dictionary::getName tells the name of the dictionary and this
 * name is printed in the drop-down with dictionary list.
 * 
 * Somehow (never really understood why) we have to copy the signal
 * definition of the Dictionary::hitFound signal. 
 * This signal is emitted for each translation found.
 *
 * Finally, there is the actual heart of the dictionary - the
 * Dictionary::translate method. 
 * This method is called every time user presses the Translate 
 * button.
 * 
 * As our dictionary is an echo one, the actual source file with
 * class implemention is even shorter that the header one:
 * @include echoplugin/EchoDictionary.cpp
 *
 * And that is all. Following section will describe how to use the
 * WebPage class to simplify parsing results on a web page.
 *
 *
 *
 * @subsection using_webpage Using WebPage class to parse HTML
 *
 * Not all on-line dictionaries provide machine-oriented output
 * of the results and you need to parse bloated HTML full of 
 * images and advertisements.
 * To ease the burden, WebPage class was written.
 * It wraps several Qt classes and adds own functionality.
 * It is able to process HTTP request and to parse received HTML,
 * looking for element with certain class or id.
 * 
 * You construct the class giving it URL to download data from
 * and then you connect its WebPage::loadingFinished signal
 * to slot in which you do the actual parsing.
 * 
 * When the page is loaded, you iterate over its elements using
 * WebPage::iterator iterator.
 * There are several methods that allows you to search for certain
 * element with given attributes (see all the find<i>Something</i>
 * methods) and you retrive the actual text by call to 
 * WebPage::getElementInnerText.
 * 
 * Below is a copy of SlovnikCzPlugin dictionary 
 * (it resides in the @c slovnikczplugin directory):
 * @include slovnikczplugin/SlovnikCzDictionary.cpp
 *
 * @section faq FAQ (altough no one ever asked these questions)
 * 
 * @subsection faq_clone Why dictionary is cloned for each search?
 * Short answer: it is easier that way (and to hell with memory
 * issues [anyway, if you run Qt, you have enough memory, don't
 * you?]).
 * 
 * Long answer: first, to set the record straigh - I don't like it
 * either but when writing the interface I was too lazy to do it
 * the hard way. The problem is that if you do translation using remote
 * service user may request new search before the preivous one ended.
 * That could theoretically break the dictionary if it uses member
 * variables to store some status. Obviously, a clean-up method
 * would solve the problem. Maybe, I will reimplement this one
 * day (it would be on my ToDo list, if I have one).
 * 
 *
 * @subsection faq_shelves Why are dictionaries organized into shelves?
 * Short answer: because it was the only option how to implement it.
 * 
 * Long answer: first reason is that service I was interested in the
 * most was the one at http://slovnik.cz and creating separate plugin
 * for each dictionary therein available would mean a lot of code 
 * duplication. 
 * However, the main reason is that Qt plugins could not use 
 * signals/slots directly.
 * I do not know the implementation details inside Qt but interface in 
 * Qt library could not have signals defined (actually, they could but
 * plugin based on this interface could not be loaded at runtime) and
 * recommended bypass is to make the plugin a factory.
 *
 * 
 *
 */
int main(int argc, char * argv[]) {
	QApplication app(argc, argv);
	QSettings settings("otter", "dict");
	
	PluginManager plugMgr;
	
	// determine plugin directories
	settings.beginGroup("application");
	int size = settings.beginReadArray("plugindirectory");
	for (int i = 0; i < size; i++) {
		settings.setArrayIndex(i);
		QString dir = settings.value("directory", "").toString();
		if (dir.isEmpty()) {
			continue;
		}
		plugMgr.addPluginDirectory(dir);
	}
	settings.endArray();
	settings.endGroup();
	
	#ifdef PLUGINS_PATH
		plugMgr.addPluginDirectory(PLUGINS_PATH);
	#endif
	plugMgr.loadPlugins();
	
	ActionZone mainWindow(settings.value("mainwindow/dictionarycount", 2).toInt(), 0);
	mainWindow.setPluginManager(&plugMgr);
	
	mainWindow.setWindowTitle("OtterDict");
	mainWindow.setWindowIcon(QIcon(QPixmap(flagIcon))); 
	
	mainWindow.show();
	
	return app.exec();
}


