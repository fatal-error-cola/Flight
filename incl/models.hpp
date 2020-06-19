#ifndef MODELS_HPP
#define MODELS_HPP

#include <cstddef>
#include <vector>
#include <QString>
#include <QTimeZone>
#include <QDateTime>
#include "helpers.hpp"
using std::size_t;

struct Airport {
	size_t index;
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
		unsigned meal;
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
	int cost;
	struct {
		QString pay_handle;
		QString tel;
	} customer;
	struct Passenger {
		QString name;
		QString document;
	};
	std::vector<Passenger> adults;
	std::vector<Passenger> children;
	std::vector<std::pair<Flight *, Class::Type>> flights;
	bool can_cancel = true;
};

#endif
