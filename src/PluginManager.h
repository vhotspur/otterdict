#ifndef OTTERDICT_PLUGINMANAGER_H_GUARD
#define OTTERDICT_PLUGINMANAGER_H_GUARD
#include <QString>
#include "DictionaryShelfPluginInterface.h"
#include "Dictionary.h"

class PluginManager {
public:
	PluginManager(const QString & pluginDir);
	
	void loadPlugins();
	
	int getPluginCount();
	
	Dictionary * getDictionary(int id);
private:
	QString pluginDir_;
	DictionaryShelfPluginInterface * plugin_;
};

#endif
