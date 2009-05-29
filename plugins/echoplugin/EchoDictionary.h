#ifndef OTTERDICT_ECHODICTIONARY_H_GUARD
#define OTTERDICT_ECHODICTIONARY_H_GUARD

#include <QObject>
#include <QString>
#include "Dictionary.h"

class EchoDictionary : public Dictionary {
	Q_OBJECT
public:
	EchoDictionary();
	virtual ~EchoDictionary();
	virtual Dictionary * clone() const;
	virtual QString getName() const;
signals:
	void hitFound(const QString &, const QString &);
protected:
	virtual void translate(const QString & what);
};

#endif
