#include <QApplication>
#include <QDir>
#include <QStandardPaths>
#include <memory>
#include "logger.hpp"
#include "models.hpp"
#include "containers.hpp"
#include "app/flightapp.hpp"
#include "app/logwidget.hpp"

int main(int argc, char *argv[]) {
	QApplication MainApp(argc, argv);

	QDir dir(QStandardPaths::writableLocation(QStandardPaths::AppLocalDataLocation));
	if(!dir.exists()) dir.mkpath(".");

	std::unique_ptr<Airports> airports(Airports::init());
	std::unique_ptr<Routes> routes(Routes::init());

	std::unique_ptr<FlightApp> flightapp(FlightApp::init());

	order_logger = std::make_unique<Logger>(
		QStandardPaths::writableLocation(QStandardPaths::AppLocalDataLocation) + "order.log",
		&LogWidget::getInstance()->order_log
	);
	flight_logger = std::make_unique<Logger>(
		QStandardPaths::writableLocation(QStandardPaths::AppLocalDataLocation) + "flight.log",
		&LogWidget::getInstance()->flight_log
	);

	flightapp->show();
	return MainApp.exec();
}
