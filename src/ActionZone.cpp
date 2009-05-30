#include "ActionZone.h"

/**
 * @details The constructor only initializes the UI.
 * 
 * @param parent Parent widget.
 * 
 */
ActionZone::ActionZone(QWidget * parent) :
	QWidget(parent)
{
	initGui();
}

/**
 * @param mgr New plugin manager to use.
 * 
 */
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
	connect(searchedTerm_, SIGNAL(returnPressed()), this, SLOT(sendTranslation()));
	inputControlsLayout_->addWidget(searchedTerm_);
	
	searchTermFocusOnEscapeAction_ = new QAction(searchedTerm_);
	searchTermFocusOnEscapeAction_->setShortcut(Qt::Key_Escape);
	searchedTerm_->addAction(searchTermFocusOnEscapeAction_);
	connect(searchTermFocusOnEscapeAction_, SIGNAL(triggered()), searchedTerm_, SLOT(setFocus()));
	connect(searchTermFocusOnEscapeAction_, SIGNAL(triggered()), searchedTerm_, SLOT(selectAll()));
	
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
