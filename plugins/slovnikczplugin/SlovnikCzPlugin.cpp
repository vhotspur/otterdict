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
	
	result.append(new SlovnikCzDictionary("encz.en", "English-Czech (slovnik.cz)"));
	result.append(new SlovnikCzDictionary("encz.cz", "Czech-English (slovnik.cz)"));
	
	result.append(new SlovnikCzDictionary("gecz.ge", "German-Czech (slovnik.cz)"));
	result.append(new SlovnikCzDictionary("gecz.cz", "Czech-German (slovnik.cz)"));
	
	result.append(new SlovnikCzDictionary("frcz.fr", "French-Czech (slovnik.cz)"));
	result.append(new SlovnikCzDictionary("frcz.cz", "Czech-French (slovnik.cz)"));
	
	result.append(new SlovnikCzDictionary("itcz.it", "Italian-Czech (slovnik.cz)"));
	result.append(new SlovnikCzDictionary("itcz.cz", "Czech-Italian (slovnik.cz)"));
	
	result.append(new SlovnikCzDictionary("lacz.la", "Latin-Czech (slovnik.cz)"));
	result.append(new SlovnikCzDictionary("lacz.cz", "Czech-Latin (slovnik.cz)"));
	
	result.append(new SlovnikCzDictionary("rucz.ru", "Russian-Czech (slovnik.cz)"));
	result.append(new SlovnikCzDictionary("rucz.cz", "Czech-Russian (slovnik.cz)"));
	
	result.append(new SlovnikCzDictionary("spcz.sp", "Spanish-Czech (slovnik.cz)"));
	result.append(new SlovnikCzDictionary("spcz.cz", "Czech-Spanish (slovnik.cz)"));
	
	return result;
}


Q_EXPORT_PLUGIN2(slovnikczplugin, SlovnikCzPlugin);
