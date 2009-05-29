#include "PluginManager.h"
#include "Dictionary.h"
#include <QPluginLoader>
#include <QDir>

PluginManager::PluginManager(const QString & pluginDir) :
	pluginDir_(pluginDir),
	plugin_(0)
{
	Dictionary dict();
}

void PluginManager::loadPlugins() {
	QDir pluginDirectory(pluginDir_);
	QString fileName = pluginDirectory.entryList(QStringList() << "libechoplugin*").first();
	QPluginLoader pluginLoader(pluginDirectory.absoluteFilePath(fileName));
	QObject * plugin = pluginLoader.instance();
	if (plugin != 0) {
		plugin_ = qobject_cast<DictionaryShelfPluginInterface *>(plugin);
	}
}


Dictionary * PluginManager::getDictionary(int id) {
	if (plugin_ == 0) {
		return 0;
	}
	QVector<Dictionary *> dicts = plugin_->getDictionaries();
	if (dicts.size() == 0) {
		return 0;
	}
	return dicts[0]->clone();
}
