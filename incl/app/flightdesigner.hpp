#ifndef FLIGHTDESIGNER_HPP
#define FLIGHTDESIGNER_HPP

#include <QWidget>
#include <QLineEdit>
#include <QComboBox>
#include <QDateTimeEdit>
#include <QSpinBox>
#include <QCheckBox>
#include "helpers.hpp"

struct FlightInfo;
struct Flight;

class FlightDesigner: public QWidget {
	Q_OBJECT
	Flight *flight_object;
	QLineEdit flight;
	QLineEdit airline;
	QLineEdit aircraft;
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
	QSpinBox transfer_discount;

	void setUi();
	void setFlightInfo(FlightInfo *flight_info);

private slots:
	void apply();

public:
	explicit FlightDesigner(FlightInfo *flight_info, QWidget *parent = nullptr);
	explicit FlightDesigner(Flight *flight, QWidget *parent = nullptr);

signals:
	void finished();
};

#endif
