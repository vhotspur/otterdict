#ifndef OTTERDICT_SLOVNIKCZDICTIONARY_H_GUARD
#define OTTERDICT_SLOVNIKCZDICTIONARY_H_GUARD

#include <QObject>
#include <QString>
#include "Dictionary.h"

class SlovnikCzDictionary : public Dictionary {
	Q_OBJECT
public:
	SlovnikCzDictionary();
	virtual ~SlovnikCzDictionary();
	virtual Dictionary * clone() const;
	virtual QString getName() const;
signals:
	void hitFound(const QString &, const QString &);
protected:
	virtual void translate(const QString & what);
};

#endif
