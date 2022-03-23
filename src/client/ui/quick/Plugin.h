#pragma once

#include <QQmlExtensionPlugin>

class Plugin: public QQmlExtensionPlugin
{
	Q_OBJECT
	Q_PLUGIN_METADATA(IID QQmlExtensionInterface_iid)
public:
	void registerTypes(char const* uri);
	void initializeEngine(QQmlEngine *engine, char const *uri);
private:
	QString fileLocation() const;
	bool isLoadedFromResources() const;	
};


