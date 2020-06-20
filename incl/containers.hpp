#ifndef CONTAINERS_HPP
#define CONTAINERS_HPP

#include <vector>
#include <map>
#include <QString>
#include <QAbstractListModel>
#include "singleton.hpp"

struct Airport;

class Airports: public QAbstractListModel, public Singleton<Airports> {
	Q_OBJECT
	std::vector<Airport> airports;
	std::map<QString, unsigned> ICAO_map;

	friend class Singleton<Airports>;
	Airports();

public:
	~Airports();
	Airport * get(unsigned index);
	Airport * get(QString ICAO);

	int rowCount(const QModelIndex &parent = QModelIndex()) const override;
	QVariant data(const QModelIndex &index, int role = Qt::DisplayRole) const override;
};

struct Route;

class Routes: public Singleton<Routes> {
	unsigned index = 0;
	std::vector<Route> routes;

	friend class Singleton<Routes>;
	Routes();

public:
	~Routes();
	unsigned getNewIndex();
	void add(Route &&route);
	void remove(unsigned index);
	Route * get(unsigned index);
};

struct Flight;

class Flights: public Singleton<Flights> {
	unsigned index = 0;
	std::vector<Flight> flights;

	friend class Singleton<Flights>;
	Flights();

public:
	~Flights();
	unsigned getNewIndex();
	void add(Flight &&flight);
	Flight * get(unsigned index);
};

struct Order;

class Orders: public Singleton<Orders> {
	unsigned index = 0;
	std::vector<Order> orders;

	friend class Singleton<Orders>;
	Orders();

public:
	~Orders();
	unsigned getNewIndex();
	void add(Order &&order);
	Order * get(unsigned index);
};

#endif
