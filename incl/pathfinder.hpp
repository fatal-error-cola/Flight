#ifndef PATHFINDER_HPP
#define PATHFINDER_HPP

#include <QDate>

struct PathFinder: public QObject {
	Q_OBJECT

	PathFinder(QObject *parent = nullptr);
	void operator()(QString depart, QString arrive, QDate date, int tickets, int prefer_class) const;
	void operator()(Airport *depart, QString arrive, QDate date, int tickets, int prefer_class) const;
	void operator()(QString depart, Airport *arrive, QDate date, int tickets, int prefer_class) const;
	void operator()(Airport *depart, Airport *arrive, QDate date, int tickets, int prefer_class) const;

signals:
	void finished(const QByteArray &result);
};

#endif
