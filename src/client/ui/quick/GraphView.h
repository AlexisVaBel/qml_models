#pragma once

#include <Navigable.h>

namespace ui::quick {

class GraphView : public Navigable {
	Q_OBJECT

public:
	explicit GraphView(QQuickItem* parent = nullptr);
	virtual ~GraphView() override = default;
	GraphView(const GraphView&) = delete;

public:
	//! Graph that should be displayed in this graph view.
	//	Q_PROPERTY(Graph*  graph READ getGraph WRITE setGraph NOTIFY
	//graphChanged FINAL) 	void                    setGraph(Graph* graph); 	inline
	//Graph*      getGraph() const noexcept { return _graph.data(); } private:
	//	QPointer<Graph>    _graph = nullptr;
	// signals:
	//	void                    graphChanged();

protected:
	//! Called when the mouse is clicked in the container (base implementation
	//! empty).
	virtual void navigableClicked(QPointF pos) override;
	virtual void navigableRightClicked(QPointF pos) override;

	//! Utilisty method to convert a given \c url to a local file path (if
	//! possible, otherwise return an empty string).
	Q_INVOKABLE QString urlToLocalFile(QUrl url) const noexcept;

signals:
	void connectorChanged();

	void rightClicked(QPointF pos);

protected:
	virtual void selectionRectActivated(const QRectF& rect) override;

	virtual void selectionRectEnd() override;

private:
	QSet<QQuickItem*> _selectedItems;
};

} // namespace ui::quick

QML_DECLARE_TYPE(ui::quick::GraphView);
