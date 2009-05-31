#include "SlovnikCzDictionary.h"
#include <QByteArray>
#include <QUrl>

SlovnikCzDictionary::SlovnikCzDictionary(const QString & dictSpecification, 
		const QString & name) :
	Dictionary(),
	httpConnection_(0),
	dictionarySpecification_(dictSpecification),
	name_(name),
	destroyWhenFinished_(false)
{
}

SlovnikCzDictionary::~SlovnikCzDictionary() {
	delete httpConnection_;
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
	httpConnection_ = new QHttp("www.slovnik.cz");
	httpConnection_->get(getRequestPath(what));
	connect(httpConnection_, SIGNAL(requestFinished(int, bool)),
		this, SLOT(onRequestFinished(int, bool)));
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

void SlovnikCzDictionary::onRequestFinished(int id, bool error) {
	QByteArray requestData(httpConnection_->readAll());
	
	HtmlParser parser;
	parser.parseTree(std::string(requestData.data()));
	
	HtmlParser::HtmlTree dom = parser.getTree();
	
	HtmlParser::HtmlTree::iterator e = dom.end();
	QString leftTerm;
	QString rightTerm;
	for (HtmlParser::HtmlTree::iterator i = dom.begin(); i != e; ++i) {
		if (i->isTag("span")) {
			i->parseAttributes(true);
			if (i->getAttribute("class") == "l") {
				leftTerm = getTextOnly(dom.begin(i), dom.end(i));
				i = dom.end(i);
			} else if (i->getAttribute("class") == "r") {
				rightTerm = getTextOnly(dom.begin(i), dom.end(i));
				i = dom.end(i);
			}
			if (!leftTerm.isEmpty() && !rightTerm.isEmpty()) {
				emit hitFound(leftTerm, rightTerm);
				leftTerm.clear();
				rightTerm.clear();
			}
		}
	}
	
	if (destroyWhenFinished_) {
		delete this;
	}
}
	
QString SlovnikCzDictionary::getTextOnly(
		HtmlParser::HtmlTree::iterator start, 
		HtmlParser::HtmlTree::iterator end) {
	QString result;
	while (start != end) {
		if (start->isText()) {
			result.append(start->getOpeningText().c_str());
		}
		++start;
	}
	return QString::fromUtf8(result.toStdString().c_str());
}


