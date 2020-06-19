#ifndef LOGWIDGET_HPP
#define LOGWIDGET_HPP

#include <QTabWidget>
#include <QPlainTextEdit>
#include "singleton.hpp"

class LogWidget: public QTabWidget, public Singleton<LogWidget> {
	Q_OBJECT

	friend class Singleton<LogWidget>;
	explicit LogWidget(QWidget *parent = nullptr);

public:
	QPlainTextEdit order_log;
	QPlainTextEdit flight_log;
};

#endif
