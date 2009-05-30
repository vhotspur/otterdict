#include "TranslationResultsViewer.h"

TranslationResultsViewer::TranslationResultsViewer(QWidget * parent) :
	QWidget(parent)
{	
	resultListView_ = new QListWidget(this);
	resultListView_->setResizeMode(QListView::Adjust);
	
	dictionaryChooser_ = new QComboBox(this);
	
	layout_ = new QVBoxLayout(this);
	layout_->addWidget(dictionaryChooser_, 0);
	layout_->addWidget(resultListView_, 1);
}

void TranslationResultsViewer::setPluginManager(PluginManager * mgr) {
	plugins_ = mgr;
}

void TranslationResultsViewer::reloadDictionaries() {
	dictionaryChooser_->clear();
	
	QStringList dicts = plugins_->getDictionaries();
	QStringList::iterator e = dicts.end();
	for (QStringList::iterator i = dicts.begin(); i != e; ++i) {
		dictionaryChooser_->addItem(*i);
	}
}

int TranslationResultsViewer::getCurrentDictionaryId() const {
	int idx = dictionaryChooser_->currentIndex();
	if (idx == -1) {
		return 0;
	}
	return idx;
}

void TranslationResultsViewer::translate(const QString & term) {
	Dictionary * dictionary = plugins_->getDictionary(getCurrentDictionaryId());
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
	resultListView_->addItem(original + " -> " + translated);
	qDebug("Found translation: `%s' -> `%s'.", qPrintable(original), qPrintable(translated));
}
