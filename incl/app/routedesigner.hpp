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
	struct {
		QComboBox airport;
		QLineEdit terminal;
		QDateTimeEdit time;
	} depart, arrive;
	QSpinBox repeat;
	struct {
		QComboBox meal;
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
