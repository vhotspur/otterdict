#ifndef OTTERDICT_ACTIONZONE_H_GUARD
#define OTTERDICT_ACTIONZONE_H_GUARD
#include <QWidget>
#include <QVBoxLayout>
#include <QHBoxLayout>
#include <QLineEdit>
#include <QPushButton>
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
	ActionZone(QWidget * parent = 0);
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
private:
	/// Initializes the UI.
	void initGui();
	
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
	/// Results viewers.
	TranslationResultsViewerList resultViewers_;
	/// Plugin manager.
	PluginManager * plugins_;
};

#endif
