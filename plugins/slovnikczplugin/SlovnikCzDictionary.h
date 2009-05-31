#ifndef OTTERDICT_SLOVNIKCZDICTIONARY_H_GUARD
#define OTTERDICT_SLOVNIKCZDICTIONARY_H_GUARD

#include <QObject>
#include <QString>
#include "Dictionary.h"
#include "WebPage.h"

class SlovnikCzDictionary : public Dictionary {
	Q_OBJECT
public:
	SlovnikCzDictionary(const QString & dictSpecification, const QString & name);
	virtual ~SlovnikCzDictionary();
	virtual void destroy();
	virtual Dictionary * clone() const;
	virtual QString getName() const;
signals:
	void hitFound(const QString &, const QString &);
protected:
	virtual void translate(const QString & what);
	QString getRequestPath(QString term);
private:
	WebPage * dictionaryPage_;
	QString dictionarySpecification_;
	QString name_;
	bool destroyWhenFinished_;
private slots:
	void onRequestFinished();
};

#endif
