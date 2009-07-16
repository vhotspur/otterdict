#include <QtGui>
#include <QIcon>
#include <QSettings>
#include "ActionZone.h"
#include "PluginManager.h"
#include "www/WebPage.h"
#include "flag.xpm"

/**
 * @mainpage
 * 
 * OtterDict is a Qt-based application that serves as an interface to
 * dictionaries available on-line.
 *
 */
int main(int argc, char * argv[]) {
	QApplication app(argc, argv);
	QSettings settings("otter", "dict");
	
	PluginManager plugMgr;
	
	// determine plugin directories
	settings.beginGroup("application");
	int size = settings.beginReadArray("plugindirectory");
	for (int i = 0; i < size; i++) {
		settings.setArrayIndex(i);
		QString dir = settings.value("directory", "").toString();
		if (dir.isEmpty()) {
			continue;
		}
		plugMgr.addPluginDirectory(dir);
	}
	settings.endArray();
	settings.endGroup();
	
	plugMgr.addPluginDirectory(qApp->applicationDirPath());
	plugMgr.loadPlugins();
	
	ActionZone mainWindow(settings.value("mainwindow/dictionarycount", 2).toInt(), 0);
	mainWindow.setPluginManager(&plugMgr);
	
	mainWindow.setWindowTitle("OtterDict");
	mainWindow.setWindowIcon(QIcon(QPixmap(flagIcon))); 
	
	mainWindow.show();
	
	return app.exec();
}


