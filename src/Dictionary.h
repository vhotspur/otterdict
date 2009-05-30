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
	/**
	 * Constructor.
	 * 
	 */
	Dictionary() {}
	/**
	 * Virtual destructor.
	 * 
	 */
	virtual ~Dictionary() {}
	/**
	 * Clones itself, returning new copy.
	 * 
	 * @return Identical copy of itself.
	 * 
	 */
	virtual Dictionary * clone() const = 0;
	/**
	 * Tells name of the dictionary.
	 * 
	 */
	virtual QString getName() const = 0;
	/**
	 * Called when new search is requested.
	 * 
	 * @param str String to be translated
	 * 
	 */
	void setTerm(const QString & str) {
		translate(str);
	}
signals: 
	/**
	 * Emmited when a translation hit is found.
	 * 
	 * @param original Original term (i.e. the one to be translated)
	 * @param translated Translation of the original term
	 * 
	 */
	void hitFound(const QString & original, const QString & translated);
protected:
	/**
	 * Callback for a new search - the heart of the dictionary.
	 * 
	 * @param what Term to translate
	 * 
	 */
	virtual void translate(const QString & what) = 0;
};

#endif
