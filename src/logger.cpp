#include "logger.hpp"
#include <QTextStream>
#include <QDateTime>

Logger::Logger(const QString &filename, QPlainTextEdit *editor_):
		file(filename), editor(editor_) {
	file.open(QIODevice::Append | QIODevice::Text);
}

void Logger::write(const QString &text) {
	QString prefix = QDateTime::currentDateTime().toString("yyyy.MM.dd hh:mm:ss >>> ");
	QTextStream out(&file);
	out.setCodec("UTF-8");
	out << prefix << text << Qt::endl;
	editor->appendHtml("<font color=\"red\">" + prefix + "</font>");
	editor->appendPlainText(text);
}
