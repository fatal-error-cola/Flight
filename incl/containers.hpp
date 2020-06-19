#ifndef CONTAINER_HPP
#define CONTAINER_HPP

#include <cstddef>
#include <vector>
#include <map>
#include <QString>
#include <QAbstractListModel>
#include <QAbstractTableModel>
#include "singleton.hpp"
using std::size_t;

struct Airport;

class Airports: public QAbstractListModel, public Singleton<Airports> {
	std::vector<Airport> airports;
	std::map<QString, size_t> ICAO_map;

	friend class Singleton<Airports>;
	Airports();

public:
	Airport & get(size_t index);
	Airport & get(QString ICAO);

	int rowCount(const QModelIndex &parent = QModelIndex()) const override;
	QVariant data(const QModelIndex &index, int role = Qt::DisplayRole) const override;
};

struct Route;

class Routes: public Singleton<Routes> {
	size_t index = 0;
	std::vector<Route> routes;

	friend class Singleton<Routes>;
	Routes();

public:
	size_t getNewIndex();
	void add(Route &&route);
	void remove(size_t index);
	Route & get(size_t index);
};

#endif
