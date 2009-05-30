#ifndef OTTERDICT_DICTIONARY_H_GUARD
#define OTTERDICT_DICTIONARY_H_GUARD
#include <QObject>
#include <QString>

/**
 * Abstract ancestor for all dictionaries in OtterDict.
 * 
 * Due to way MOC treates files you <em>have to</em> specify
 * the hitFound() signal also in derived classes.
 * 
 */
class Dictionary : public QObject {
	
public:
	/// Constructor.
	Dictionary() {}
	/// Virtual destructor.
	virtual ~Dictionary() {}
	/// Clones itself, returning new copy.
	virtual Dictionary * clone() const { return 0; }
	/// Tells name of the dictionary.
	virtual QString getName() const { return ""; }
	/// Called when new search is requested.
	void setTerm(const QString & str) {
		translate(str);
	}
signals: 
	/// Signal to be emmited when a translation hit is found.
	void hitFound(const QString &, const QString &);
protected:
	/// Callback for a new search - the heart of the dictionary.
	virtual void translate(const QString &) {};
};

#endif
