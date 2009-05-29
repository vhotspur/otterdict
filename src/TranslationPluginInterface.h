#include <QObject>
#include <QtPlugin>
#include <QVector>
#include <QString>

class TranslationPluginInterface {
public:
	virtual ~TranslationPluginInterface() {}
	virtual TranslationPluginInterface * clone() const = 0;
	virtual QString getName() = 0;
	virtual QVector<QString> getDictionaries() = 0;
	virtual void translate(const QString & what) = 0;
//signals:
	virtual void foundTranslation(const QString & original, const QString & translated) = 0;
};



Q_DECLARE_INTERFACE(TranslationPluginInterface,
	"otterdict.plugin.TranslationPluginInterface/1.0");



