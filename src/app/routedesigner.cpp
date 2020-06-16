#include "app/routedesigner.hpp"
#include <QGridLayout>
#include <QGroupBox>
#include <QFormLayout>
#include <QLabel>
#include <QPushButton>
#include <QDialogButtonBox>
#include "models.hpp"

RouteDesigner::RouteDesigner(QWidget *parent): QWidget(parent) {
	depart.time.setCalendarPopup(true);
	depart.time.setDisplayFormat("yyyy/MM/dd hh:mm");
	depart.time.setMinimumDate(QDate::currentDate().addDays(1));
	arrive.time.setCalendarPopup(true);
	arrive.time.setDisplayFormat("yyyy/MM/dd hh:mm");
	arrive.time.setMinimumDate(QDate::currentDate().addDays(1));

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
	auto *server_layout = new QFormLayout(server_box);
	server_layout->addRow("飞机餐：", &server.meal);
	server_layout->addRow("Wi-Fi：", &server.hasWiFi);

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
	layout->addWidget(server_box, 3, 2, Qt::AlignLeft);
	layout->addItem(new QSpacerItem(0, 0, QSizePolicy::Expanding, QSizePolicy::Minimum), 0, 0, -1, 1);
	layout->addItem(new QSpacerItem(0, 0, QSizePolicy::Expanding, QSizePolicy::Minimum), 0, 5, -1, 1);
	layout->addItem(new QSpacerItem(0, 0, QSizePolicy::Minimum, QSizePolicy::Expanding), 4, 0, 1, 4);
	layout->addLayout(button_layout, 5, 1, 1, 4);
}

RouteDesigner::RouteDesigner(const Route &route, QWidget *parent): RouteDesigner(parent) {
	flight.setText(route.info.flight);
	airline.setText(route.info.airline);
	aircraft.setText(route.info.aircraft);
	depart.terminal.setText(route.info.depart.terminal);
	depart.time.setDateTime(route.info.depart.time);
	arrive.terminal.setText(route.info.depart.terminal);
	arrive.time.setDateTime(route.info.depart.time);
	repeat.setValue(route.repeat);
	server.hasWiFi.setCheckState(route.info.server.hasWiFi ? Qt::Checked : Qt::Unchecked);
}
