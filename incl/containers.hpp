#ifndef CONTAINER_HPP
#define CONTAINER_HPP

#include <map>
#include <QString>
#include <QStandardItemModel>
#include <QCompleter>
#include "singleton.hpp"

struct Airport;

class Airports: public QAbstractListModel, public Singleton<Airports> {
	std::vector<Airport> airports;

	friend class Singleton<Airports>;
	Airports();

public:
	int rowCount(const QModelIndex &parent = QModelIndex()) const override;
	QVariant data(const QModelIndex &index, int role = Qt::DisplayRole) const override;
};

#endif
