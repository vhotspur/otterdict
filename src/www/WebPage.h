#ifndef OTTTERDICT_WEBPAGE_H_GUARD
#define OTTTERDICT_WEBPAGE_H_GUARD

#include <QObject>
#include <QHttp>
#include <QUrl>
#include <QIODevice>
#include "HtmlParser.h"

class WebPage : public QObject {
	Q_OBJECT
public:
	WebPage(QUrl url, QIODevice * postData = 0);
	~WebPage();
signals:
	void loadingInProgress();
	void loadingFinished();
public:
	typedef HtmlParser::HtmlTree::iterator iterator;
	iterator end() const;
	iterator begin() const;
	iterator findElementWithClass(const QString & name, 
		const QString & classname, 
		const iterator startingPoint) const;
	iterator findElementWithClass(const QString & name, 
		const QString & classname) const;
	iterator findElementWithId(const QString & elementId);
	QString getElementInnerText(iterator elementIterator) const;
	iterator getFirstSibling(iterator elementIterator) const;
private:
	QHttp * connection_;
	HtmlParser::HtmlTree dom_;
private slots:
	void onRequestFinished(int id, bool error);
};

#endif
