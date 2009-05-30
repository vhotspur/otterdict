#include "ReverseDictionary.h"

ReverseDictionary::ReverseDictionary() :
	Dictionary()
{
}

ReverseDictionary::~ReverseDictionary() {
}


Dictionary * ReverseDictionary::clone() const {
	return new ReverseDictionary();
}

QString ReverseDictionary::getName() const {
	return "ReverseDictionary";
}

void ReverseDictionary::translate(const QString & what) {
	QString result;
	QString::const_iterator e = what.end();
	for (QString::const_iterator i = what.begin(); i != e; ++i) {
		result.prepend(*i);
	}
	emit hitFound(what, result);
}

