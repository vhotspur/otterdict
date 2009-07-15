#ifndef OTTERDICT_SLOVNIKCZDICTIONARY_H_GUARD
#define OTTERDICT_SLOVNIKCZDICTIONARY_H_GUARD

#include <QObject>
#include <QString>
#include "Dictionary.h"
#include "WebPage.h"

/**
 * %Dictionary of SlovnikCzPlugin.
 * 
 */
class SlovnikCzDictionary : public Dictionary {
	Q_OBJECT
public:
	/// Constructor.
	SlovnikCzDictionary(const QString & dictSpecification, const QString & name);
	virtual ~SlovnikCzDictionary();
	virtual void destroy();
	virtual Dictionary * clone() const;
	virtual QString getName() const;
signals:
	void hitFound(const QString &, const QString &);
protected:
	virtual void translate(const QString & what);
	/// Tells full path to page with term translation.
	QString getRequestPath(QString term);
private:
	/// Web page with translation.
	WebPage * dictionaryPage_;
	/// Tells which dictionary (which language) we use.
	QString dictionarySpecification_;
	/// Human-readable dictionary name.
	QString name_;
	/// Whether to destroy itself automatically. 
	/// When set to yes, dictionary destroyes automatically itself after 
	/// processing the request.
	bool destroyWhenFinished_;
private slots:
	/// Callback when HTTP request is completed.
	void onRequestFinished();
};

#endif
