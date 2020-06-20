#ifndef FLIGHTWIDGET_HPP
#define FLIGHTWIDGET_HPP

#include <QStackedWidget>
#include "singleton.hpp"
#include "menu.hpp"

struct Flight;

class FlightMenuItem: public MenuItem {
	Q_OBJECT
	unsigned index;

protected:
	void mouseReleaseEvent(QMouseEvent *event) override;

public:
	FlightMenuItem(unsigned index = 0, QWidget *parent = nullptr);

public slots:
	void setUi() override;
};

class FlightWidget: public QStackedWidget, public Singleton<FlightWidget> {
	Q_OBJECT

	friend class Singleton<FlightWidget>;
	explicit FlightWidget(QWidget *parent = nullptr);

public:
	Menu menu;
};

#endif
