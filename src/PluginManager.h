#ifndef OTTERDICT_PLUGINMANAGER_H_GUARD
#define OTTERDICT_PLUGINMANAGER_H_GUARD

#include <QString>
#include <QVector>
#include "DictionaryShelfPluginInterface.h"
#include "Dictionary.h"

class PluginManager {
public:
	PluginManager(const QString & pluginDir);
	
	void loadPlugins();
	
	int getPluginCount();
	
	Dictionary * getDictionary(int id);
protected:
	void loadPlugin(const QString & filename);
	void addDictionary(Dictionary * dictionary);
private:
	QString pluginDir_;
	QVector<Dictionary *> dictionaries_;
};

#endif
