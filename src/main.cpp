#include <QtGui>
#include <QCommonStyle>
#include "ActionZone.h"
#include "PluginManager.h"
#include "www/WebPage.h"

int main(int argc, char * argv[]) {
	QApplication app(argc, argv);
	
	PluginManager plugMgr(qApp->applicationDirPath() + "/");
	plugMgr.loadPlugins();
	
	ActionZone mainWindow(0);
	mainWindow.setPluginManager(&plugMgr);
	
	QCommonStyle style;
	mainWindow.setWindowTitle("OtterDict");
	mainWindow.setWindowIcon(style.standardIcon(QStyle::SP_MessageBoxQuestion));
	
	mainWindow.show();
	
	return app.exec();
}


