#ifndef OTTERDICT_DICTIONARY_H_GUARD
#define OTTERDICT_DICTIONARY_H_GUARD
#include <QObject>
#include <QString>


class Dictionary : public QObject {
	
public:
	Dictionary() {}
	virtual ~Dictionary() {}
	virtual Dictionary * clone() const { return 0; }
	virtual QString getName() const { return ""; }
	void setTerm(const QString & str) {
		translate(str);
	}
signals: 
	void hitFound(const QString &, const QString &);
protected:
	virtual void translate(const QString &) {};
};

#endif
