#include "SlovnikCzPlugin.h"
#include "SlovnikCzDictionary.h"
#include "Dictionary.h"

SlovnikCzPlugin::SlovnikCzPlugin() {
}

QString SlovnikCzPlugin::getName() {
	return "Slovnik.cz";
}


QVector<Dictionary *> SlovnikCzPlugin::getDictionaries() {
	QVector<Dictionary *> result;
	result.append(new SlovnikCzDictionary());
	return result;
}


Q_EXPORT_PLUGIN2(slovnikczplugin, SlovnikCzPlugin);
