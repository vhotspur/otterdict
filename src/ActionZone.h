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
	
	QHBoxLayout * inputControlsLayout_;
	QHBoxLayout * resultsLayout_;
	QVBoxLayout * topLayout_;
	QLineEdit * searchedTerm_;
	QPushButton * searchButton_;
	TranslationResultsViewer * viewer1_;
	TranslationResultsViewer * viewer2_;
	PluginManager * plugins_;
};

#endif
