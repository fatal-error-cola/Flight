#include "app/logwidget.hpp"

LogWidget::LogWidget(QWidget *parent): QTabWidget(parent) {
	order_log = new QPlainTextEdit;
	order_log->setReadOnly(true);

	flight_log = new QPlainTextEdit;
	flight_log->setReadOnly(true);

	addTab(order_log, "订单日志");
	addTab(flight_log, "航班日志");
}
