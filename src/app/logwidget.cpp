#include "app/logwidget.hpp"

LogWidget::LogWidget(QWidget *parent):
		QTabWidget(parent) {
	order_log.setReadOnly(true);
	flight_log.setReadOnly(true);

	addTab(&order_log, "\xe8\xae\xa2\xe5\x8d\x95\xe6\x97\xa5\xe5\xbf\x97");
	addTab(&flight_log, "\xe8\x88\xaa\xe7\x8f\xad\xe6\x97\xa5\xe5\xbf\x97");
}
