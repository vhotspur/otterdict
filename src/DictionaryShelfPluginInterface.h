#include <QtPlugin>
#include <QString>
#include <QVector>
#include "Dictionary.h"

/**
 * Interface for dictionary plugin.
 * 
 */
class DictionaryShelfPluginInterface {
public:
	/**
	 * Virtual destructor.
	 * Provided for convenience only.
	 * 
	 */
	virtual ~DictionaryShelfPluginInterface() {}
	/**
	 * Tells name of the plugin.
	 * 
	 */
	virtual QString getName() = 0;
	/**
	 * Tells list of dictionaries.
	 * 
	 * @warning The returned list must be deleted by the caller.
	 * 
	 */
	virtual QVector<Dictionary *> getDictionaries() = 0;
};

Q_DECLARE_INTERFACE(DictionaryShelfPluginInterface,
	"otterdict.plugin.DictionaryShelfPluginInterface/1.0");

