#ifndef MODELS_HPP
#define MODELS_HPP

#include <vector>
#include <QString>
#include <QTimeZone>
#include <QDateTime>
#include <QJsonObject>
#include "helpers.hpp"

struct Airport {
	unsigned index;
	QString ICAO;
	QString IATA;
	QString name;
	QString city;
	QTimeZone time_zone;

	Airport() = default;
	Airport(unsigned index, const QJsonObject &json);
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
		unsigned tickets;
		int cost;
	} classes[Class::NUM];

	QJsonObject toJson() const;
};

struct Route {
	unsigned index;
	FlightInfo info;
	unsigned repeat;
};

struct Flight {
	unsigned index;
	FlightInfo info;
	int transfer_discount;
};

struct OrderInfo {
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
	std::vector<std::pair<unsigned, unsigned>> flights;

	OrderInfo() = default;
	OrderInfo(const QJsonObject &json);
};

struct Order {
	unsigned index;
	int cost;
	OrderInfo info;
	bool can_cancel = true;

	QJsonObject toJson() const;
};

#endif
