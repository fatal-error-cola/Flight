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
	unsigned new_widget_index = 0;

public:
	explicit Menu(MenuItem *item = nullptr, QWidget *parent = nullptr);

public slots:
	void insertItem(MenuItem *item);
};

#endif
