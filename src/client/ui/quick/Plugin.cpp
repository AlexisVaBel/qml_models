#include "Plugin.h"

#include <Navigable.h>
#include <QQmlEngine>

namespace{
		static const struct {
	const char *type;
	int major, minor;
	} qmldir [] = {
		
		};
}//namespace


void Plugin::registerTypes(const char *uri)
{
	qmlRegisterType<ui::quick::Navigable>(uri, 2, 0, "Navigable");
	const QString filesLocation = fileLocation();
	for (auto i : qmldir) {
		qmlRegisterType(QUrl(filesLocation + "/" + i.type + ".qml"), uri, i.major, i.minor, i.type);
	}
}

void Plugin::initializeEngine(QQmlEngine *engine, const char *uri)
{
	Q_UNUSED(uri);
	
	if (isLoadedFromResources())
		engine->addImportPath(QStringLiteral("qrc:/"));
	
//	engine->rootContext()->setContextProperty( "defaultNodeStyle", QVariant::fromValue(qan::Node::style()) );
//	engine->rootContext()->setContextProperty( "defaultEdgeStyle", QVariant::fromValue(qan::Edge::style()) );
//	engine->rootContext()->setContextProperty( "defaultGroupStyle", QVariant::fromValue(qan::Group::style()) );	
}

QString Plugin::fileLocation() const
{
	if (isLoadedFromResources())
		return QStringLiteral("qrc:/QuickNodes");
	return baseUrl().toString();	
}

bool Plugin::isLoadedFromResources() const
{
	QFile file(baseUrl().toLocalFile() + qmldir[0].type + ".qml");
	return !file.exists();
}
