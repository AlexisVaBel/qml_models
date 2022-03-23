//
// Created by belyeav on 23.03.2022.
//
#include "Navigable.h"

using namespace ui::quick;

Navigable::Navigable(QQuickItem* parent)
	: Super(parent)
	, _containerItem(new QQuickItem{this}) {
	_containerItem->setTransformOrigin(TransformOrigin::TopLeft);
	_containerItem->setAcceptTouchEvents(true);

	connect(_containerItem, &QQuickItem::childrenRectChanged, // Listen to children rect changes to update containerItem size
			[this]() {
				if (this->_containerItem != nullptr) {
					const auto cr = this->_containerItem->childrenRect();
					this->_containerItem->setWidth(cr.width());
					this->_containerItem->setHeight(cr.height());
				}
			});
	setAcceptedMouseButtons(Qt::RightButton | Qt::LeftButton);
	setTransformOrigin(TransformOrigin::TopLeft);

	setAcceptTouchEvents(true);
}

void Navigable::setNavigable(bool navigable) noexcept {
	if (navigable != _navigable) {
		_navigable = navigable;
		emit navigableChanged();
	}
}

void Navigable::centerOn(QQuickItem* item) {
	if (_containerItem == nullptr ||
			item == nullptr)
		return;

	const qreal zoom = _containerItem->scale();

	// 1.
	const QPointF itemPos = _containerItem->mapToItem(item, QPointF{-item->width() / 2., -item->height() / 2.});
	QPointF containerPos{0., 0.};
	containerPos.rx() = itemPos.x() * zoom;
	containerPos.ry() = itemPos.y() * zoom;
	_containerItem->setPosition(containerPos);

	// 2.
	const QPointF viewCenter = QPointF{width() / 2., height() / 2.};
	const QPointF viewCenterContainerCs = mapToItem(_containerItem, viewCenter);
	const QPointF viewOriginContainerCs = mapToItem(_containerItem, QPointF{0, 0});
	const QPointF translationContainerCs = viewCenterContainerCs - viewOriginContainerCs;
	_containerItem->setPosition(_containerItem->position() + (translationContainerCs * zoom));
}

void Navigable::centerOnPosition(QPointF position) {
	//
	QPointF navigableCenter{width() / 2., height() / 2.};
	QPointF navigableCenterContainerCs = mapToItem(_containerItem, navigableCenter);
	QPointF translation{navigableCenterContainerCs - position};
	_containerItem->setPosition(QPointF{_containerItem->x() + translation.x(),
			_containerItem->y() + translation.y()});
}

void Navigable::fitInView() {
	QRectF content = _containerItem->childrenRect();
	if (!content.isEmpty()) { // Protect against div/0, can't fit if there is no content...
		const qreal viewWidth = width();
		const qreal viewHeight = height();

		const qreal fitWidthZoom = viewWidth / content.width();
		const qreal fitHeightZoom = viewHeight / content.height();

		qreal fitZoom = fitWidthZoom;
		if (content.height() * fitWidthZoom > viewHeight)
			fitZoom = fitHeightZoom;
		fitZoom -= 0.1; // Add margins

		// FIXME: Buggy, do something similar to  centerOn() 2.0...
		QPointF contentPos{0., 0.};

		contentPos = content.topLeft() * fitZoom;
		_containerItem->setPosition(-contentPos);
//		_panModified = false;
//		_zoomModified = false;

		// Don't use setZoom() because we force a TopLeft scale
//		if (isValidZoom(fitZoom)) {
//			_zoom = fitZoom;
//			_containerItem->setScale(_zoom);
			//			emit zoomChanged();
			//			emit containerItemModified();
			//			navigableContainerItemModified();
//		}
	}
}
