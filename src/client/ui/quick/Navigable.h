//-----------------------------------------------------------------------------
//
// \file	Navigable.h
// \author	based on code of that benoit@destrat.io, thanks for
// \date	2022 03 23
// \info    tryed to use code style - combination of
//-----------------------------------------------------------------------------

#pragma once

#include <QPointer>
#include <QQuickItem>

namespace ui::quick {
class Navigable : public QQuickItem {
	Q_OBJECT
	using Self = Navigable;
	using Super = QQuickItem;

public:
	explicit Navigable(QQuickItem* parent = nullptr);
	virtual ~Navigable() override = default;
	Navigable(Navigable const&) = delete;

	/*! \brief (Dis)Enable navigation.
     */
	Q_PROPERTY(bool navigable READ getNavigable WRITE setNavigable NOTIFY navigableChanged FINAL)
	inline bool getNavigable() const noexcept {
		return _navigable;
	}
	void setNavigable(bool navigable) noexcept;
signals:
	void navigableChanged();

private:
	bool _navigable{true};

public:
	/*! \brief Container for area child items
     */
	Q_PROPERTY(QQuickItem* containerItem READ getContainerItem CONSTANT FINAL)
	inline QQuickItem* getContainerItem() noexcept {
		return _containerItem.data();
	}

private:
	QPointer<QQuickItem> _containerItem{nullptr};

public:
	//! Center the view on a given child item.
	Q_INVOKABLE void centerOn(QQuickItem* item);

	//! Center the view on a given position
	Q_INVOKABLE void centerOnPosition(QPointF position);

	/*! Fit the area content (\c containerItem childs) in view and update current zoom level.
     *
     */
	Q_INVOKABLE void fitInView();
};
} // namespace ui::quick

QML_DECLARE_TYPE(ui::quick::Navigable)
