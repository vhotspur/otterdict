#include <QtGui>
#include <QIcon>
#include <QSettings>
#include "ActionZone.h"
#include "PluginManager.h"
#include "www/WebPage.h"
#include "flag.xpm"

int main(int argc, char * argv[]) {
	QApplication app(argc, argv);
	QSettings settings("otter", "dict");
	
	QString pluginDirectory = 
		settings.value("application/plugindirectory", qApp->applicationDirPath()).toString();
	PluginManager plugMgr(pluginDirectory + "/");
	plugMgr.loadPlugins();
	
	ActionZone mainWindow(settings.value("mainwindow/dictionarycount", 2).toInt(), 0);
	mainWindow.setPluginManager(&plugMgr);
	
	mainWindow.setWindowTitle("OtterDict");
	mainWindow.setWindowIcon(QIcon(QPixmap(flagIcon))); 
	
	mainWindow.show();
	
	return app.exec();
}


