#ifndef ROUTEWIDGET_HPP
#define ROUTEWIDGET_HPP

#include <QStackedWidget>
#include "singleton.hpp"
#include "menu.hpp"

struct Route;

class RouteMenuItem: public MenuItem {
	Q_OBJECT
	unsigned index;

protected:
	void mouseReleaseEvent(QMouseEvent *event) override;

public:
	RouteMenuItem(unsigned index = 0, QWidget *parent = nullptr);

public slots:
	void setUi() override;
	void remove();
};

class RouteWidget: public QStackedWidget, public Singleton<RouteWidget> {
	Q_OBJECT

	friend class Singleton<RouteWidget>;
	explicit RouteWidget(QWidget *parent = nullptr);

public:
	Menu menu;
};

#endif
