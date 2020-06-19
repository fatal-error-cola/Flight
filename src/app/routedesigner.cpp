#include "app/routedesigner.hpp"
#include <cstddef>
#include <utility>
#include <QCompleter>
#include <QGridLayout>
#include <QFormLayout>
#include <QGroupBox>
#include <QLabel>
#include <QPushButton>
#include <QDialogButtonBox>
#include "app/routewidget.hpp"
#include "helpers.hpp"
#include "models.hpp"
#include "containers.hpp"
using std::size_t;

RouteDesigner::RouteDesigner(Route *route_, QWidget *parent):
		QWidget(parent), route(route_) {
	repeat.setMaximum(999);
	repeat.setSuffix(" 天");

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

	for(size_t i = 0; i < Server::Meal::NUM; ++i)
		server.meal[i].setText(Server::Meal::name[i]);

	server.hasWiFi.setText("Wi-Fi");

	for(size_t i = 0; i < Class::NUM; ++i) {
		classes[i].tickets.setMaximum(9999);
		classes[i].cost.setMaximum(99999);
		classes[i].cost.setSuffix(" 元");
	}


	auto *layout = new QGridLayout(this);

	auto *depart_box = new QGroupBox;
	auto *depart_layout = new QFormLayout(depart_box);
	depart_layout->addRow("机场：", &depart.airport);
	depart_layout->addRow("航站楼：", &depart.terminal);
	depart_layout->addRow("当地时间：", &depart.time);

	auto *arrive_box = new QGroupBox;
	auto *arrive_layout = new QFormLayout(arrive_box);
	arrive_layout->addRow("机场：", &arrive.airport);
	arrive_layout->addRow("航站楼：", &arrive.terminal);
	arrive_layout->addRow("当地时间：", &arrive.time);

	auto *server_box = new QGroupBox;
	auto *server_layout = new QHBoxLayout(server_box);
	for(size_t i = 0; i < Server::Meal::NUM; ++i)
		server_layout->addWidget(&server.meal[i]);
	server_layout->addWidget(&server.hasWiFi);

	auto *classes_layout = new QHBoxLayout;
	for(size_t i = 0; i < Class::NUM; ++i) {
		auto *class_box = new QGroupBox(Class::name[i]);
		class_box->setAlignment(Qt::AlignHCenter);
		auto *class_layout = new QFormLayout(class_box);
		class_layout->addRow("座位：", &classes[i].tickets);
		class_layout->addRow("价格：", &classes[i].cost);
		classes_layout->addWidget(class_box);
	}

	auto *button_layout = new QHBoxLayout;
	auto *buttons = new QDialogButtonBox(QDialogButtonBox::Ok | QDialogButtonBox::Cancel);
	button_layout->addItem(new QSpacerItem(0, 0, QSizePolicy::Expanding, QSizePolicy::Minimum));
	button_layout->addWidget(buttons);

	auto *first_column = new QFormLayout;
	first_column->addRow("航班号：", &flight);
	first_column->addRow("航司：", &airline);
	first_column->addRow("机型：", &aircraft);
	first_column->addRow("周期：", &repeat);

	auto *second_column = new QGridLayout;
	second_column->addWidget(new QLabel("出发："), 0, 0, Qt::AlignRight | Qt::AlignVCenter);
	second_column->addWidget(depart_box, 0, 1, Qt::AlignLeft);
	second_column->addWidget(new QLabel("到达："), 1, 0, Qt::AlignRight | Qt::AlignVCenter);
	second_column->addWidget(arrive_box, 1, 1, Qt::AlignLeft);
	second_column->addWidget(new QLabel("服务："), 2, 0, Qt::AlignRight | Qt::AlignVCenter);
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
		for(size_t i = 0; i < Server::Meal::NUM; ++i)
			server.meal[i].setCheckState(route->info.server.meal & 1 << i ? Qt::Checked : Qt::Unchecked);
		server.hasWiFi.setCheckState(route->info.server.hasWiFi ? Qt::Checked : Qt::Unchecked);
		for(size_t i = 0; i < Class::NUM; ++i) {
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
	route->info.depart.airport = &Airports::getInstance()->get(depart.airport.currentIndex());
	route->info.depart.terminal = depart.terminal.text();
	route->info.depart.time = depart.time.dateTime();
	route->info.arrive.airport = &Airports::getInstance()->get(arrive.airport.currentIndex());
	route->info.arrive.terminal = arrive.terminal.text();
	route->info.arrive.time = arrive.time.dateTime();
	route->info.server.meal = 0;
	for(size_t i = 0; i < Server::Meal::NUM; ++i)
		if(server.meal[i].checkState() == Qt::Checked)
			route->info.server.meal |= 1 << i;
	route->info.server.hasWiFi = server.hasWiFi.checkState() == Qt::Checked;
	for(size_t i = 0; i < Class::NUM; ++i) {
		route->info.classes[i].tickets = classes[i].tickets.value();
		route->info.classes[i].cost = classes[i].cost.value();
	}
	if(!new_route) emit finished();
	else {
		size_t index = route->index;
		Routes::getInstance()->add(std::move(*route));
		RouteWidget::getInstance()->menu.insertItem(new RouteMenuItem(index));
	}
	deleteLater();
}
