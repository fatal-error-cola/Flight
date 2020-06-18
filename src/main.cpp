#include <QApplication>
#include <QDir>
#include <QStandardPaths>
#include <memory>
#include "containers.hpp"
#include "models.hpp"
#include "app/flightapp.hpp"

int main(int argc, char *argv[]) {
	QApplication MainApp(argc, argv);
	QDir dir(QStandardPaths::writableLocation(QStandardPaths::AppLocalDataLocation));
	if(!dir.exists()) dir.mkpath(".");
	std::unique_ptr<Airports> airports(Airports::init());
	std::unique_ptr<FlightApp> flightapp(FlightApp::init());
	flightapp->show();
	return MainApp.exec();
}
