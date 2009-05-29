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
	qDebug("EchoDictionary::translate(\"%s\")", qPrintable(what));
	emit hitFound(what, what);
}

