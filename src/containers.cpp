#include "containers.hpp"
#include <utility>
#include <algorithm>
#include <QStandardPaths>
#include <QFile>
#include <QJsonDocument>
#include <QJsonArray>
#include "models.hpp"

Airports::Airports() {
	QFile file(QStandardPaths::writableLocation(QStandardPaths::AppLocalDataLocation) + "/airports.json");
	if(!file.exists()) QFile::copy(":/default/airports.json", file.fileName());
	file.open(QIODevice::ReadOnly | QIODevice::Text);
	auto &&data = QJsonDocument::fromJson(file.readAll()).array();
	unsigned count = 0;
	for(auto &&item : data) {
		const auto &airport = airports.emplace_back(count++, item.toObject());
		ICAO_map.emplace(airport.ICAO, airport.index);
	}
}

Airports::~Airports() = default;

Airport * Airports::get(unsigned index) {
	return &airports[index];
}

Airport * Airports::get(QString ICAO) {
	return get(ICAO_map.at(ICAO));
}

int Airports::rowCount(const QModelIndex &parent) const {
	if(parent.isValid()) return 0;
	return airports.size();
}

QVariant Airports::data(const QModelIndex &index, int role) const {
	int row = index.row();
	switch(role) {
		case Qt::DisplayRole:
		case Qt::EditRole: {
			auto &&airport = airports[row];
			return QStringList{airport.name, airport.ICAO, airport.IATA, airport.city}.join(" / ");
		}
	}
	return QVariant();
}


Routes::Routes() {
}

Routes::~Routes() {
}

unsigned Routes::getNewIndex() {
	return ++index;
}

void Routes::add(Route &&route) {
	routes.push_back(std::move(route));
}

void Routes::remove(unsigned index) {
	routes.erase(std::lower_bound(routes.begin(), routes.end(), index,
		[](const Route &x, unsigned index) { return x.index < index; }));
}

Route * Routes::get(unsigned index) {
	auto r = std::lower_bound(routes.begin(), routes.end(), index,
		[](const Route &x, unsigned index) { return x.index < index; });
	if(r == routes.end() || r->index != index) return nullptr;
	else return &*r;
}


Flights::Flights() {
}

Flights::~Flights() {
}

unsigned Flights::getNewIndex() {
	return ++index;
}

void Flights::add(Flight &&flight) {
	flights.push_back(std::move(flight));
}

Flight * Flights::get(unsigned index) {
	auto r = std::lower_bound(flights.begin(), flights.end(), index,
		[](const Flight &x, unsigned index) { return x.index < index; });
	if(r == flights.end() || r->index != index) return nullptr;
	else return &*r;
}


Orders::Orders() {
}

Orders::~Orders() {
}

unsigned Orders::getNewIndex() {
	return ++index;
}

void Orders::add(Order &&order) {
	orders.push_back(std::move(order));
}

Order * Orders::get(unsigned index) {
	auto r = std::lower_bound(orders.begin(), orders.end(), index,
		[](const Order &x, unsigned index) { return x.index < index; });
	if(r == orders.end() || r->index != index) return nullptr;
	else return &*r;
}
