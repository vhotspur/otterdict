#ifndef OTTERDICT_SLOVNIKCZPLUGIN_H_GUARD
#define OTTERDICT_SLOVNIKCZPLUGIN_H_GUARD

#include <QObject>
#include <QVector>
#include <QString>
#include "DictionaryShelfPluginInterface.h"
#include "Dictionary.h"

/**
 * Plugin for on-line dictionary at http://slovnik.cz/.
 * 
 */
class SlovnikCzPlugin : public QObject, DictionaryShelfPluginInterface {
	Q_OBJECT
	Q_INTERFACES(DictionaryShelfPluginInterface)
public:
	SlovnikCzPlugin();
	virtual ~SlovnikCzPlugin() {}
	virtual QString getName();
	virtual QVector<Dictionary *> getDictionaries();
};

#endif
