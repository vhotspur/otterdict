#include "ActionZone.h"

ActionZone::ActionZone(QWidget * parent) :
	QWidget(parent)
{
	initGui();
}

void ActionZone::setPluginManager(PluginManager * mgr) {
	plugins = mgr;
	viewer1->setPluginManager(mgr);
	viewer1->reloadDictionaries();
	viewer2->setPluginManager(mgr);
	viewer2->reloadDictionaries();
}

void ActionZone::sendTranslation() {
	qDebug("Emmiting...");
	emit newTranslation(searchedTerm->text());
}

void ActionZone::initGui() {
	inputControlsLayout = new QHBoxLayout();
	resultsLayout = new QHBoxLayout();
	topLayout = new QVBoxLayout(this);
	topLayout->addLayout(inputControlsLayout, 0);
	topLayout->addLayout(resultsLayout, 2);
	
	searchedTerm = new QLineEdit(this);
	connect(searchedTerm, SIGNAL(editingFinished()), this, SLOT(sendTranslation()));
	inputControlsLayout->addWidget(searchedTerm);
	
	searchButton = new QPushButton("Translate!", this);
	connect(searchButton, SIGNAL(clicked()), this, SLOT(sendTranslation()));
	inputControlsLayout->addWidget(searchButton);
	
	viewer1 = new TranslationResultsViewer(this);
	connect(this, SIGNAL(newTranslation(const QString &)), viewer1, SLOT(translate(const QString &)));
	resultsLayout->addWidget(viewer1, 1);
	
	viewer2 = new TranslationResultsViewer(this);
	connect(this, SIGNAL(newTranslation(const QString &)), viewer2, SLOT(translate(const QString &)));
	resultsLayout->addWidget(viewer2, 1);
}
