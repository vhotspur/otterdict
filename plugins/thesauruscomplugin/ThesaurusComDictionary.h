#ifndef OTTERDICT_THESAURUSCOMDICTIONARY_H_GUARD
#define OTTERDICT_THESAURUSCOMDICTIONARY_H_GUARD

#include <QObject>
#include <QString>
#include <QHttp>
#include "Dictionary.h"
#include "WebPage.h"

class ThesaurusComDictionary : public Dictionary {
	Q_OBJECT
public:
	ThesaurusComDictionary();
	virtual ~ThesaurusComDictionary();
	virtual void destroy();
	virtual Dictionary * clone() const;
	virtual QString getName() const;
signals:
	void hitFound(const QString &, const QString &);
protected:
	virtual void translate(const QString & what);
private:
	WebPage * dictionaryPage_;
	bool destroyWhenFinished_;
private slots:
	void onRequestFinished();
};

#endif
