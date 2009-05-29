#include "EchoDictionary.h"

EchoDictionary::EchoDictionary() :
	Dictionary()
{
}

EchoDictionary::~EchoDictionary() {
}


Dictionary * EchoDictionary::clone() const {
	return new EchoDictionary();
}

QString EchoDictionary::getName() const {
	return "EchoDictionary";
}

void EchoDictionary::translate(const QString & what) {
	emit hitFound(what, what);
}

