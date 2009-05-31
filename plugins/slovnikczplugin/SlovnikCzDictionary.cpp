#include "SlovnikCzDictionary.h"

SlovnikCzDictionary::SlovnikCzDictionary() :
	Dictionary()
{
}

SlovnikCzDictionary::~SlovnikCzDictionary() {
}


Dictionary * SlovnikCzDictionary::clone() const {
	return new SlovnikCzDictionary();
}

QString SlovnikCzDictionary::getName() const {
	return "Slovnik.cz";
}

void SlovnikCzDictionary::translate(const QString & what) {
	emit hitFound(what, "<not implemented>");
}

