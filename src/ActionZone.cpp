#include "ActionZone.h"

ActionZone::ActionZone(QWidget * parent) :
	QWidget(parent)
{
	initGui();
}

void ActionZone::setPluginManager(PluginManager * mgr) {
	plugins_ = mgr;
	viewer1_->setPluginManager(mgr);
	viewer1_->reloadDictionaries();
	viewer2_->setPluginManager(mgr);
	viewer2_->reloadDictionaries();
}

void ActionZone::sendTranslation() {
	qDebug("Emmiting...");
	emit newTranslation(searchedTerm_->text());
}

void ActionZone::initGui() {
	inputControlsLayout_ = new QHBoxLayout();
	resultsLayout_ = new QHBoxLayout();
	topLayout_ = new QVBoxLayout(this);
	topLayout_->addLayout(inputControlsLayout_, 0);
	topLayout_->addLayout(resultsLayout_, 2);
	
	searchedTerm_ = new QLineEdit(this);
	connect(searchedTerm_, SIGNAL(editingFinished()), this, SLOT(sendTranslation()));
	inputControlsLayout_->addWidget(searchedTerm_);
	
	searchButton_ = new QPushButton("Translate!", this);
	connect(searchButton_, SIGNAL(clicked()), this, SLOT(sendTranslation()));
	inputControlsLayout_->addWidget(searchButton_);
	
	viewer1_ = new TranslationResultsViewer(this);
	connect(this, SIGNAL(newTranslation(const QString &)), viewer1_, SLOT(translate(const QString &)));
	resultsLayout_->addWidget(viewer1_, 1);
	
	viewer2_ = new TranslationResultsViewer(this);
	connect(this, SIGNAL(newTranslation(const QString &)), viewer2_, SLOT(translate(const QString &)));
	resultsLayout_->addWidget(viewer2_, 1);
}
