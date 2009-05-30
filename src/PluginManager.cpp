#include "PluginManager.h"
#include "Dictionary.h"
#include <QPluginLoader>
#include <QDir>

PluginManager::PluginManager(const QString & pluginDir) :
	pluginDir_(pluginDir),
	dictionaries_()
{
	qDebug("Creating PluginManager...");
}

void PluginManager::loadPlugins() {
	QDir pluginDirectory(pluginDir_);
	
	QString fileName = pluginDirectory.entryList(QStringList() << "libechoplugin*").first();
	loadPlugin(pluginDirectory.absoluteFilePath(fileName));
}

void PluginManager::loadPlugin(const QString & filename) {
	QPluginLoader pluginLoader(filename);
	QObject * plugin = pluginLoader.instance();
	if (plugin == 0) {
		// FIXME - inform about invalid plugin format
		return;
	}
	DictionaryShelfPluginInterface * shelf = 
		qobject_cast<DictionaryShelfPluginInterface *>(plugin);
	if (shelf == 0) {
		// FIXME - inform about invalid plugin interface
		return;
	}
	
	// everythings seems fine, let's add the dictionaries to the 
	// local list
	DictionaryList dicts = shelf->getDictionaries();
	DictionaryList::iterator e = dicts.end();
	for (DictionaryList::iterator i = dicts.begin(); i != e; ++i) {
		addDictionary(*i);
	}
}

void PluginManager::addDictionary(Dictionary * dictionary) {
	dictionaries_.append(dictionary);
}

QStringList PluginManager::getDictionaries() const {
	QStringList result;
	DictionaryList::const_iterator e = dictionaries_.end();
	for (DictionaryList::const_iterator i = dictionaries_.begin(); i != e; ++i) {
		result.append((*i)->getName());
	}
	return result;
}

Dictionary * PluginManager::getDictionary(int id) {
	if (id < 0 || id >= dictionaries_.size()) {
		return 0;
	}
	return dictionaries_[id]->clone();
}
