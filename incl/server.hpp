#ifndef SERVER_HPP
#define SERVER_HPP

#include <QByteArray>
#include <QTcpServer>
#include <QTcpSocket>
#include "singleton.hpp"

class TcpServer: public Singleton<TcpServer> {
	QTcpServer server;

	friend class Singleton<TcpServer>;
	TcpServer();

public:
	~TcpServer();
};

enum RequestType { FindPath = 0, Pay = 1, GetOrder = 2 };

class SocketHandler: public QObject {
	Q_OBJECT
	QTcpSocket *socket;
	QByteArray buffer;
	int stack;
	enum State { InString = 0x1, Escape = 0x2 };
	unsigned state = 0x0;

	void solve(const QByteArray &bytearray);

private slots:
	void read();

public:
	SocketHandler(QTcpSocket *socket_);

public slots:
	void write(const QByteArray &bytearray);
};

#endif
