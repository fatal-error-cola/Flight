#ifndef LOGGER_HPP
#define LOGGER_HPP

#include <memory>
#include <QFile>
#include <QPlainTextEdit>

class Logger {
	QFile file;
	QPlainTextEdit *editor;

public:
	explicit Logger(const QString &filename, QPlainTextEdit *editor);

	void write(const QString &text);
};

inline std::unique_ptr<Logger> order_logger;
inline std::unique_ptr<Logger> flight_logger;

#endif
