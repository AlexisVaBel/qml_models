#pragma once

#include <QQmlEngine>

#include <ui/quick/Navigable.h>

struct QuickNodes {
	static void initialize(QQmlEngine* /*engine*/) {
		qmlRegisterType<ui::quick::Navigable>("QuickNodes", 2, 0, "Navigable");
	}
};
