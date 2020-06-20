#include "app/flightwidget.hpp"
#include <QGridLayout>
#include <QLabel>
#include <QPushButton>
#include "app/flightdesigner.hpp"
#include "models.hpp"
#include "containers.hpp"

FlightMenuItem::FlightMenuItem(unsigned index_, QWidget *parent):
		MenuItem(parent), index(index_) {
	if(index == 0) setNewItemUi();
	else setUi();
}

void FlightMenuItem::setUi() {
	qDeleteAll(findChildren<QWidget*>(QString(), Qt::FindDirectChildrenOnly));

	auto *flight = Flights::getInstance()->get(index);

	auto *layout = static_cast<QGridLayout *>(this->layout());
	if(layout == nullptr) layout = new QGridLayout(this);

	auto *flight_label = new QLabel(flight->info.flight);
	flight_label->setFont(QFont("Arial", 30, QFont::Bold));

	layout->addWidget(flight_label, 0, 0, -1, 1);
	layout->addItem(new QSpacerItem(20, 0, QSizePolicy::Minimum, QSizePolicy::Minimum), 0, 1, -1, 1);
	layout->addWidget(new QLabel(flight->info.depart.airport->name), 0, 2, Qt::AlignRight);
	layout->addWidget(new QLabel("—"), 0, 3);
	layout->addWidget(new QLabel(flight->info.arrive.airport->name), 0, 4, Qt::AlignLeft);
	layout->addWidget(new QLabel(flight->info.depart.time.toString("yyyy.MM.dd hh:mm")), 1, 2, Qt::AlignRight);
	layout->addWidget(new QLabel("—"), 1, 3);
	layout->addWidget(new QLabel(flight->info.arrive.time.toString("yyyy.MM.dd hh:mm")), 1, 4, Qt::AlignLeft);
	layout->addItem(new QSpacerItem(0, 0, QSizePolicy::Expanding, QSizePolicy::Minimum), 0, 5, -1, 1);
}

void FlightMenuItem::mouseReleaseEvent(QMouseEvent *) {
	auto *designer = new FlightDesigner(Flights::getInstance()->get(index));
	FlightWidget::getInstance()->addWidget(designer);
	FlightWidget::getInstance()->setCurrentWidget(designer);
	connect(designer, &FlightDesigner::finished,
		[this] { setUi(); FlightWidget::getInstance()->menu.insertItem(this); });
}

FlightWidget::FlightWidget(QWidget *parent):
		QStackedWidget(parent) {
	addWidget(&menu);
}
