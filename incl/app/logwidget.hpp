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
	QPlainTextEdit *flight_log;
	QPlainTextEdit *order_log;
};

#endif
