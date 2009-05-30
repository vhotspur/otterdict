#ifndef OTTERDICT_ACTIONZONE_H_GUARD
#define OTTERDICT_ACTIONZONE_H_GUARD
#include <QWidget>
#include <QVBoxLayout>
#include <QHBoxLayout>
#include <QLineEdit>
#include <QPushButton>
#include "TranslationResultsViewer.h"
#include "PluginManager.h"

class ActionZone : public QWidget {
	Q_OBJECT
public:
	ActionZone(QWidget * parent = 0);
	void setPluginManager(PluginManager * mgr);
public slots:
	void sendTranslation();
signals:
	void newTranslation(const QString &);
private:
	void initGui();
	
	QHBoxLayout * inputControlsLayout;
	QHBoxLayout * resultsLayout;
	QVBoxLayout * topLayout;
	QLineEdit * searchedTerm;
	QPushButton * searchButton;
	TranslationResultsViewer * viewer1;
	TranslationResultsViewer * viewer2;
	PluginManager * plugins;
};

#endif
