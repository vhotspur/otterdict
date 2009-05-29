#include <QtGui>
#include "ActionZone.h"
#include "PluginManager.h"

int main(int argc, char * argv[]) {
	QApplication app(argc, argv);
	
	PluginManager plugMgr(qApp->applicationDirPath() + "/");
	plugMgr.loadPlugins();
	
	ActionZone mainWindow(0);
	mainWindow.setPluginManager(&plugMgr);
	
	mainWindow.show();
	
	return app.exec();
}


