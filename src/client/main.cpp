#include <QApplication>
#include <QFont>
#include <QtPlugin>
#include <QTranslator>

#include "spdlog/sinks/stdout_sinks.h"
#include <docopt/docopt.h>
#include <functional>
#include <iostream>
#include <QQmlApplicationEngine>
#include <spdlog/spdlog.h>

static constexpr auto USAGE =
		R"(QML NODES.

    Usage:
          TODO - prepare usage
 Options:
          -h --help     Show this screen.
          --version     Show version.
)";

auto initLog() {
	auto console = spdlog::stdout_logger_mt("console");
	spdlog::set_default_logger(console);
	spdlog::set_pattern("[source %s] [function %!] [line %#] %v");
	return console;
}

bool installTranslator(QLocale const& locale, QString const& fileName) {
	auto* translator = new QTranslator(qApp);
	if (!translator->load(locale, fileName, "_", ":/lang")) {
		return false;
	}

	return QCoreApplication::installTranslator(translator);
}

int main(int argc, char* argv[]) {
	QGuiApplication app(argc, argv);

	QLocale locale("ru_RU");
	installTranslator(locale, "qtbase");

	QFont font("Roboto Regular", 14);
	app.setFont(font);

	SPDLOG_INFO("initiated app");

	SPDLOG_INFO("initiated qml engine");

	QQmlApplicationEngine engine;

	engine.addImportPath("qrc:/ui/qml/");
	QUrl const qmlUrl("qrc:/ui/qml/main.qml");

	engine.load(QUrl(QStringLiteral("qrc:/ui/qml/main.qml")));

	QObject::connect(
			&engine, &QQmlApplicationEngine::objectCreated, &app, [qmlUrl](QObject* obj, const QUrl& objUrl) {
				if (!obj && qmlUrl == objUrl)
					QCoreApplication::exit(-1);
			},
			Qt::QueuedConnection);

	return app.exec();

} // namespace ui