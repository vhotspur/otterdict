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
	ActionZone(QWidget * parent = 0) :
		QWidget(parent)
	{
		initGui();
	}
	void setPluginManager(PluginManager * mgr) {
		plugins = mgr;
		viewer1->setPluginManager(mgr);
		viewer2->setPluginManager(mgr);
	}
public slots:
	void sendTranslation() {
		qDebug("Emmiting...");
		emit newTranslation(searchedTerm->text());
	}
signals:
	void newTranslation(const QString &);
private:
	void initGui() {
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
	
	
	
	QHBoxLayout * inputControlsLayout;
	QHBoxLayout * resultsLayout;
	QVBoxLayout * topLayout;
	QLineEdit * searchedTerm;
	QPushButton * searchButton;
	TranslationResultsViewer * viewer1;
	TranslationResultsViewer * viewer2;
	PluginManager * plugins;
};

