#ifndef ROUTEDESIGNER_HPP
#define ROUTEDESIGNER_HPP

#include <QWidget>
#include <QLineEdit>
#include <QComboBox>
#include <QDateTimeEdit>
#include <QSpinBox>
#include <QCheckBox>
#include "helpers.hpp"

struct Route;

class RouteDesigner: public QWidget {
	Q_OBJECT
	QLineEdit flight;
	QLineEdit airline;
	QLineEdit aircraft;
	QSpinBox repeat;
	struct {
		QComboBox airport;
		QLineEdit terminal;
		QDateTimeEdit time;
	} depart, arrive;
	struct {
		QCheckBox meal[Server::Meal::NUM];
		QCheckBox hasWiFi;
	} server;
	struct {
		QSpinBox tickets;
		QSpinBox cost;
	} classes[Class::NUM];

public:
	explicit RouteDesigner(QWidget *parent = nullptr);
	explicit RouteDesigner(const Route &route, QWidget *parent = nullptr);
};

#endif
