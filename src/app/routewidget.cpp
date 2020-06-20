#include "app/routewidget.hpp"
#include <QGridLayout>
#include <QLabel>
#include <QPushButton>
#include "app/routedesigner.hpp"
#include "models.hpp"
#include "containers.hpp"

RouteMenuItem::RouteMenuItem(unsigned index_, QWidget *parent):
		MenuItem(parent), index(index_) {
	if(index == 0) setNewItemUi();
	else setUi();
}

void RouteMenuItem::setUi() {
	qDeleteAll(findChildren<QWidget*>(QString(), Qt::FindDirectChildrenOnly));

	auto *route = Routes::getInstance()->get(index);

	auto *layout = static_cast<QGridLayout *>(this->layout());
	if(layout == nullptr) layout = new QGridLayout(this);

	auto *flight_label = new QLabel(route->info.flight);
	flight_label->setFont(QFont("Arial", 30, QFont::Bold));

	auto *delete_button = new QPushButton;
	delete_button->setFixedSize(60, 60);
	delete_button->setFlat(true);
	delete_button->setIcon(QIcon(":/icons/delete.svg"));
	delete_button->setIconSize(QSize(40, 40));

	layout->addWidget(flight_label, 0, 0, -1, 1);
	layout->addItem(new QSpacerItem(20, 0, QSizePolicy::Minimum, QSizePolicy::Minimum), 0, 1, -1, 1);
	layout->addWidget(new QLabel(route->info.depart.airport->name), 0, 2, Qt::AlignRight);
	layout->addWidget(new QLabel("\xe2\x80\x94"), 0, 3);
	layout->addWidget(new QLabel(route->info.arrive.airport->name), 0, 4, Qt::AlignLeft);
	layout->addWidget(new QLabel(route->info.depart.time.toString("yyyy.MM.dd hh:mm")), 1, 2, Qt::AlignRight);
	layout->addWidget(new QLabel("\xe2\x80\x94"), 1, 3);
	layout->addWidget(new QLabel(route->info.arrive.time.toString("yyyy.MM.dd hh:mm")), 1, 4, Qt::AlignLeft);
	layout->addItem(new QSpacerItem(20, 0, QSizePolicy::Expanding, QSizePolicy::Minimum), 0, 5, -1, 1);
	layout->addWidget(delete_button, 0, 6, -1, 1);

	connect(delete_button, &QPushButton::clicked, this, &RouteMenuItem::remove);
}

void RouteMenuItem::remove() {
	Routes::getInstance()->remove(index);
	deleteLater();
}

void RouteMenuItem::mouseReleaseEvent(QMouseEvent *) {
	auto *designer = new RouteDesigner(index == 0 ? nullptr : Routes::getInstance()->get(index));
	RouteWidget::getInstance()->addWidget(designer);
	RouteWidget::getInstance()->setCurrentWidget(designer);
	connect(designer, &RouteDesigner::finished,
		[this] { setUi(); RouteWidget::getInstance()->menu.insertItem(this); });
	connect(designer, &RouteDesigner::remove, this, &RouteMenuItem::remove);
}

RouteWidget::RouteWidget(QWidget *parent):
		QStackedWidget(parent), menu(new RouteMenuItem) {
	addWidget(&menu);
}
