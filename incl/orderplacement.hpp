#ifndef ORDERPLACEMENT_HPP
#define ORDERPLACEMENT_HPP

#include <QObject>

struct OrderInfo;

class OrderPlacement: public QObject {
	Q_OBJECT

public:
	OrderPlacement(QObject *parent = nullptr);
	void operator()(OrderInfo &&order_info);

signals:
	void finished(const QByteArray &result);
};

#endif
