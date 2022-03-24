#include "Grid.h"

using namespace ui::quick;

Grid::Grid(QQuickItem *parent) : QQuickItem(parent) { setEnabled(false); }
//

bool Grid::updateGrid(const QRectF &viewRect, const QQuickItem &container,
                      const QQuickItem &navigable) noexcept {
  Q_UNUSED(viewRect)
  Q_UNUSED(container)
  Q_UNUSED(navigable)
  return false;
}

bool Grid::updateGrid() noexcept { return false; }
//-----------------------------------------------------------------------------

/* Grid Management */ //--------------------------------------------------------
void Grid::setThickColor(QColor thickColor) noexcept {
  if (thickColor != _thickColor) {
    _thickColor = thickColor;
    emit thickColorChanged();
  }
}

void Grid::setGridWidth(qreal gridWidth) noexcept {
  if (gridWidth < 0.001) {
    qWarning() << "qan::Grid::setMinorWidth(): Warning, major width should be "
                  "superior to 0.0";
    return;
  }
  if (!qFuzzyCompare(1.0 + gridWidth, 1.0 + _gridWidth)) {
    _gridWidth = gridWidth;
    emit gridWidthChanged();
  }
}

void Grid::setGridScale(qreal gridScale) noexcept {
  if (gridScale < 0.001) {
    qWarning() << "qan::Grid::setGridScale(): Warning, grid scale should be "
                  "superior to 0.0";
    return;
  }
  if (!qFuzzyCompare(1.0 + gridScale, 1.0 + _gridScale)) {
    _gridScale = gridScale;
    emit gridScaleChanged();
    updateGrid();
  }
}

void Grid::setGridMajor(int gridMajor) noexcept {
  if (gridMajor < 1) {
    qWarning() << "qan::Grid::setGridMajor(): Warning, grid major should be "
                  "superior or equal to 1";
    return;
  }
  if (gridMajor != _gridMajor) {
    _gridMajor = gridMajor;
    emit gridMajorChanged();
    updateGrid();
  }
}
