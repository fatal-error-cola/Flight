#ifndef MODELS_HPP
#define MODELS_HPP

#include <cstddef>
#include <QString>
#include <QTimeZone>
#include <QDateTime>
#include <vector>
#include "helpers.hpp"
using std::size_t;

struct Airport {
	QString ICAO;
	QString IATA;
	QString name;
	QString city;
	QTimeZone time_zone;
};

struct FlightInfo {
	QString flight;
	QString airline;
	QString aircraft;
	struct {
		Airport *airport;
		QString terminal;
		QDateTime time;
	} depart, arrive;
	struct {
		size_t meal;
		bool hasWiFi;
	} server;
	struct {
		size_t tickets;
		int cost;
	} classes[Class::NUM];
};

struct Route {
	size_t index;
	FlightInfo info;
	size_t repeat;
};

struct Flight {
	size_t index;
	FlightInfo info;
	bool has_transfer_discount = false;
};

struct Order {
	size_t index;
	struct {
		QString tel;
		QString pay_handle;
	} customer;
	std::vector<Flight *> flights;
	struct Passenger {
		QString name;
		QString document_type;
		QString document;
	};
	std::vector<Passenger> passengers;
	bool can_cancel = true;
};

#endif
