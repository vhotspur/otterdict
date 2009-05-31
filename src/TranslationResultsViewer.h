#ifndef OTTERDICT_TRANSLATIONRESULTSVIEWER_H_GUARD
#define OTTERDICT_TRANSLATIONRESULTSVIEWER_H_GUARD
#include <QWidget>
#include <QListWidget>
#include <QVBoxLayout>
#include <QComboBox>
#include "PluginManager.h"

/**
 * Widget representing results of search in one dictionary.
 * 
 */
class TranslationResultsViewer : public QWidget {
	Q_OBJECT
public:
	/// Constructor.
	TranslationResultsViewer(QWidget * parent = 0);
	/// Destructor.
	~TranslationResultsViewer();
	/// Sets a new plugin manager to use.
	void setPluginManager(PluginManager * mgr);
public slots:
	/// Translates given term.
	void translate(const QString & term);
	/// Displays translated term.
	void translationFound(const QString & original, const QString & translated);
	/// Reloads dictionaries from plugin manager.
	void reloadDictionaries();
protected:
	/// Tells id of currently selected dictionary.
	int getCurrentDictionaryId() const;
private:
	/// Top-level layout.
	QVBoxLayout * layout_;
	/// Widget with results.
	QListWidget * resultListView_;
	/// List of available dictionaries.
	QComboBox * dictionaryChooser_;
	/// Plugin manager.
	PluginManager * plugins_;
};

#endif
