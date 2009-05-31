#include "WebPage.h"

WebPage::WebPage(QUrl url, QIODevice * postData) :
		dom_()
{
	int portNo = url.port() == -1 ? 80 : url.port();
	connection_ = new QHttp(url.host(), portNo);
	
	connect(connection_, SIGNAL(requestFinished(int, bool)),
		this, SLOT(onRequestFinished(int, bool)));
	
	QString path = url.toString(QUrl::RemoveAuthority);
	if (postData != 0) {
		connection_->post(path, postData);
	} else {
		connection_->get(path);
	}
}

WebPage::~WebPage() {
	delete connection_;
}

void WebPage::onRequestFinished(int id, bool error) {
	QByteArray requestData(connection_->readAll());
	
	HtmlParser parser;
	parser.parseTree(std::string(requestData.data()));
	
	dom_ = parser.getTree();
	emit loadingFinished();
}

WebPage::iterator WebPage::end() const {
	return dom_.end();
}

WebPage::iterator WebPage::begin() const {
	return dom_.begin();
}

WebPage::iterator WebPage::findElementWithClass(const QString & name, 
		const QString & classname, 
		const WebPage::iterator startingPoint) const {
	iterator e = end();
	for (iterator i = startingPoint; i != e; ++i) {
		if (i->isTag(qPrintable(name))) {
			i->parseAttributes(true);
			QString classes(i->getAttribute("class").c_str());
			QStringList allClasses = classes.split(QRegExp("\\s+"));
			if (allClasses.contains(classname, Qt::CaseInsensitive)) {
				return i;
			}
		}
	}
	
	return e;
}

WebPage::iterator WebPage::findElementWithClass(const QString & name, 
		const QString & classname) const {
	return findElementWithClass(name, classname, begin());
}

WebPage::iterator WebPage::findElementWithId(const QString & elementId) {
	iterator e = end();
	for (iterator i = begin(); i != e; ++i) {
		if (i->isTag()) {
			i->parseAttributes(true);
			if (QString(i->getAttribute("id").c_str()) == elementId) {
				return i;
			}
		}
	}
	
	return e;
}

QString WebPage::getElementInnerText(WebPage::iterator elementIterator) const {
	QString result;
	iterator start = dom_.begin(elementIterator);
	iterator end = dom_.end(elementIterator);
	while (start != end) {
		if (start->isText()) {
			result.append(start->getOpeningText().c_str());
		}
		++start;
	}
	return result;
}

WebPage::iterator WebPage::getFirstSibling(WebPage::iterator elementIterator) const {
	return dom_.next_sibling(elementIterator);
}



