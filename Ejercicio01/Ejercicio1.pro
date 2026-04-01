QT       += core gui widgets

TARGET = Ejercicio01
TEMPLATE = app

# Esto es para que use C++ moderno
CONFIG += c++17

SOURCES += \
    main.cpp \
    login.cpp \
    tablero.cpp

HEADERS += \
    login.h \
    tablero.h

FORMS += \
    login.ui \
    tablero.ui

# Para que encuentre los archivos generados
DESTDIR = bin