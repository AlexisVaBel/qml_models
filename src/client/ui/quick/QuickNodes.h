#pragma once

#include <QQmlEngine>

#include <ui/quick/Navigable.h>
#include <ui/quick/GraphView.h>
#include <ui/quick/Grid.h>
#include <ui/quick/PieChart.h>

namespace ui::quick{
struct QuickNodes {
	static void initialize(QQmlEngine* /*engine*/) {		
		qmlRegisterType<ui::quick::Grid>("QuickNodes", 2, 0, "Grid");
		qmlRegisterType<ui::quick::GraphView>("QuickNodes", 2, 0, "GraphView");
		qmlRegisterType<ui::quick::Navigable>("QuickNodes", 2, 0, "Navigable");
		qmlRegisterType<ui::quick::PieChart>("QuickNodes", 2, 0, "PieChart");
	}
};
}
