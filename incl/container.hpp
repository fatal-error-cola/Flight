#ifndef CONTAINER_HPP
#define CONTAINER_HPP

#include <map>
#include <QString>
#include <QStandardItemModel>
#include "singleton.hpp"

struct Airport;

class Airports: /*public QAbstractTableModel,*/ public Singleton<Airports> {
	std::map<QString, Airport> airports;

	Airports();

public:
	// int rowCount(const QModelIndex &parent = QModelIndex()) const override;
	// int columnCount(const QModelIndex &parent = QModelIndex()) const override;
	// QVariant data(const QModelIndex &index, int role = Qt::DisplayRole) const override;
};

#endif
