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

#include <Grid.h>

// TODO  (Me - Aleksei) fix style

namespace ui::quick {
class Navigable : public QQuickItem {
  Q_OBJECT
  using Self = Navigable;
  using Super = QQuickItem;

public:
  explicit Navigable(QQuickItem *parent = nullptr);
  virtual ~Navigable() override = default;
  Navigable(Navigable const &) = delete;

  /*! \brief (Dis)Enable navigation.
   */
  Q_PROPERTY(bool navigable READ getNavigable WRITE setNavigable NOTIFY
                 navigableChanged FINAL)
  inline bool getNavigable() const noexcept { return _navigable; }
  void setNavigable(bool navigable) noexcept;
signals:
  void navigableChanged();

private:
  bool _navigable{true};

public:
  /*! \brief Container for area child items
   */
  Q_PROPERTY(QQuickItem *containerItem READ getContainerItem CONSTANT FINAL)
  inline QQuickItem *getContainerItem() noexcept {
    return _containerItem.data();
  }

private:
  QPointer<QQuickItem> _containerItem{nullptr};

public:
  //! Center the view on a given child item.
  Q_INVOKABLE void centerOn(QQuickItem *item);

  //! Center the view on a given position
  Q_INVOKABLE void centerOnPosition(QPointF position);

  /*! Fit the area content (\c containerItem childs) in view and update current
   * zoom level.
   *
   */
  Q_INVOKABLE void fitInView();

public:
  //! \brief Auto fitting mode.
  enum AutoFitMode {
    //! No auto-fitting (default).
    NoAutoFit,
    /*! Auto fit area content when the area is resized without user modified
     * zoom or pan, and eventually auto center content.
     *
     * Setting \c autoFitMode to \c AutoFit has the following effects:
     * \li Content will be fitted automatically when the view is resized if user
     * has not already applied a custom zoom or pan. \li If the user has applied
     * a custom zoom or pan, the content will be automatically centered if the
     * transformed container item is smaller than navigable area. \li Content
     * will be anchored to the left or the right view borders when its width is
     * larger than the navigable area, but there is a space "in panning" between
     * content and view border.
     */
    AutoFit
  };
  Q_ENUM(AutoFitMode)

  /*! \brief Current auto-fit mode (default to NoAutoFit).    */
  Q_PROPERTY(AutoFitMode autoFitMode READ getAutoFitMode WRITE setAutoFitMode
                 NOTIFY autoFitModeChanged FINAL)
  //! \sa autoFitMode
  AutoFitMode getAutoFitMode() const { return _autoFitMode; }
  //! \sa autoFitMode
  void setAutoFitMode(AutoFitMode autoFitMode);

private:
  //! \copydoc autoFitMode
  AutoFitMode _autoFitMode{NoAutoFit};
signals:
  //! \sa autoFitMode
  void autoFitModeChanged();

public:
  /*! \brief Zoom incrementation delta (default to 0.05,ie 5%).
   */
  Q_PROPERTY(qreal zoomIncrement READ getZoomIncrement WRITE setZoomIncrement
                 NOTIFY zoomIncrementChanged FINAL)
  //! \sa zoomIncrement
  qreal getZoomIncrement() const { return _zoomIncrement; }
  //! \sa zoomIncrement
  void setZoomIncrement(qreal zoomIncrement) noexcept {
    _zoomIncrement = zoomIncrement;
    emit zoomIncrementChanged();
  }

private:
  //! \copydoc zoomIncrement
  qreal _zoomIncrement = 0.05;
signals:
  //! \sa zoomIncrement
  void zoomIncrementChanged();

public:
  /*! \brief Area current zoom level (default to 1.0).
   *
   * Setting a zoom value outside the (minZoom, maxZoom) range has no effect.
   *
   * Accessing zoom directly from QML is safe, since setZoom() is protected
   * against binding loops.
   */
  Q_PROPERTY(qreal zoom READ getZoom WRITE setZoom NOTIFY zoomChanged FINAL)
  //! \sa zoom
  inline qreal getZoom() const noexcept { return _zoom; }
  /*! \brief Set navigable area current zoom (zoom is applied on current \c
   * zoomOrigin).
   *
   * \note To avoid QML binding loops, this setter is protected against setting
   * the same value multiple times. \sa zoom
   */
  void setZoom(qreal zoom);
  //! Set area current zoom centered on a given \c center point.
  Q_INVOKABLE void zoomOn(QPointF center, qreal zoom);
  //! Return true if zoom is valid (ie it is different from the actual zoom and
  //! in the (minZoom, maxZoom) range.
  bool isValidZoom(qreal zoom) const;

private:
  //! \copydoc zoom
  qreal _zoom = 1.0;
signals:
  //! \sa zoom
  void zoomChanged();

private:
  //! Flag set to true if area panning has been modified since the last
  //! fitInView() call.
  bool _panModified = false;
  //! Flag set to true if area zoom has been modified since the last fitInView()
  //! call.
  bool _zoomModified = false;

public:
  /*! \brief Origin point where any zoom set view setZoom or \c zoom will be
   * applied (default to QQuickItem::Center).
   */
  Q_PROPERTY(QQuickItem::TransformOrigin zoomOrigin READ getZoomOrigin WRITE
                 setZoomOrigin NOTIFY zoomOriginChanged FINAL)
  //! \sa zoomOrigin
  QQuickItem::TransformOrigin getZoomOrigin() const noexcept {
    return _zoomOrigin;
  }
  /*! \brief Set navigable area current zoom origin (either QQuickItem::TopLeft
   * or QQuickItem::Center).
   *
   * \note Zooming initiated via mouse wheel is always applied at current mouse
   * position. \sa zoom
   */
  void setZoomOrigin(QQuickItem::TransformOrigin zoomOrigin);

private:
  //! \copydoc zoomOrigin
  QQuickItem::TransformOrigin _zoomOrigin = QQuickItem::Center;
signals:
  //! \sa zoomOrigin
  void zoomOriginChanged();

public:
  //! Area maximum zoom level (-1 = no maximum zoom limitation, 1.0 = no zoom
  //! allowed, >1.0 = zoomMax*100% maximum zoom).
  Q_PROPERTY(qreal zoomMax READ getZoomMax WRITE setZoomMax NOTIFY
                 zoomMaxChanged FINAL)
  //! \sa zoomMax
  qreal getZoomMax() const noexcept { return _zoomMax; }
  //! \sa zoomMax
  void setZoomMax(qreal zoomMax);

private:
  //! \copydoc zoomMax
  qreal _zoomMax = -1.0;
signals:
  //! \sa zoomMax
  void zoomMaxChanged();

public:
  //! Area minimum zoom level, default to 0.1 (10% zoom), zoomMin can't be <= 0.
  Q_PROPERTY(qreal zoomMin READ getZoomMin WRITE setZoomMin NOTIFY
                 zoomMinChanged FINAL)
  //! \sa zoomMin
  qreal getZoomMin() const noexcept { return _zoomMin; }
  //! \sa zoomMin
  void setZoomMin(qreal zoomMin);

private:
  //! \copydoc zoomMin
  qreal _zoomMin = 0.1;
signals:
  //! \sa zoomMin
  void zoomMinChanged();

signals:
  //! Emitted whenever the mouse is clicked in the container.
  void clicked(QVariant pos);

  //! Emitted whenever the mouse is right clicked in the container.
  void rightClicked(QVariant pos);

  //! Emitted whenever the container item is scaled (zoomed) or panned.
  void containerItemModified();

protected:
  //! Called when the mouse is clicked in the container (base implementation
  //! empty).
  virtual void navigableClicked(QPointF pos) { Q_UNUSED(pos); }
  //! Called when the mouse is right clicked in the container (base
  //! implementation empty).
  virtual void navigableRightClicked(QPointF pos) { Q_UNUSED(pos); }
  //! Called when the container item is scaled (zoomed) or panned (base
  //! implementation empty).
  virtual void navigableContainerItemModified() {}

public:
  //! True when the navigable conctent area is actually dragged.
  Q_PROPERTY(bool dragActive READ getDragActive WRITE setDragActive NOTIFY
                 dragActiveChanged FINAL)
  //! \copydoc dragActive
  inline bool getDragActive() const noexcept { return _dragActive; }
  //! \copydoc dragActive
  void setDragActive(bool dragActive) noexcept;

private:
  //! \copydoc dragActive
  bool _dragActive{false};
signals:
  //! \copydoc dragActive
  void dragActiveChanged();

protected:
#if QT_VERSION < QT_VERSION_CHECK(6, 0, 0)
  virtual void geometryChanged(const QRectF &newGeometry,
                               const QRectF &oldGeometry) override;
#else
  virtual void geometryChange(const QRectF &newGeometry,
                              const QRectF &oldGeometry) override;
#endif
  virtual void mouseMoveEvent(QMouseEvent *event) override;
  virtual void mousePressEvent(QMouseEvent *event) override;
  virtual void mouseReleaseEvent(QMouseEvent *event) override;
  virtual void wheelEvent(QWheelEvent *event) override;

protected:
  bool _leftButtonPressed = false;
  QPointF _lastPan{};

  /*! \name Selection Rectangle Management */ //------------------------------
                                              //@{
public:
  /*! \brief Enable or disable visual selection rect (default to true, ie
   * selection is enabled).
   */
  Q_PROPERTY(
      bool selectionRectEnabled READ getSelectionRectEnabled WRITE
          setSelectionRectEnabled NOTIFY selectionRectEnabledChanged FINAL)
  //! \sa selectionRectEnabled
  inline bool getSelectionRectEnabled() const noexcept {
    return _selectionRectEnabled;
  }
  //! \sa selectionRectEnabled
  void setSelectionRectEnabled(bool selectionRectEnabled) noexcept;

private:
  //! \copydoc selectionRectEnabled
  bool _selectionRectEnabled = true;
signals:
  //! \sa selectionRectEnabled
  void selectionRectEnabledChanged();

public:
  /*! \brief Selection rectangle is activated instead of view panning when CTRL
   * key is used while clicking and dragging.
   */
  Q_PROPERTY(QQuickItem *selectionRectItem READ getSelectionRectItem WRITE
                 setSelectionRectItem FINAL)
  //! \copydoc selectionRectItem
  inline QQuickItem *getSelectionRectItem() noexcept {
    return _selectionRectItem;
  }
  //! \copydoc selectionRectItem
  void setSelectionRectItem(QQuickItem *selectionRectItem) noexcept;

private:
  //! \copydoc selectionRectItem
  QPointer<QQuickItem> _selectionRectItem = nullptr;

  //! \copydoc selectionRectItem
  bool _ctrlLeftButtonPressed = false;

  //! \copydoc selectionRectItem
  bool _selectRectActive = false;

  //! \copydoc selectionRectItem
  QPointF _lastSelectRect{};
  QPointF _startSelectRect{};

protected:
  //! Called when the selectionRectItem is activated, ie it's geometry has
  //! changed, \c rect is in containerItem space.
  virtual void selectionRectActivated(const QRectF &rect);

  //! Called when the selectionRectItem interaction ends.
  virtual void selectionRectEnd();
  //@}
public:
  Q_PROPERTY(Grid *grid READ getGrid WRITE setGrid NOTIFY gridChanged FINAL)

  Grid *getGrid() noexcept { return _grid.data(); }
  const Grid *getGrid() const noexcept { return _grid.data(); }
  void setGrid(Grid *grid) noexcept;

private:
  //! Force update of grid.
  void updateGrid() noexcept;
  //! \copydoc grid
  QPointer<Grid> _grid;

  std::unique_ptr<Grid> _defaultGrid;
signals:
  void gridChanged();
};
} // namespace ui::quick

QML_DECLARE_TYPE(ui::quick::Navigable)
