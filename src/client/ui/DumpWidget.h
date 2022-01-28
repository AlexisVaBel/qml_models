#pragma once

#include <QWidget>

namespace client::ui {

class DumpWidget : public QWidget {
	Q_OBJECT
	using Self = DumpWidget;
	using Super = QWidget;

public:
	DumpWidget(QWidget* parent = nullptr);
	~DumpWidget();
};
} // namespace client::ui
