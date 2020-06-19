#ifndef MENU_HPP
#define MENU_HPP

#include <QVBoxLayout>
#include <QGroupBox>
#include <QScrollArea>

class MenuItem: public QGroupBox {
	Q_OBJECT

protected:
	void setNewItemUi();

public:
	explicit MenuItem(QWidget *parent = nullptr);

public slots:
	virtual void setUi() = 0;
};

class Menu: public QScrollArea {
	Q_OBJECT
	QVBoxLayout *layout;

public:
	explicit Menu(MenuItem *item, QWidget *parent = nullptr);

public slots:
	void insertItem(MenuItem *item);
};

#endif
