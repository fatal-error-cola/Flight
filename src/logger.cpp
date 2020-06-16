#include "logger.hpp"
#include <QTextStream>
#include <QDateTime>

Logger::Logger(QObject *parent, const QString &fileName, QPlainTextEdit *editor_):
		QObject(parent),
		file(fileName, this),
		editor(editor_) {
	file.open(QIODevice::Append | QIODevice::Text);
}

void Logger::write(const QString &text) {
	QString prefix = QDateTime::currentDateTime().toString("yyyy.MM.dd hh:mm:ss >>> ");
	QTextStream out(file);
	out.setCodec("UTF-8");
	out << prefix << text << Qt::endl;
	editor->appendPlainText(prefix);
	editor->appendPlainText(text);
}
