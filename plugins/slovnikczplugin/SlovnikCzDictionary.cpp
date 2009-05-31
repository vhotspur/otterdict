#include "SlovnikCzDictionary.h"
#include <QByteArray>
#include <QUrl>

class HtmlParser;

SlovnikCzDictionary::SlovnikCzDictionary(const QString & dictSpecification, 
		const QString & name) :
	Dictionary(),
	dictionaryPage_(0),
	dictionarySpecification_(dictSpecification),
	name_(name),
	destroyWhenFinished_(false)
{
}

SlovnikCzDictionary::~SlovnikCzDictionary() {
	delete dictionaryPage_;
}

void SlovnikCzDictionary::destroy() {
	destroyWhenFinished_ = true;
}

Dictionary * SlovnikCzDictionary::clone() const {
	return new SlovnikCzDictionary(dictionarySpecification_, name_);
}

QString SlovnikCzDictionary::getName() const {
	return name_;
}

void SlovnikCzDictionary::translate(const QString & what) {
	dictionaryPage_ = new WebPage("http://www.slovnik.cz" + getRequestPath(what));
	connect(dictionaryPage_, SIGNAL(loadingFinished()),
		this, SLOT(onRequestFinished()));
}

QString SlovnikCzDictionary::getRequestPath(QString term) {
	QUrl url;
	url.setPath("/bin/mld.fpl");
	url.addQueryItem("vcb", term.toUtf8());
	url.addQueryItem("dictdir", dictionarySpecification_);
	url.addQueryItem("lines", "40");
	url.addQueryItem("js", "0");
	return url.toString(QUrl::RemoveAuthority);
}

void SlovnikCzDictionary::onRequestFinished() {
	WebPage::iterator e = dictionaryPage_->end();
	QString leftTerm;
	QString rightTerm;
	emit hitFound("request", "finished");
	
	WebPage::iterator i = dictionaryPage_->begin();
	while (i != e) {
		if (i->isTag("span")) {
			i->parseAttributes(true);
			if (i->getAttribute("class") == "l") {
				leftTerm = dictionaryPage_->getElementInnerText(i);
				i = dictionaryPage_->getFirstSibling(i);
			} else if (i->getAttribute("class") == "r") {
				rightTerm = dictionaryPage_->getElementInnerText(i);
				i = dictionaryPage_->getFirstSibling(i);
			} else {
				++i;
			}
			if (!leftTerm.isEmpty() && !rightTerm.isEmpty()) {
				emit hitFound(leftTerm, rightTerm);
				leftTerm.clear();
				rightTerm.clear();
			}
		} else {
			++i;
		}
	}
	
	if (destroyWhenFinished_) {
		delete this;
	}
}


