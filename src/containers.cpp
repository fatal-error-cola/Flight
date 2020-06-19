#include "containers.hpp"
#include <cstddef>
#include <utility>
#include <algorithm>
#include <QStandardPaths>
#include <QFile>
#include <QJsonDocument>
#include <QJsonArray>
#include <QJsonValueRef>
#include "models.hpp"

Airports::Airports() {
	QFile file(QStandardPaths::writableLocation(QStandardPaths::AppLocalDataLocation) + "/airports.json");
	if(!file.exists()) QFile::copy(":/default/airports.json", file.fileName());
	file.open(QIODevice::ReadOnly);
	const auto data = QJsonDocument::fromJson(file.readAll()).array();
	size_t count = 0;
	for(auto &&item : data) {
		Airport airport{
			count++,
			item["ICAO"].toString(),
			item["IATA"].toString(),
			item["name"].toString(),
			item["city"].toString(),
			QTimeZone(item["timezone"].toString().toUtf8())
		};
		airports.push_back(airport);
		ICAO_map.emplace(airport.ICAO, airport.index);
	}
}

Airport & Airports::get(size_t index) {
	return airports[index];
}

Airport & Airports::get(QString ICAO) {
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

size_t Routes::getNewIndex() {
	return ++index;
}

void Routes::add(Route &&route) {
	routes.push_back(std::move(route));
}

void Routes::remove(size_t index) {
	routes.erase(std::lower_bound(routes.begin(), routes.end(), index,
		[](const Route &x, size_t index) { return x.index < index; }));
}

Route & Routes::get(size_t index) {
	return *std::lower_bound(routes.begin(), routes.end(), index,
		[](const Route &x, size_t index) { return x.index < index; });
}
