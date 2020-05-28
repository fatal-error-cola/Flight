#include <QApplication>
#include "flightapp.hpp"

int main(int argc, char *argv[]) {
    QApplication MainApp(argc, argv);
    FlightApp flightapp;
    flightapp.show();
    return MainApp.exec();
}
