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
 * \section building Building
 * To build OtterDict, you need to have (in braces are programs/versions 
 * I have used when developing)
 * - C++ compiler [g++ (GCC) 4.4.0]
 * - CMake [2.6]
 * - make [GNU Make 3.81]
 * - Qt libraries [4.5.2]
 * 
 * I developed OtterDict on GNU/Linux, however it may be possible to port
 * it to other systems supported by 
 * <a href="http://www.qtsoftware.com/">Qt</a>.
 * 
 * The actual building process is pretty straightforward (in following
 * commands, we assume that you have version 0.1).
 * 
 * First, unpack the tarball
 * @code
 * tar -xzf otterdict-0.1.tar.gz
 * cd otterdict-0.1
 * @endcode
 * Now, you have two options. You can either start build directly by
 * executing
 * @code
 * cmake .
 * @endcode
 * or if you prefer building outside the source directory, create build
 * directory and run <code>cmake</code> there
 * @code
 * mkdir build
 * cd build
 * cmake ..
 * @endcode
 * Now you can actually build the application by executing
 * @code
 * make
 * @endcode
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


