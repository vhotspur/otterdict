#ifndef OTTERDICT_THESAURUSCOMDICTIONARY_H_GUARD
#define OTTERDICT_THESAURUSCOMDICTIONARY_H_GUARD

#include <QObject>
#include <QString>
#include <QHttp>
#include "Dictionary.h"
#include "HtmlParser.h"

class ThesaurusComDictionary : public Dictionary {
	Q_OBJECT
public:
	ThesaurusComDictionary();
	virtual ~ThesaurusComDictionary();
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
private slots:
	void onRequestFinished(int id, bool error);
};

#endif
