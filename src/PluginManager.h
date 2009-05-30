#ifndef OTTERDICT_PLUGINMANAGER_H_GUARD
#define OTTERDICT_PLUGINMANAGER_H_GUARD

#include <QString>
#include <QVector>
#include <QStringList>
#include "DictionaryShelfPluginInterface.h"
#include "Dictionary.h"

class PluginManager {
public:
	PluginManager(const QString & pluginDir);
	
	void loadPlugins();
	
	int getPluginCount();
	QStringList getDictionaries() const;
	
	Dictionary * getDictionary(int id);
protected:
	typedef QVector<Dictionary *> DictionaryList;
	void loadPlugin(const QString & filename);
	void addDictionary(Dictionary * dictionary);
private:
	QString pluginDir_;
	DictionaryList dictionaries_;
};

#endif
