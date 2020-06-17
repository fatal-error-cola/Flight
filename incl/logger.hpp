#ifndef LOGGER_HPP
#define LOGGER_HPP

#include <QFile>
#include <QPlainTextEdit>

class Logger {
	QFile file;
	QPlainTextEdit *editor;

public:
	explicit Logger(QObject *parent, QString fileName, QPlainTextEdit *editor);

public slots:
	void write(const QString &text);
};

#endif
