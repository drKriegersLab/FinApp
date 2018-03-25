#-------------------------------------------------
#
# Project created by QtCreator 2018-01-21T19:01:18
#
#-------------------------------------------------

QT       += core gui charts

greaterThan(QT_MAJOR_VERSION, 4): QT += widgets

TARGET = FinApp
TEMPLATE = app

# The following define makes your compiler emit warnings if you use
# any feature of Qt which as been marked as deprecated (the exact warnings
# depend on your compiler). Please consult the documentation of the
# deprecated API in order to know how to port your code away from it.
DEFINES += QT_DEPRECATED_WARNINGS

# You can also make your code fail to compile if you use deprecated APIs.
# In order to do so, uncomment the following line.
# You can also select to disable deprecated APIs only up to a certain version of Qt.
#DEFINES += QT_DISABLE_DEPRECATED_BEFORE=0x060000    # disables all the APIs deprecated before Qt 6.0.0


SOURCES += \
        main.cpp \
        finapp.cpp \
    xml_parser/csv_input.cpp \
    xml_parser/database_manager.cpp \
    xml_parser/parse_csv.cpp \
    xml_parser/xml_parser_main.cpp \
    tablemanager.cpp \
    graphmanager.cpp

HEADERS += \
        finapp.h \
    xml_parser/csv_input.h \
    xml_parser/database_manager.h \
    xml_parser/parse_csv.h \
    xml_parser/xml_parser_main.h \
    tablemanager.h \
    graphmanager.h

FORMS += \
        finapp.ui

DISTFILES += \
    xml_base/2017_01.csv