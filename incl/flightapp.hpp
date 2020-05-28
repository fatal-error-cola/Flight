#ifndef FLIGHTAPP_HPP
#define FLIGHTAPP_HPP

#include <QMainWindow>
#include <memory>

namespace Ui { class FlightApp; }

class FlightApp: public QMainWindow {
	Q_OBJECT
	std::unique_ptr<Ui::FlightApp> ui;

public:
	explicit FlightApp(QWidget *parent = nullptr);
	~FlightApp();
};

#endif
