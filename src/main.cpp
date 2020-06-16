#include <QApplication>
#include <memory>
#include "app/flightapp.hpp"

int main(int argc, char *argv[]) {
	QApplication MainApp(argc, argv);
	std::unique_ptr<FlightApp> flightapp(FlightApp::init());
	flightapp->show();
	return MainApp.exec();
}
