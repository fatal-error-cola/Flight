#include "app/flightapp.hpp"
#include "app/routedesigner.hpp"
#include "app/logwidget.hpp"
#include <QHBoxLayout>
#include <QListWidget>
#include <QListWidgetItem>
#include <QStackedLayout>
#include <QLabel>

FlightApp::FlightApp(QWidget *parent): QMainWindow(parent) {
	setWindowTitle("客户端");
	resize(800, 600);

	auto *central_widget = new QWidget(this);
	auto *central_layout = new QHBoxLayout(central_widget);

	auto *tab_widget = new QListWidget;
	tab_widget->setFixedWidth(82);
	tab_widget->setViewMode(QListView::IconMode);
	tab_widget->setFlow(QListView::TopToBottom);
	tab_widget->setMovement(QListView::Static);
	tab_widget->viewport()->setAutoFillBackground(false);
	tab_widget->setFrameShape(QListWidget::NoFrame);
	tab_widget->setTextElideMode(Qt::ElideNone);
	tab_widget->setStyleSheet(R"(
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

	tab_widget->addItem(new QListWidgetItem(QIcon(":/icons/help.svg"), "设计航线"));
	tab_widget->addItem(new QListWidgetItem(QIcon(":/icons/help.svg"), "管理航班"));
	tab_widget->addItem(new QListWidgetItem(QIcon(":/icons/help.svg"), "查看日志"));
	tab_widget->addItem(new QListWidgetItem(QIcon(":/icons/help.svg"), "帮助文档"));

	auto *widgets = new QStackedLayout;
	widgets->addWidget(new RouteDesigner);
	widgets->addWidget(new QLabel("管理航班"));
	widgets->addWidget(LogWidget::init());
	widgets->addWidget(new QLabel("帮助文档"));

	central_layout->addWidget(tab_widget);
	central_layout->addLayout(widgets);

	setCentralWidget(central_widget);

	connect(tab_widget, &QListWidget::currentRowChanged, widgets, &QStackedLayout::setCurrentIndex);

	tab_widget->setCurrentRow(0);
}
