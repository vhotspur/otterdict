#include <QWidget>
#include <QListWidget>
#include <QVBoxLayout>
#include "PluginManager.h"

class TranslationResultsViewer : public QWidget {
	Q_OBJECT
public:
	TranslationResultsViewer(QWidget * parent = 0) :
		QWidget(parent)
	{
		layout = new QVBoxLayout();
		resultListView = new QListWidget(this);
		resultListView->setResizeMode(QListView::Adjust);
		
		layout->addWidget(resultListView, 1);
	}
	void setPluginManager(PluginManager * mgr) {
		plugins = mgr;
	}
public slots:
	void translate(const QString & term) {
		Dictionary * dictionary = plugins->getDictionary(0);
		if (dictionary == 0) {
			return;
		}
		qDebug("Translating `%s' using `%s' dictionary.", 
			qPrintable(term), qPrintable(dictionary->getName()));
		connect(dictionary, SIGNAL(hitFound(const QString &, const QString &)),
			this, SLOT(translationFound(const QString &, const QString &)));
		dictionary->setTerm(term);
		delete dictionary;
	}
	void translationFound(const QString & original, const QString & translated) {
		resultListView->addItem(original + " -> " + translated);
	}
private:
	QVBoxLayout * layout;
	QListWidget * resultListView;
	PluginManager * plugins;
};
