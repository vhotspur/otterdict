#ifndef OTTERDICT_TRANSLATIONRESULTSVIEWER_H_GUARD
#define OTTERDICT_TRANSLATIONRESULTSVIEWER_H_GUARD
#include <QWidget>
#include <QListWidget>
#include <QVBoxLayout>
#include "PluginManager.h"

class TranslationResultsViewer : public QWidget {
	Q_OBJECT
public:
	TranslationResultsViewer(QWidget * parent = 0);
	void setPluginManager(PluginManager * mgr);
public slots:
	void translate(const QString & term);
	void translationFound(const QString & original, const QString & translated);
private:
	QVBoxLayout * layout;
	QListWidget * resultListView;
	PluginManager * plugins;
};

#endif
