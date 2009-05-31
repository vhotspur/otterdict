#include "ThesaurusComPlugin.h"
#include "ThesaurusComDictionary.h"
#include "Dictionary.h"

ThesaurusComPlugin::ThesaurusComPlugin() {
}

QString ThesaurusComPlugin::getName() {
	return "Thesaurus.com";
}


QVector<Dictionary *> ThesaurusComPlugin::getDictionaries() {
	QVector<Dictionary *> result;
	result.append(new ThesaurusComDictionary());
	return result;
}


Q_EXPORT_PLUGIN2(thesauruscomplugin, ThesaurusComPlugin);
