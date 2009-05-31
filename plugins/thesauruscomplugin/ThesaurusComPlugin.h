#ifndef OTTERDICT_THESAURUSCOMPLUGIN_H_GUARD
#define OTTERDICT_THESAURUSCOMPLUGIN_H_GUARD

#include <QObject>
#include <QVector>
#include <QString>
#include "DictionaryShelfPluginInterface.h"
#include "Dictionary.h"

class ThesaurusComPlugin : public QObject, DictionaryShelfPluginInterface {
	Q_OBJECT
	Q_INTERFACES(DictionaryShelfPluginInterface)
public:
	ThesaurusComPlugin();
	virtual ~ThesaurusComPlugin() {}
	virtual QString getName();
	virtual QVector<Dictionary *> getDictionaries();
};

#endif
