#ifndef FLIGHTAPP_HPP
#define FLIGHTAPP_HPP

#include <QMainWindow>
#include <QWidget>
#include "singleton.hpp"

class FlightApp: public QMainWindow, public Singleton<FlightApp> {
	Q_OBJECT

	friend class Singleton<FlightApp>;
	explicit FlightApp(QWidget *parent = nullptr);
};

#endif
