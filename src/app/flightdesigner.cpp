#include "app/flightdesigner.hpp"
#include <utility>
#include <QCompleter>
#include <QGridLayout>
#include <QFormLayout>
#include <QGroupBox>
#include <QLabel>
#include <QPushButton>
#include <QDialogButtonBox>
#include "app/flightwidget.hpp"
#include "helpers.hpp"
#include "models.hpp"
#include "containers.hpp"
#include "logger.hpp"

void FlightDesigner::setUi() {
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

	transfer_discount.setMaximum(100);
	transfer_discount.setSuffix("%");


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
	auto *buttons = new QDialogButtonBox(QDialogButtonBox::Ok | QDialogButtonBox::Cancel);
	button_layout->addItem(new QSpacerItem(0, 0, QSizePolicy::Expanding, QSizePolicy::Minimum));
	button_layout->addWidget(buttons);

	auto *first_column = new QFormLayout;
	first_column->addRow("\xe8\x88\xaa\xe7\x8f\xad\xe5\x8f\xb7\xef\xbc\x9a", &flight);
	first_column->addRow("\xe8\x88\xaa\xe5\x8f\xb8\xef\xbc\x9a", &airline);
	first_column->addRow("\xe6\x9c\xba\xe5\x9e\x8b\xef\xbc\x9a", &aircraft);
	first_column->addRow("\xe4\xb8\xad\xe8\xbd\xac\xe6\x8a\x98\xe6\x89\xa3\xef\xbc\x9a", &transfer_discount);

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

	connect(buttons, &QDialogButtonBox::rejected, this, &QObject::deleteLater);
	connect(buttons, &QDialogButtonBox::accepted, this, &FlightDesigner::apply);
}

void FlightDesigner::setFlightInfo(FlightInfo *flight_info) {
	flight.setText(flight_info->flight);
	airline.setText(flight_info->airline);
	aircraft.setText(flight_info->aircraft);
	depart.airport.setCurrentIndex(flight_info->depart.airport->index);
	depart.terminal.setText(flight_info->depart.terminal);
	depart.time.setDateTime(flight_info->depart.time);
	arrive.airport.setCurrentIndex(flight_info->arrive.airport->index);
	arrive.terminal.setText(flight_info->depart.terminal);
	arrive.time.setDateTime(flight_info->depart.time);
	for(unsigned i = 0; i < Server::Meal::NUM; ++i)
		server.meal[i].setChecked(flight_info->server.meal & 1 << i);
	server.hasWiFi.setChecked(flight_info->server.hasWiFi);
	for(unsigned i = 0; i < Class::NUM; ++i) {
		classes[i].tickets.setValue(flight_info->classes[i].tickets);
		classes[i].cost.setValue(flight_info->classes[i].cost);
	}
}

FlightDesigner::FlightDesigner(FlightInfo *flight_info, QWidget *parent):
		QWidget(parent), flight_object(nullptr) {
	setUi();
	setFlightInfo(flight_info);
	transfer_discount.setValue(100);
}

FlightDesigner::FlightDesigner(Flight *flight_, QWidget *parent):
		QWidget(parent), flight_object(flight_) {
	setUi();
	setFlightInfo(&flight_object->info);
	transfer_discount.setValue(flight_object->transfer_discount);

	flight.setDisabled(true);
	airline.setDisabled(true);
	aircraft.setDisabled(true);
	depart.airport.setDisabled(true);
	depart.terminal.setDisabled(true);
	depart.time.setDisabled(true);
	arrive.airport.setDisabled(true);
	arrive.terminal.setDisabled(true);
	arrive.time.setDisabled(true);
	for(unsigned i = 0; i < Server::Meal::NUM; ++i)
		server.meal[i].setDisabled(true);
	server.hasWiFi.setDisabled(true);
	for(unsigned i = 0; i < Class::NUM; ++i)
		classes[i].tickets.setDisabled(true);
}

void FlightDesigner::apply() {
	bool new_flight = flight_object == nullptr;
	if(new_flight) {
		flight_object = new Flight;
		flight_object->index = Flights::getInstance()->getNewIndex();

		flight_object->info.flight = flight.text();
		flight_object->info.airline = airline.text();
		flight_object->info.aircraft = aircraft.text();
		flight_object->info.depart.airport = Airports::getInstance()->get(depart.airport.currentIndex());
		flight_object->info.depart.terminal = depart.terminal.text();
		flight_object->info.depart.time = depart.time.dateTime();
		flight_object->info.depart.time.setTimeZone(flight_object->info.depart.airport->time_zone);
		flight_object->info.arrive.airport = Airports::getInstance()->get(arrive.airport.currentIndex());
		flight_object->info.arrive.terminal = arrive.terminal.text();
		flight_object->info.arrive.time = arrive.time.dateTime();
		flight_object->info.arrive.time.setTimeZone(flight_object->info.arrive.airport->time_zone);
		flight_object->info.server.meal = 0;
		for(unsigned i = 0; i < Server::Meal::NUM; ++i)
			if(server.meal[i].isChecked())
				flight_object->info.server.meal |= 1 << i;
		flight_object->info.server.hasWiFi = server.hasWiFi.isChecked();
		for(unsigned i = 0; i < Class::NUM; ++i)
			flight_object->info.classes[i].tickets = classes[i].tickets.value();
	}

	for(unsigned i = 0; i < Class::NUM; ++i)
		flight_object->info.classes[i].cost = classes[i].cost.value();
	flight_object->transfer_discount = transfer_discount.value();

	if(!new_flight) emit finished();
	else {
		unsigned index = flight_object->index;
		flight_logger->write(
			QString("flight %1 (index %2) is now online")
				.arg(flight_object->info.flight)
				.arg(index)
		);
		Flights::getInstance()->add(std::move(*flight_object));
		FlightWidget::getInstance()->menu.insertItem(new FlightMenuItem(index));
		delete flight_object;
	}
	deleteLater();
}
