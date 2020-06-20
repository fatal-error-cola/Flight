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
	setWindowTitle("\xe5\xae\xa2\xe6\x88\xb7\xe7\xab\xaf");
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

	menu.addItem(new QListWidgetItem(QIcon(":/icons/log.svg"),
		"\xe6\x9f\xa5\xe7\x9c\x8b\xe6\x97\xa5\xe5\xbf\x97"));
	menu.addItem(new QListWidgetItem(QIcon(":/icons/route.svg"),
		"\xe8\xae\xbe\xe8\xae\xa1\xe8\x88\xaa\xe7\xba\xbf"));
	menu.addItem(new QListWidgetItem(QIcon(":/icons/flight.svg"),
		"\xe7\xae\xa1\xe7\x90\x86\xe8\x88\xaa\xe7\x8f\xad"));
	menu.addItem(new QListWidgetItem(QIcon(":/icons/guide.svg"),
		"\xe5\xb8\xae\xe5\x8a\xa9\xe6\x96\x87\xe6\xa1\xa3"));
	menu.setFixedWidth(menu.sizeHintForColumn(0));
	menu.setFixedHeight((menu.sizeHintForRow(0) + 5) * menu.count() + 2 * menu.frameWidth());

	auto *widgets = new QStackedLayout;
	widgets->addWidget(LogWidget::init());
	widgets->addWidget(RouteWidget::init());
	widgets->addWidget(FlightWidget::init());
	widgets->addWidget(new QLabel("\xe5\xb8\xae\xe5\x8a\xa9\xe6\x96\x87\xe6\xa1\xa3"));

	central_layout->addWidget(&menu);
	central_layout->addLayout(widgets);

	setCentralWidget(central_widget);

	connect(&menu, &QListWidget::currentRowChanged, widgets, &QStackedLayout::setCurrentIndex);

	menu.setCurrentRow(0);
}
