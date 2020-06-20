QT += core gui widgets network
CONFIG += c++17

# The following define makes your compiler emit warnings if you use
# any Qt feature that has been marked deprecated (the exact warnings
# depend on your compiler). Please consult the documentation of the
# deprecated API in order to know how to port your code away from it.
DEFINES += QT_DEPRECATED_WARNINGS

# You can also make your code fail to compile if it uses deprecated APIs.
# In order to do so, uncomment the following line.
# You can also select to disable deprecated APIs only up to a certain version of Qt.
#DEFINES += QT_DISABLE_DEPRECATED_BEFORE=0x060000    # disables all the APIs deprecated before Qt 6.0.0

INCLUDEPATH += $$PWD/incl

VPATH += \
	$$PWD/incl \
	$$PWD/src \
	$$PWD/resource

HEADERS += \
	singleton.hpp \
	helpers.hpp \
	models.hpp \
	containers.hpp \
	logger.hpp \
	costcalc.hpp \
	paymodule.hpp \
	orderplacement.hpp \
	server.hpp \
	app/flightapp.hpp \
	app/logwidget.hpp \
	app/menu.hpp \
	app/routewidget.hpp \
	app/routedesigner.hpp \
	app/flightwidget.hpp \
	app/flightdesigner.hpp

SOURCES += \
	helpers.cpp \
	models.cpp \
	containers.cpp \
	logger.cpp \
	costcalc.cpp \
	paymodule.cpp \
	orderplacement.cpp \
	server.cpp \
	app/flightapp.cpp \
	app/logwidget.cpp \
	app/menu.cpp \
	app/routewidget.cpp \
	app/routedesigner.cpp \
	app/flightwidget.cpp \
	app/flightdesigner.cpp \
	main.cpp

RESOURCES += \
	resource/resource.qrc
