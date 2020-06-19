#include "app/menu.hpp"
#include <QHBoxLayout>
#include <QLabel>

MenuItem::MenuItem(QWidget *parent): QGroupBox(parent) {
	setFixedHeight(80);
	setStyleSheet(R"(
		QGroupBox {
			border-style: solid;
			border-width: 1px;
			border-radius: 10px;
		}
		QGroupBox:hover {
			border-color: blue;
		}
	)");
	setCursor(Qt::PointingHandCursor);
}

void MenuItem::setNewItemUi() {
	auto *layout = new QHBoxLayout(this);
	auto *plus = new QLabel;
	QPixmap icon(":/icons/new.svg");
	plus->setPixmap(icon.scaled(40, 40, Qt::KeepAspectRatio, Qt::SmoothTransformation));
	layout->addWidget(plus, 0, Qt::AlignCenter);
}

Menu::Menu(MenuItem *item, QWidget *parent): QScrollArea(parent) {
	setFrameShape(QFrame::NoFrame);
	setWidgetResizable(true);
	auto *inner = new QWidget;
	layout = new QVBoxLayout(inner);
	layout->addWidget(item);
	layout->addItem(new QSpacerItem(0, 0, QSizePolicy::Minimum, QSizePolicy::Expanding));
	setWidget(inner);
}

void Menu::insertItem(MenuItem *item) {
	layout->insertWidget(1, item);
}
