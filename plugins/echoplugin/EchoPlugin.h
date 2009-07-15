#ifndef OTTERDICT_ECHOPLUGIN_H_GUARD
#define OTTERDICT_ECHOPLUGIN_H_GUARD

#include <QObject>
#include <QVector>
#include <QString>
#include "DictionaryShelfPluginInterface.h"
#include "Dictionary.h"

/**
 * Testing plugin.
 * 
 */
class EchoPlugin : public QObject, DictionaryShelfPluginInterface {
	Q_OBJECT
	Q_INTERFACES(DictionaryShelfPluginInterface)
public:
	EchoPlugin();
	virtual ~EchoPlugin() {}
	virtual QString getName();
	virtual QVector<Dictionary *> getDictionaries();
};

#endif
