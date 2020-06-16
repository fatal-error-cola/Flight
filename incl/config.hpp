#ifndef CONFIG_HPP
#define CONFIG_HPP

#include <QSettings>

inline QSettings config(QStandardPaths::writableLocation(QStandardPaths::AppLocalDataLocation) + "/config.ini");

extern double children_discount;

#endif
