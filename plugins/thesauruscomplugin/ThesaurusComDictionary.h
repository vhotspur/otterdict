#ifndef OTTERDICT_THESAURUSCOMDICTIONARY_H_GUARD
#define OTTERDICT_THESAURUSCOMDICTIONARY_H_GUARD

#include <QObject>
#include <QString>
#include <QHttp>
#include "Dictionary.h"
#include "WebPage.h"

/**
 * English thesaurus dictionary of ThesaurusComPlugin.
 * 
 */
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
	/// Web page with translation.
	WebPage * dictionaryPage_;
	/// Whether to destroy itself automatically. 
	/// When set to yes, dictionary destroyes automatically itself after 
	/// processing the request.
	bool destroyWhenFinished_;
private slots:
	/// Callback when HTTP request is completed.
	void onRequestFinished();
};

#endif
