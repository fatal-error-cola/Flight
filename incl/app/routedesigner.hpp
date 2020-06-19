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
	Route *route;
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

private slots:
	void apply();

public:
	explicit RouteDesigner(Route *route = nullptr, QWidget *parent = nullptr);

signals:
	void finished();
};

#endif
