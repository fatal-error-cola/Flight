#include "flightapp.hpp"
#include "ui_flightapp.h"
#include <memory>

FlightApp::FlightApp(QWidget *parent)
		: QMainWindow(parent), ui(new Ui::FlightApp) {
	ui->setupUi(this);
}

FlightApp::~FlightApp() = default;
