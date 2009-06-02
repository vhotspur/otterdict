#ifndef OTTERDICT_ACTIONZONE_H_GUARD
#define OTTERDICT_ACTIONZONE_H_GUARD
#include <QWidget>
#include <QVBoxLayout>
#include <QHBoxLayout>
#include <QLineEdit>
#include <QPushButton>
#include <QToolButton>
#include <QAction>
#include "TranslationResultsViewer.h"
#include "PluginManager.h"

/**
 * UI widget holding the input text field as well as the result area.
 * 
 */
class ActionZone : public QWidget {
	Q_OBJECT
public:
	/// Constructor.
	ActionZone(int displayedDictionaries, QWidget * parent = 0);
	/// Destructor.
	~ActionZone();
	/// Sets plugin manager to use.
	void setPluginManager(PluginManager * mgr);
public slots:
	/// Triggered when new search term is entered.
	void sendTranslation();
signals:
	/// Emitted when new term is entered.
	void newTranslation(const QString &);
protected:
	/// List of translation results viewers.
	typedef QVector<TranslationResultsViewer *> TranslationResultsViewerList;
	/// Displays info that there are no dictionaries available
	void displayNoDictionariesMessage();
private:
	/// Initializes the UI.
	void initGui(int displaydDictionaries);
	
	/// Layout for input entry and submit button.
	QHBoxLayout * inputControlsLayout_;
	/// Layout for result viewers.
	QHBoxLayout * resultsLayout_;
	/// Top-level layout
	QVBoxLayout * topLayout_;
	/// Input field with searched term.
	QLineEdit * searchedTerm_;
	/// Action widget for the input field.
	QAction * searchTermFocusOnEscapeAction_;
	/// Submit button.
	QPushButton * searchButton_;
	/// Preferences button.
	QToolButton * preferencesButton_;
	/// Results viewers.
	TranslationResultsViewerList resultViewers_;
	/// Plugin manager.
	PluginManager * plugins_;
	/// Whether there are some dictionaries
	bool noDictionaries;
private slots:
	/// Displays preferences dialog.
	void preferencesDialog();
};

#endif
