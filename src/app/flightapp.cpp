#include "app/flightapp.hpp"
#include "app/logwidget.hpp"
#include "app/routewidget.hpp"
#include "app/flightwidget.hpp"
#include <QHBoxLayout>
#include <QStackedLayout>
#include <QListWidgetItem>
#include <QLabel>

FlightApp::FlightApp(QWidget *parent):
		QMainWindow(parent) {
	setWindowTitle("客户端");
	resize(800, 600);

	auto *central_widget = new QWidget(this);
	auto *central_layout = new QHBoxLayout(central_widget);

	menu.setViewMode(QListView::IconMode);
	menu.setFlow(QListView::TopToBottom);
	menu.setMovement(QListView::Static);
	menu.viewport()->setAutoFillBackground(false);
	menu.setFrameShape(QFrame::NoFrame);
	menu.setTextElideMode(Qt::ElideNone);
	menu.setStyleSheet(R"(
		QListView::item {
			padding: 10px;
			border: none;
		}
		QListView::item:selected {
			border-style: solid;
			border-width: 1px;
			border-radius: 10px;
		}
	)");

	menu.addItem(new QListWidgetItem(QIcon(":/icons/help.svg"), "查看日志"));
	menu.addItem(new QListWidgetItem(QIcon(":/icons/help.svg"), "设计航线"));
	menu.addItem(new QListWidgetItem(QIcon(":/icons/help.svg"), "管理航班"));
	menu.addItem(new QListWidgetItem(QIcon(":/icons/help.svg"), "帮助文档"));
	menu.setFixedWidth(menu.sizeHintForColumn(0));
	menu.setFixedHeight((menu.sizeHintForRow(0) + 5) * menu.count() + 2 * menu.frameWidth());

	auto *widgets = new QStackedLayout;
	widgets->addWidget(LogWidget::init());
	widgets->addWidget(RouteWidget::init());
	widgets->addWidget(FlightWidget::init());
	widgets->addWidget(new QLabel("帮助文档"));

	central_layout->addWidget(&menu);
	central_layout->addLayout(widgets);

	setCentralWidget(central_widget);

	connect(&menu, &QListWidget::currentRowChanged, widgets, &QStackedLayout::setCurrentIndex);

	menu.setCurrentRow(0);
}
