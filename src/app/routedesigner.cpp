#include "app/routedesigner.hpp"
#include <cstddef>
#include <QGridLayout>
#include <QGroupBox>
#include <QFormLayout>
#include <QLabel>
#include <QPushButton>
#include <QDialogButtonBox>
#include "helpers.hpp"
#include "models.hpp"
using std::size_t;

RouteDesigner::RouteDesigner(QWidget *parent): QWidget(parent) {
	repeat.setMaximum(999);
	repeat.setSuffix(" 天");
	depart.time.setCalendarPopup(true);
	depart.time.setDisplayFormat("yyyy/MM/dd hh:mm");
	depart.time.setMinimumDate(QDate::currentDate().addDays(1));
	arrive.time.setCalendarPopup(true);
	arrive.time.setDisplayFormat("yyyy/MM/dd hh:mm");
	arrive.time.setMinimumDate(QDate::currentDate().addDays(1));
	for(size_t i = 0; i < Server::Meal::NUM; ++i)
		server.meal[i].setText(Server::Meal::name[i + 1]);
	server.hasWiFi.setText("Wi-Fi");
	for(size_t i = 0; i < Class::NUM; ++i) {
		classes[i].tickets.setMaximum(999);
		classes[i].cost.setMaximum(99999);
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
		class_layout->addRow("座位数：", &classes[i].tickets);
		class_layout->addRow("价格：", &classes[i].cost);
		classes_layout->addWidget(class_box);
	}

	auto *button_layout = new QHBoxLayout;
	auto *buttons = new QDialogButtonBox(QDialogButtonBox::Ok | QDialogButtonBox::Cancel);
	button_layout->addItem(new QSpacerItem(0, 0, QSizePolicy::Expanding, QSizePolicy::Minimum));
	button_layout->addWidget(buttons);

	layout->addWidget(new QLabel("航班号："), 0, 1, Qt::AlignRight | Qt::AlignVCenter);
	layout->addWidget(&flight, 0, 2, Qt::AlignLeft);
	layout->addWidget(new QLabel("航司："), 0, 3, Qt::AlignRight | Qt::AlignVCenter);
	layout->addWidget(&airline, 0, 4, Qt::AlignLeft);
	layout->addWidget(new QLabel("机型："), 1, 1, Qt::AlignRight | Qt::AlignVCenter);
	layout->addWidget(&aircraft, 1, 2, Qt::AlignLeft);
	layout->addWidget(new QLabel("周期："), 1, 3, Qt::AlignRight | Qt::AlignVCenter);
	layout->addWidget(&repeat, 1, 4, Qt::AlignLeft);
	layout->addWidget(new QLabel("出发："), 2, 1, Qt::AlignRight | Qt::AlignVCenter);
	layout->addWidget(depart_box, 2, 2, Qt::AlignLeft);
	layout->addWidget(new QLabel("到达："), 2, 3, Qt::AlignRight | Qt::AlignVCenter);
	layout->addWidget(arrive_box, 2, 4, Qt::AlignLeft);
	layout->addWidget(new QLabel("服务："), 3, 1, Qt::AlignRight | Qt::AlignVCenter);
	layout->addWidget(server_box, 3, 2, 1, 3, Qt::AlignLeft);
	layout->addItem(new QSpacerItem(0, 0, QSizePolicy::Expanding, QSizePolicy::Minimum), 0, 0, -1, 1);
	layout->addItem(new QSpacerItem(0, 0, QSizePolicy::Expanding, QSizePolicy::Minimum), 0, 5, -1, 1);
	layout->addLayout(classes_layout, 4, 1, 1, 4);
	layout->addItem(new QSpacerItem(0, 0, QSizePolicy::Minimum, QSizePolicy::Expanding), 5, 1, 1, 4);
	layout->addLayout(button_layout, 6, 1, 1, 4);
}

RouteDesigner::RouteDesigner(const Route &route, QWidget *parent): RouteDesigner(parent) {
	flight.setText(route.info.flight);
	airline.setText(route.info.airline);
	aircraft.setText(route.info.aircraft);
	repeat.setValue(route.repeat);
	depart.terminal.setText(route.info.depart.terminal);
	depart.time.setDateTime(route.info.depart.time);
	arrive.terminal.setText(route.info.depart.terminal);
	arrive.time.setDateTime(route.info.depart.time);
	for(size_t i = 0; i < Server::Meal::NUM; ++i)
		server.meal[i].setCheckState(route.info.server.meal & 1 << i ? Qt::Checked : Qt::Unchecked);
	server.hasWiFi.setCheckState(route.info.server.hasWiFi ? Qt::Checked : Qt::Unchecked);
	for(size_t i = 0; i < Class::NUM; ++i) {
		classes[i].tickets.setValue(route.info.classes[i].tickets);
		classes[i].cost.setValue(route.info.classes[i].cost);
	}
}
