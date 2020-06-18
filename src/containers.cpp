#include "containers.hpp"
#include "models.hpp"
#include <QStandardPaths>
#include <QFile>

#include <QDebug>

Airports::Airports() {
	QFile file(QStandardPaths::writableLocation(QStandardPaths::AppLocalDataLocation) + "/airports.csv");
	if(!file.exists()) QFile::copy(":/default/airports.csv", file.fileName());
	qDebug() << file.exists();

	airports.push_back({"ZBAA", "PEK", "北京首都国际机场", "北京", QTimeZone("Asia/Shanghai")});
	airports.push_back({"ZSPD", "PVG", "上海浦东国际机场", "上海", QTimeZone("Asia/Shanghai")});
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
			return QStringList{airport.name, airport.ICAO, airport.IATA, airport.city}.join("-");
			break;
		}
	}
	return QVariant();
}
