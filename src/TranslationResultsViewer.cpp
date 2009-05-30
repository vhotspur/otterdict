#include "TranslationResultsViewer.h"

TranslationResultsViewer::TranslationResultsViewer(QWidget * parent) :
	QWidget(parent)
{	
	resultListView = new QListWidget(this);
	resultListView->setResizeMode(QListView::Adjust);
	
	dictionaryChooser = new QComboBox(this);
	
	layout = new QVBoxLayout(this);
	layout->addWidget(dictionaryChooser, 0);
	layout->addWidget(resultListView, 1);
}

void TranslationResultsViewer::setPluginManager(PluginManager * mgr) {
	plugins = mgr;
}

void TranslationResultsViewer::reloadDictionaries() {
	dictionaryChooser->clear();
	
	QStringList dicts = plugins->getDictionaries();
	QStringList::iterator e = dicts.end();
	for (QStringList::iterator i = dicts.begin(); i != e; ++i) {
		dictionaryChooser->addItem(*i);
	}
}

int TranslationResultsViewer::getCurrentDictionaryId() const {
	int idx = dictionaryChooser->currentIndex();
	if (idx == -1) {
		return 0;
	}
	return idx;
}

void TranslationResultsViewer::translate(const QString & term) {
	Dictionary * dictionary = plugins->getDictionary(getCurrentDictionaryId());
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
	qDebug("Found translation: `%s' -> `%s'.", qPrintable(original), qPrintable(translated));
}
