#ifndef OTTERDICT_PLUGINMANAGER_H_GUARD
#define OTTERDICT_PLUGINMANAGER_H_GUARD

#include <QString>
#include <QVector>
#include <QStringList>
#include "DictionaryShelfPluginInterface.h"
#include "Dictionary.h"

/**
 * Manager of dictionary plugins.
 * 
 */
class PluginManager {
public:
	/// Constructor.
	PluginManager();
	/// Destructor.
	~PluginManager();
	
	/// Adds directory where to look for plugins.
	void addPluginDirectory(const QString & dirname);
	
	/// Loads all available plugins.
	void loadPlugins();
	
	/// Tells names of all available dictionaries.
	QStringList getDictionaries() const;
	
	/// Gets copy of specified dictionary.
	Dictionary * getDictionary(int id);
protected:
	/// List of dictionaries.
	typedef QVector<Dictionary *> DictionaryList;
	/// Loads plugin from given file.
	void loadPlugin(const QString & filename);
	/// Adds a dictionary to the list.
	void addDictionary(Dictionary * dictionary);
private:
	/// Directories where to look for plugins.
	QStringList pluginDirectories_;
	/// List of all loaded dictionaries.
	DictionaryList dictionaries_;
};

#endif
