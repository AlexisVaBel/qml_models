#include "PieChart.h"

#include <QPainter>
#include <QPen>

using namespace ui::quick;

PieChart::PieChart(QQuickItem *parent) : QQuickPaintedItem(parent) {}

void PieChart::setName(const QString &name) { _name = name; }

void PieChart::setColor(const QColor &color) { _color = color; }

void PieChart::paint(QPainter *painter) {
  QPen pen(_color, 2);
  painter->setPen(pen);
  painter->setRenderHints(QPainter::Antialiasing, true);
  painter->drawPie(boundingRect().adjusted(1, 1, -1, -1), 90 * 16, 290 * 16);
}
