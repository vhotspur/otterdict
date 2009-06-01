#include "ThesaurusComDictionary.h"
#include <QByteArray>
#include <QUrl>

ThesaurusComDictionary::ThesaurusComDictionary() :
	Dictionary(),
	dictionaryPage_(0),
	destroyWhenFinished_(false)
{
}

ThesaurusComDictionary::~ThesaurusComDictionary() {
	delete dictionaryPage_;
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
	dictionaryPage_ = new WebPage(QUrl(
		"http://thesaurus.reference.com/browse/" + QUrl::toPercentEncoding(what)));
	connect(dictionaryPage_, SIGNAL(loadingFinished()),
		this, SLOT(onRequestFinished()));
}

void ThesaurusComDictionary::onRequestFinished() {
	WebPage::iterator endIter = dictionaryPage_->end();
	
	// trick - dummy cycle to allow breaks from within
	do { 	
		WebPage::iterator nothingFoundHeading = dictionaryPage_->findElementWithId("Heading");
		if (nothingFoundHeading != endIter) {
			QString headingText = dictionaryPage_->getElementInnerText(nothingFoundHeading);
			if (headingText.startsWith("No results found")) {
				emit hitFound("<no synonym found>", "");
				break;
			}
		}
		
		QString term;
		WebPage::iterator query = dictionaryPage_->findElementWithId("query");
		if (query != endIter) {
			term = dictionaryPage_->getElementInnerText(query);
		}
		
		WebPage::iterator resultDelimiter = dictionaryPage_
			->findElementWithClass("div", "result_copyright");
			
		WebPage::iterator i = dictionaryPage_->findElementWithClass("table", "the_content");
		while (1) { // break from within
			i = dictionaryPage_->findElementWithClass("a",
				"theColor", i, resultDelimiter);
				
			if (i == endIter) {
				break;
			}
			
			QString synonym = dictionaryPage_->getElementInnerText(i);
			emit hitFound(term, synonym);
			
			i = dictionaryPage_->getFirstSibling(i);
		}
		
	// trick - dummy cycle to allow breaks from within
	} while (0);
	
	if (destroyWhenFinished_) {
		delete this;
	}
}
	


