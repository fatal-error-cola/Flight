#include "app/routedesigner.hpp"
#include <utility>
#include <QCompleter>
#include <QGridLayout>
#include <QFormLayout>
#include <QGroupBox>
#include <QLabel>
#include <QPushButton>
#include <QDialogButtonBox>
#include "app/flightapp.hpp"
#include "app/routewidget.hpp"
#include "app/flightwidget.hpp"
#include "app/flightdesigner.hpp"
#include "helpers.hpp"
#include "models.hpp"
#include "containers.hpp"

RouteDesigner::RouteDesigner(Route *route_, QWidget *parent):
		QWidget(parent), route(route_) {
	repeat.setMaximum(999);
	repeat.setSuffix(" \xe5\xa4\xa9");

	depart.airport.setEditable(true);
	depart.airport.setModel(Airports::getInstance());
	auto depart_airport_completer = new QCompleter(Airports::getInstance(), &depart.airport);
	depart_airport_completer->setFilterMode(Qt::MatchContains);
	depart_airport_completer->setCaseSensitivity(Qt::CaseInsensitive);
	depart.airport.setCompleter(depart_airport_completer);

	depart.time.setCalendarPopup(true);
	depart.time.setDisplayFormat("yyyy/MM/dd hh:mm");
	depart.time.setMinimumDate(QDate::currentDate().addDays(1));

	arrive.airport.setEditable(true);
	arrive.airport.setModel(Airports::getInstance());
	auto arrive_airport_completer = new QCompleter(Airports::getInstance(), &arrive.airport);
	arrive_airport_completer->setFilterMode(Qt::MatchContains);
	arrive_airport_completer->setCaseSensitivity(Qt::CaseInsensitive);
	arrive.airport.setCompleter(arrive_airport_completer);

	arrive.time.setCalendarPopup(true);
	arrive.time.setDisplayFormat("yyyy/MM/dd hh:mm");
	arrive.time.setMinimumDate(QDate::currentDate().addDays(1));

	for(unsigned i = 0; i < Server::Meal::NUM; ++i)
		server.meal[i].setText(Server::Meal::name[i]);

	server.hasWiFi.setText("Wi-Fi");

	for(unsigned i = 0; i < Class::NUM; ++i) {
		classes[i].tickets.setMaximum(9999);
		classes[i].cost.setMaximum(99999);
		classes[i].cost.setSuffix(" \xe5\x85\x83");
	}


	auto *layout = new QGridLayout(this);

	auto *depart_box = new QGroupBox;
	auto *depart_layout = new QFormLayout(depart_box);
	depart_layout->addRow("\xe6\x9c\xba\xe5\x9c\xba\xef\xbc\x9a", &depart.airport);
	depart_layout->addRow("\xe8\x88\xaa\xe7\xab\x99\xe6\xa5\xbc\xef\xbc\x9a", &depart.terminal);
	depart_layout->addRow("\xe5\xbd\x93\xe5\x9c\xb0\xe6\x97\xb6\xe9\x97\xb4\xef\xbc\x9a", &depart.time);

	auto *arrive_box = new QGroupBox;
	auto *arrive_layout = new QFormLayout(arrive_box);
	arrive_layout->addRow("\xe6\x9c\xba\xe5\x9c\xba\xef\xbc\x9a", &arrive.airport);
	arrive_layout->addRow("\xe8\x88\xaa\xe7\xab\x99\xe6\xa5\xbc\xef\xbc\x9a", &arrive.terminal);
	arrive_layout->addRow("\xe5\xbd\x93\xe5\x9c\xb0\xe6\x97\xb6\xe9\x97\xb4\xef\xbc\x9a", &arrive.time);

	auto *server_box = new QGroupBox;
	auto *server_layout = new QHBoxLayout(server_box);
	for(unsigned i = 0; i < Server::Meal::NUM; ++i)
		server_layout->addWidget(&server.meal[i]);
	server_layout->addWidget(&server.hasWiFi);

	auto *classes_layout = new QHBoxLayout;
	for(unsigned i = 0; i < Class::NUM; ++i) {
		auto *class_box = new QGroupBox(Class::name[i]);
		class_box->setAlignment(Qt::AlignHCenter);
		auto *class_layout = new QFormLayout(class_box);
		class_layout->addRow("\xe5\xba\xa7\xe4\xbd\x8d\xef\xbc\x9a", &classes[i].tickets);
		class_layout->addRow("\xe4\xbb\xb7\xe6\xa0\xbc\xef\xbc\x9a", &classes[i].cost);
		classes_layout->addWidget(class_box);
	}

	auto *button_layout = new QHBoxLayout;

	if(route != nullptr) {
		auto *submit_button = new QPushButton("\xe5\x8f\x91\xe5\xb8\x83");
		submit_button->setFixedSize(80, 32);
		button_layout->addWidget(submit_button);
		connect(submit_button, &QPushButton::clicked, [this] {
			auto *designer = new FlightDesigner(&route->info);
			FlightWidget::getInstance()->addWidget(designer);
			FlightWidget::getInstance()->setCurrentWidget(designer);
			FlightApp::getInstance()->menu.setCurrentRow(2);
			if(route->repeat == 0) emit remove();
			else {
				route->info.depart.time = route->info.depart.time.addDays(route->repeat);
				route->info.arrive.time = route->info.arrive.time.addDays(route->repeat);
				emit finished();
			}
			deleteLater();
		});
	}

	auto *buttons = new QDialogButtonBox(QDialogButtonBox::Ok | QDialogButtonBox::Cancel);
	button_layout->addItem(new QSpacerItem(0, 0, QSizePolicy::Expanding, QSizePolicy::Minimum));
	button_layout->addWidget(buttons);

	auto *first_column = new QFormLayout;
	first_column->addRow("\xe8\x88\xaa\xe7\x8f\xad\xe5\x8f\xb7\xef\xbc\x9a", &flight);
	first_column->addRow("\xe8\x88\xaa\xe5\x8f\xb8\xef\xbc\x9a", &airline);
	first_column->addRow("\xe6\x9c\xba\xe5\x9e\x8b\xef\xbc\x9a", &aircraft);
	first_column->addRow("\xe5\x91\xa8\xe6\x9c\x9f\xef\xbc\x9a", &repeat);

	auto *second_column = new QGridLayout;
	second_column->addWidget(new QLabel("\xe5\x87\xba\xe5\x8f\x91\xef\xbc\x9a"), 0, 0, Qt::AlignRight | Qt::AlignVCenter);
	second_column->addWidget(depart_box, 0, 1, Qt::AlignLeft);
	second_column->addWidget(new QLabel("\xe5\x88\xb0\xe8\xbe\xbe\xef\xbc\x9a"), 1, 0, Qt::AlignRight | Qt::AlignVCenter);
	second_column->addWidget(arrive_box, 1, 1, Qt::AlignLeft);
	second_column->addWidget(new QLabel("\xe6\x9c\x8d\xe5\x8a\xa1\xef\xbc\x9a"), 2, 0, Qt::AlignRight | Qt::AlignVCenter);
	second_column->addWidget(server_box, 2, 1, Qt::AlignLeft);

	layout->addLayout(first_column, 0, 1, Qt::AlignHCenter);
	layout->addLayout(second_column, 0, 2, Qt::AlignHCenter);
	layout->addLayout(classes_layout, 1, 1, 1, 2);
	layout->addItem(new QSpacerItem(0, 0, QSizePolicy::Expanding, QSizePolicy::Minimum), 0, 0, -1, 1);
	layout->addItem(new QSpacerItem(0, 0, QSizePolicy::Expanding, QSizePolicy::Minimum), 0, 3, -1, 1);
	layout->addItem(new QSpacerItem(0, 0, QSizePolicy::Minimum, QSizePolicy::Expanding), 2, 1, 1, 2);
	layout->addLayout(button_layout, 3, 1, 1, 2);

	if(route != nullptr) {
		flight.setText(route->info.flight);
		airline.setText(route->info.airline);
		aircraft.setText(route->info.aircraft);
		repeat.setValue(route->repeat);
		depart.airport.setCurrentIndex(route->info.depart.airport->index);
		depart.terminal.setText(route->info.depart.terminal);
		depart.time.setDateTime(route->info.depart.time);
		arrive.airport.setCurrentIndex(route->info.arrive.airport->index);
		arrive.terminal.setText(route->info.depart.terminal);
		arrive.time.setDateTime(route->info.depart.time);
		for(unsigned i = 0; i < Server::Meal::NUM; ++i)
			server.meal[i].setChecked(route->info.server.meal & 1 << i);
		server.hasWiFi.setChecked(route->info.server.hasWiFi);
		for(unsigned i = 0; i < Class::NUM; ++i) {
			classes[i].tickets.setValue(route->info.classes[i].tickets);
			classes[i].cost.setValue(route->info.classes[i].cost);
		}
	}

	connect(buttons, &QDialogButtonBox::rejected, this, &QObject::deleteLater);
	connect(buttons, &QDialogButtonBox::accepted, this, &RouteDesigner::apply);
}

void RouteDesigner::apply() {
	bool new_route = route == nullptr;
	if(new_route) {
		route = new Route;
		route->index = Routes::getInstance()->getNewIndex();
	}
	route->info.flight = flight.text();
	route->info.airline = airline.text();
	route->info.aircraft = aircraft.text();
	route->repeat = repeat.value();
	route->info.depart.airport = Airports::getInstance()->get(depart.airport.currentIndex());
	route->info.depart.terminal = depart.terminal.text();
	route->info.depart.time = depart.time.dateTime();
	route->info.depart.time.setTimeZone(route->info.depart.airport->time_zone);
	route->info.arrive.airport = Airports::getInstance()->get(arrive.airport.currentIndex());
	route->info.arrive.terminal = arrive.terminal.text();
	route->info.arrive.time = arrive.time.dateTime();
	route->info.arrive.time.setTimeZone(route->info.arrive.airport->time_zone);
	route->info.server.meal = 0;
	for(unsigned i = 0; i < Server::Meal::NUM; ++i)
		if(server.meal[i].isChecked())
			route->info.server.meal |= 1 << i;
	route->info.server.hasWiFi = server.hasWiFi.isChecked();
	for(unsigned i = 0; i < Class::NUM; ++i) {
		route->info.classes[i].tickets = classes[i].tickets.value();
		route->info.classes[i].cost = classes[i].cost.value();
	}
	if(!new_route) emit finished();
	else {
		unsigned index = route->index;
		Routes::getInstance()->add(std::move(*route));
		RouteWidget::getInstance()->menu.insertItem(new RouteMenuItem(index));
		delete route;
	}
	deleteLater();
}
