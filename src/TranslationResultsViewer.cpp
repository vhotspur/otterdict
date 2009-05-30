#include "TranslationResultsViewer.h"

TranslationResultsViewer::TranslationResultsViewer(QWidget * parent) :
	QWidget(parent)
{
	layout = new QVBoxLayout();
	resultListView = new QListWidget(this);
	resultListView->setResizeMode(QListView::Adjust);
	layout->addWidget(resultListView, 1);
}

void TranslationResultsViewer::setPluginManager(PluginManager * mgr) {
	plugins = mgr;
}

void TranslationResultsViewer::translate(const QString & term) {
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

void TranslationResultsViewer::translationFound(const QString & original, const QString & translated) {
	resultListView->addItem(original + " -> " + translated);
}
