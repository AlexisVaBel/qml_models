#pragma once

#include <QQuickItem>
#include <QtQml>

namespace ui::quick {
class Grid : public QQuickItem {
  Q_OBJECT
public:
  explicit Grid(QQuickItem *parent = nullptr);
  virtual ~Grid() override = default;
  Grid(Grid const &) = delete;

public:
  virtual bool updateGrid(const QRectF &viewRect, const QQuickItem &container,
                          const QQuickItem &navigable) noexcept;

protected:
  virtual bool updateGrid() noexcept;

public:
  Q_PROPERTY(QColor thickColor READ getThickColor WRITE setThickColor NOTIFY
                 thickColorChanged FINAL)
  void setThickColor(QColor thickColor) noexcept;
  inline QColor getThickColor() const noexcept { return _thickColor; }
signals:
  void thickColorChanged();

private:
  QColor _thickColor{211, 211, 211}; // lightgrey #D3D3D3 / rgb(211,211,211)

public:
  Q_PROPERTY(qreal gridWidth READ getGridWidth WRITE setGridWidth NOTIFY
                 gridWidthChanged FINAL)
  void setGridWidth(qreal gridWidth) noexcept;
  inline qreal getGridWidth() const noexcept { return _gridWidth; }
signals:
  void gridWidthChanged();

private:
  qreal _gridWidth{3.};

public:
  Q_PROPERTY(qreal gridScale READ getGridScale WRITE setGridScale NOTIFY
                 gridScaleChanged FINAL)
  void setGridScale(qreal gridScale) noexcept;
  inline qreal getGridScale() const noexcept { return _gridScale; }
signals:
  void gridScaleChanged();

private:
  qreal _gridScale{100.};

public:
  Q_PROPERTY(int gridMajor READ getGridMajor WRITE setGridMajor NOTIFY
                 gridMajorChanged FINAL)
  void setGridMajor(int gridMajor) noexcept;
  inline int getGridMajor() const noexcept { return _gridMajor; }
signals:
  void gridMajorChanged();

private:
  int _gridMajor{5};
};

} // namespace ui::quick

QML_DECLARE_TYPE(ui::quick::Grid);
