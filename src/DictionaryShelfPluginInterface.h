#include <QtPlugin>
#include <QString>
#include <QVector>
#include "Dictionary.h"

class DictionaryShelfPluginInterface {
public:
	virtual ~DictionaryShelfPluginInterface() {}
	virtual QString getName() = 0;
	virtual QVector<Dictionary *> getDictionaries() = 0;
};

Q_DECLARE_INTERFACE(DictionaryShelfPluginInterface,
	"otterdict.plugin.DictionaryShelfPluginInterface/1.0");

