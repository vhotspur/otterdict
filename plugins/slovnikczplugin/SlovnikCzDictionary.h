#ifndef OTTERDICT_SLOVNIKCZDICTIONARY_H_GUARD
#define OTTERDICT_SLOVNIKCZDICTIONARY_H_GUARD

#include <QObject>
#include <QString>
#include <QHttp>
#include "Dictionary.h"
#include "HtmlParser.h"

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
	QString getTextOnly(HtmlParser::HtmlTree::iterator start, HtmlParser::HtmlTree::iterator end);
	QString getRequestPath(QString term);
private:
	QHttp * httpConnection_;
	QString dictionarySpecification_;
	QString name_;
	bool destroyWhenFinished_;
private slots:
	void onRequestFinished(int id, bool error);
};

#endif
