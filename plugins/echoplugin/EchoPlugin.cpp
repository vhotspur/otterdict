#include "EchoPlugin.h"
#include "EchoDictionary.h"
#include "Dictionary.h"

EchoPlugin::EchoPlugin() {
	qDebug("EchoPlugin::EchoPlugin");
}

QString EchoPlugin::getName() {
	return "EchoPlugin";
}


QVector<Dictionary *> EchoPlugin::getDictionaries() {
	QVector<Dictionary *> result;
	qDebug("EchoPlugin::getDictionaries");
	result.append(new EchoDictionary());
	qDebug("leaving EchoPlugin::getDictionaries");
	return result;
}


Q_EXPORT_PLUGIN2(echoplugin, EchoPlugin);
