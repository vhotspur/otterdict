#include "ActionZone.h"
#include <QDialog>
#include <QIcon>
#include <QLabel>
#include <QComboBox>
#include <QSettings>
#include <QMessageBox>
#include "preferences.xpm"

/**
 * @details The constructor only initializes the UI.
 * 
 * @param displayedDictionaries Number of dictionaries to display
 * @param parent Parent widget.
 * 
 */
ActionZone::ActionZone(int displayedDictionaries, QWidget * parent) :
	QWidget(parent),
	resultViewers_(),
	noDictionaries(false)
{
	if (displayedDictionaries <= 0) {
		displayedDictionaries = 1;
	} else if (displayedDictionaries >= 10) {
		displayedDictionaries = 2;
	}
	initGui(displayedDictionaries);
}

ActionZone::~ActionZone() {
	delete topLayout_;
}

/**
 * @param mgr New plugin manager to use.
 * 
 */
void ActionZone::setPluginManager(PluginManager * mgr) {
	plugins_ = mgr;
	
	if (plugins_->getDictionaries().size() == 0) {
		noDictionaries = true;
		displayNoDictionariesMessage();
		return;
	}
	
	TranslationResultsViewerList::iterator e = resultViewers_.end();
	for (TranslationResultsViewerList::iterator i = resultViewers_.begin(); i != e; ++i) {
		(*i)->setPluginManager(mgr);
		(*i)->reloadDictionaries();
	}
}

void ActionZone::displayNoDictionariesMessage() {
	QMessageBox msgBox;
	msgBox.setText("There are no dictionaries available. Set correct path to the plugins and restart OtterDict.");
	msgBox.exec();
}

void ActionZone::sendTranslation() {
	if (noDictionaries) {
		displayNoDictionariesMessage();
		return;
	}
	emit newTranslation(searchedTerm_->text());
}

/**
 * @param displayedDictionaries Number of dictionaries to display
 * 
 */
void ActionZone::initGui(int displayedDictionaries) {
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
	
	preferencesButton_ = new QToolButton(this);
	preferencesButton_->setIcon(QIcon(QPixmap(preferencesIcon)));
	connect(preferencesButton_, SIGNAL(clicked()), this, SLOT(preferencesDialog()));
	inputControlsLayout_->addWidget(preferencesButton_);
	
	for (int i=0; i<displayedDictionaries; i++) {
		TranslationResultsViewer * viewer = new TranslationResultsViewer(this);
		resultViewers_.append(viewer);
	}
	
	TranslationResultsViewerList::iterator e = resultViewers_.end();
	for (TranslationResultsViewerList::iterator i = resultViewers_.begin(); i != e; ++i) {
		connect(this, SIGNAL(newTranslation(const QString &)), 
			*i, SLOT(translate(const QString &)));
		resultsLayout_->addWidget(*i, 1);
	}
	
}

void ActionZone::preferencesDialog() {
	QDialog * dialog = new QDialog();
	
	QPushButton * okButton = new QPushButton("OK", dialog);
	connect(okButton, SIGNAL(clicked()), dialog, SLOT(accept()));
	QPushButton * cancelButton = new QPushButton("Cancel", dialog);
	connect(cancelButton, SIGNAL(clicked()), dialog, SLOT(reject()));
	QBoxLayout * buttonLayout = new QHBoxLayout();
	buttonLayout->addWidget(okButton);
	buttonLayout->addWidget(cancelButton);
	
	QLabel * dictionaryCountLabel = new QLabel("Number of dictionaries", dialog);
	QComboBox * dictionaryCountCombo = new QComboBox(dialog);
	dictionaryCountCombo->addItem("1");
	dictionaryCountCombo->addItem("2");
	dictionaryCountCombo->addItem("3");
	dictionaryCountCombo->addItem("4");
	dictionaryCountCombo->addItem("5");
	dictionaryCountCombo->setCurrentIndex(resultViewers_.size() - 1);
	
	QLabel * pluginDirectoryLabel = new QLabel("Directory with plugins", dialog);
	QLineEdit * pluginDirectory = new QLineEdit(dialog);
	
	QLabel * reloadInfoLabel = new QLabel(
		"You need to restart OtterDict in order to changes take effect", dialog);
	reloadInfoLabel->setWordWrap(true);
	reloadInfoLabel->setFrameShape(QFrame::StyledPanel);
	
	QGridLayout * preferencesLayout = new QGridLayout(dialog);
	preferencesLayout->setSizeConstraint(QLayout::SetFixedSize);
	preferencesLayout->addWidget(dictionaryCountLabel, 0, 0, Qt::AlignRight);
	preferencesLayout->addWidget(dictionaryCountCombo, 0, 1, Qt::AlignLeft);
	preferencesLayout->addWidget(pluginDirectoryLabel, 1, 0, Qt::AlignRight);
	preferencesLayout->addWidget(pluginDirectory, 1, 1, Qt::AlignLeft);
	preferencesLayout->addWidget(reloadInfoLabel, 2, 0, 1, 2, Qt::AlignHCenter);
	preferencesLayout->addLayout(buttonLayout, 3, 0, 1, 2, Qt::AlignHCenter);
	
	dialog->setSizeGripEnabled(false);
	dialog->setWindowTitle("OtterDict preferences");
	
	QDialog::DialogCode retCode = (QDialog::DialogCode)dialog->exec();
	if (retCode == QDialog::Rejected) {
		return;
	}
	
	int dictionaryCount = dictionaryCountCombo->currentIndex() + 1;
	
	QSettings settings("otter", "dict");
	settings.setValue("mainwindow/dictionarycount", dictionaryCount);
	settings.setValue("application/plugindirectory", pluginDirectory->text());
}
