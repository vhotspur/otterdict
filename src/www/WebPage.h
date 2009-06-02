#ifndef OTTTERDICT_WEBPAGE_H_GUARD
#define OTTTERDICT_WEBPAGE_H_GUARD

#include <QObject>
#include <QHttp>
#include <QUrl>
#include <QIODevice>
#include "HtmlParser.h"

/**
 * Wrapper for downloading and parsing a web page.
 * 
 */
class WebPage : public QObject {
	Q_OBJECT
public:
	/// Constructor.
	WebPage(QUrl url, QIODevice * postData = 0);
	/// Destructor.
	~WebPage();
signals:
	/// Emitted to inform about page loading.
	void loadingInProgress();
	/// Emitted to inform about finished page loading.
	void loadingFinished();
public:
	/// Iterator over HTML page elements.
	typedef HtmlParser::HtmlTree::iterator iterator;
	/// Tells end iterator to page elements.
	iterator end() const;
	/// Tells iterator to the first page element.
	iterator begin() const;
	/// Finds element with given class.
	iterator findElementWithClass(const QString & name, 
		const QString & classname, 
		const iterator startingPoint);
	/// Finds element with given class.
	iterator findElementWithClass(const QString & name, 
		const QString & classname,
		const iterator startingPoint,
		const iterator endPoint);
	/// Finds element with given class.
	iterator findElementWithClass(const QString & name, 
		const QString & classname);
	/// Finds element with given id.
	iterator findElementWithId(const QString & elementId);
	/// Tells all inner text of given element and its subelements.
	QString getElementInnerText(iterator elementIterator) const;
	/// Tells next sibling of given element.
	iterator getFirstSibling(iterator elementIterator) const;
private:
	/// HTTP connection wrapper.
	QHttp * connection_;
	/// HTML page DOM.
	HtmlParser::HtmlTree dom_;
private slots:
	/// Callback when page is loaded.
	void onRequestFinished(int id, bool error);
};

#endif
