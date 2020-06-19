#ifndef ROUTEWIDGET_HPP
#define ROUTEWIDGET_HPP

#include <cstddef>
#include <QStackedWidget>
#include "singleton.hpp"
#include "menu.hpp"
using std::size_t;

struct Route;

class RouteMenuItem: public MenuItem {
	Q_OBJECT
	size_t index;

protected:
	void mouseReleaseEvent(QMouseEvent *event) override;

public:
	RouteMenuItem(size_t index = 0, QWidget *parent = nullptr);

public slots:
	void setUi() override;
};

class RouteWidget: public QStackedWidget, public Singleton<RouteWidget> {
	Q_OBJECT

	friend class Singleton<RouteWidget>;
	explicit RouteWidget(QWidget *parent = nullptr);

public:
	Menu menu;
};

#endif
