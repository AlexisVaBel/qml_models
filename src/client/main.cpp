#include <QApplication>

#include <client/ui/DumpWidget.h>

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

int main(int argc, char** argv) {
	SPDLOG_INFO("initiated app");

	QApplication app(argc, argv);

	SPDLOG_INFO("initiated qml engine");

	QQmlApplicationEngine engine;

	engine.load(QUrl(QStringLiteral("qrc:/ui/qml/main.qml")));

	return app.exec();

} // namespace ui