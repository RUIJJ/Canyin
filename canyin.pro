#-------------------------------------------------
#
# Project created by QtCreator 2018-10-21T13:21:11
#
#-------------------------------------------------

QT       += core gui sql

greaterThan(QT_MAJOR_VERSION, 4): QT += widgets

INCLUDEPATH += $$PWD/include
include(./Cashier/cashier.pri)
include(./Admin/admin.pri)
include(./Login/login.pri)
include(./Sqlconnect/Sqlconnect.pri)

TARGET = canyin
TEMPLATE = app
RC_ICONS = window.ico

SOURCES += main.cpp\

HEADERS  +=

RESOURCES += \
    resource.qrc
