#include "GraphView.h"

#include <QQuickItem>

using namespace ui::quick;

GraphView::GraphView(QQuickItem* parent) {
	setAntialiasing(true);
	setSmooth(true);
	setFocus(true);
}

void GraphView::navigableClicked(QPointF pos) {
	Q_UNUSED(pos)
}

void GraphView::navigableRightClicked(QPointF pos) {
	emit rightClicked(pos);
}

QString GraphView::urlToLocalFile(QUrl url) const noexcept {
	if (url.isLocalFile())
		return url.toLocalFile();
	return QString{};
}
//-----------------------------------------------------------------------------

/* Selection Rectangle Management */ //-----------------------------------------
void GraphView::selectionRectActivated(const QRectF& rect) {
	if (rect.isEmpty())
		return;
	// Algorithm:
	// 1. Iterate over all already selected items, remove one that are no longer
	// inside selection rect
	//    (for example, if selection rect has grown down...)
	// 2. Iterate over all graph items, select items inside selection rect.

	// 1.

	// 2.
}

void GraphView::selectionRectEnd() {
	_selectedItems.clear(); // Clear selection cache
}
