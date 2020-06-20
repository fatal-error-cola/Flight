#include "server.hpp"
#include <utility>
#include <QJsonDocument>
#include "logger.hpp"
#include "orderplacement.hpp"
#include "models.hpp"
#include "containers.hpp"

TcpServer::TcpServer() {
	server.listen(QHostAddress::Any, 8080);
	order_logger->write("server started");
	server.connect(&server, &QTcpServer::newConnection,
		[this] { new SocketHandler(server.nextPendingConnection()); });
}

TcpServer::~TcpServer() {
	order_logger->write("server closed");
}

SocketHandler::SocketHandler(QTcpSocket *socket_): socket(socket_) {
	connect(socket, &QIODevice::readyRead, this, &SocketHandler::read);
	connect(socket, &QTcpSocket::disconnected, socket, &QObject::deleteLater);
	connect(socket, &QTcpSocket::disconnected, this, &QObject::deleteLater);
}

void SocketHandler::read() {
	for(char ch : socket->readAll()) {
		buffer.append(ch);
		if(state & InString) {
			if(state & Escape) state &= ~Escape;
			else {
				if(ch == '"') state &= ~InString;
				else if(ch == '\\') state |= Escape;
			}
		} else {
			if(ch == '"') state |= InString;
			else if(ch == '{' || ch == '[') ++stack;
			else if(ch == '}' || ch == ']') --stack;
		}
		if(stack == 0) {
			solve(std::move(buffer));
			buffer = QByteArray();
		}
	}
}

void SocketHandler::solve(const QByteArray &bytearray) {
	auto data = QJsonDocument::fromJson(bytearray);
	if(data.isEmpty()) return;
	switch(data["type"].toInt()) {
		case FindPath: {
			break;
		}
		case Pay: {
			OrderPlacement placeOrder;
			connect(&placeOrder, &OrderPlacement::finished, this, &SocketHandler::write);
			placeOrder(data.object());
			break;
		}
		case GetOrder: {
			break;
		}
	}
}

void SocketHandler::write(const QByteArray &bytearray) {
	socket->write(bytearray);
	socket->disconnectFromHost();
}
