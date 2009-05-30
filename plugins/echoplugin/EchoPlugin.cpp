#include "EchoPlugin.h"
#include "EchoDictionary.h"
#include "ReverseDictionary.h"
#include "Dictionary.h"

EchoPlugin::EchoPlugin() {
}

QString EchoPlugin::getName() {
	return "EchoPlugin";
}


QVector<Dictionary *> EchoPlugin::getDictionaries() {
	QVector<Dictionary *> result;
	result.append(new ReverseDictionary());
	result.append(new EchoDictionary());
	return result;
}


Q_EXPORT_PLUGIN2(echoplugin, EchoPlugin);
