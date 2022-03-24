#pragma once

#include <QColor>
#include <QQuickPaintedItem>

namespace ui::quick {

class PieChart : public QQuickPaintedItem {
  Q_OBJECT
  Q_PROPERTY(QString name READ name WRITE setName);
  Q_PROPERTY(QColor color READ color WRITE setColor);

  //  QML_ELEMENT

public:
  explicit PieChart(QQuickItem *parent = nullptr);

  inline QString name() const { return _name; }
  void setName(const QString &name);

  inline QColor color() const { return _color; }
  void setColor(const QColor &color);

  void paint(QPainter *painter);

private:
  QString _name;
  QColor _color;
};

} // namespace ui::quick

QML_DECLARE_TYPE(ui::quick::PieChart)
