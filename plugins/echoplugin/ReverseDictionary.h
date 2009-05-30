#ifndef OTTERDICT_REVERSEDICTIONARY_H_GUARD
#define OTTERDICT_REVERSEDICTIONARY_H_GUARD

#include <QObject>
#include <QString>
#include "Dictionary.h"

class ReverseDictionary : public Dictionary {
	Q_OBJECT
public:
	ReverseDictionary();
	virtual ~ReverseDictionary();
	virtual Dictionary * clone() const;
	virtual QString getName() const;
signals:
	void hitFound(const QString &, const QString &);
protected:
	virtual void translate(const QString & what);
};

#endif
