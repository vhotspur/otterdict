#include <QtGui>
#include <QCommonStyle>
#include <QSettings>
#include "ActionZone.h"
#include "PluginManager.h"
#include "www/WebPage.h"

int main(int argc, char * argv[]) {
	QApplication app(argc, argv);
	QSettings settings("otter", "dict");
	
	QString pluginDirectory = 
		settings.value("application/plugindirectory", qApp->applicationDirPath()).toString();
	PluginManager plugMgr(pluginDirectory + "/");
	plugMgr.loadPlugins();
	
	ActionZone mainWindow(settings.value("mainwindow/dictionarycount", 2).toInt(), 0);
	mainWindow.setPluginManager(&plugMgr);
	
	QCommonStyle style;
	mainWindow.setWindowTitle("OtterDict");
	mainWindow.setWindowIcon(style.standardIcon(QStyle::SP_MessageBoxQuestion));
	
	mainWindow.show();
	
	return app.exec();
}


