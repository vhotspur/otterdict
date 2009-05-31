#include "ThesaurusComDictionary.h"
#include <QByteArray>
#include <QUrl>

ThesaurusComDictionary::ThesaurusComDictionary() :
	Dictionary(),
	httpConnection_(0),
	destroyWhenFinished_(false)
{
}

ThesaurusComDictionary::~ThesaurusComDictionary() {
	delete httpConnection_;
}

void ThesaurusComDictionary::destroy() {
	destroyWhenFinished_ = true;
}

Dictionary * ThesaurusComDictionary::clone() const {
	return new ThesaurusComDictionary();
}

QString ThesaurusComDictionary::getName() const {
	return "English thesaurus (Thesaurus.com)";
}

void ThesaurusComDictionary::translate(const QString & what) {
	httpConnection_ = new QHttp("thesaurus.reference.com");
	httpConnection_->get(getRequestPath(what));
	connect(httpConnection_, SIGNAL(requestFinished(int, bool)),
		this, SLOT(onRequestFinished(int, bool)));
}

QString ThesaurusComDictionary::getRequestPath(QString term) {
	return "/browse/" + QUrl::toPercentEncoding(term);
}

void ThesaurusComDictionary::onRequestFinished(int id, bool error) {
	QByteArray requestData(httpConnection_->readAll());
	
	HtmlParser parser;
	parser.parseTree(std::string(requestData.data()));
	
	HtmlParser::HtmlTree dom = parser.getTree();
	
	HtmlParser::HtmlTree::iterator e = dom.end();
	QString leftTerm;
	for (HtmlParser::HtmlTree::iterator i = dom.begin(); i != e; ++i) {
		if (i->isTag()) {
			i->parseAttributes(true);
		}
		
		if (i->isTag("a")) {	
			if (i->getAttribute("class") == "theColor") {
				emit hitFound(leftTerm, getTextOnly(dom.begin(i), dom.end(i)));
				i = dom.end(i);
			}
		} else if (i->isTag("span")) {
			if (i->getAttribute("id") == "query") {
				leftTerm = getTextOnly(dom.begin(i), dom.end(i));
				i = dom.end(i);
			}
		} else if (i->isTag("div")) {
			if (i->getAttribute("class") == "result_copyright") {
				// end the search
				break;
			}
			if (i->getAttribute("id") == "Heading") {
				if (getTextOnly(dom.begin(i), dom.end(i)).startsWith("No results found")) {
					emit hitFound(leftTerm, "<no synonym found>");
					break;
				}
			}
			
		}
	}
	
	if (destroyWhenFinished_) {
		delete this;
	}
}
	
QString ThesaurusComDictionary::getTextOnly(
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


