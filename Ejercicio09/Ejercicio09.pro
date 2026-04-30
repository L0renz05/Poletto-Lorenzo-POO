QT       += core gui widgets sql
CONFIG   += c++17

TARGET = Ejercicio09
TEMPLATE = app

SOURCES += \
    admindb.cpp \
    login.cpp \
    main.cpp \
    pintura.cpp

HEADERS += \
    admindb.h \
    login.h \
    pintura.h

FORMS += \
    Login.ui