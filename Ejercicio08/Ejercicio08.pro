QT       += core gui printsupport

greaterThan(QT_MAJOR_VERSION, 4): QT += widgets

CONFIG += c++17

# Archivos fuente (.cpp) y cabeceras (.h) se irán sumando solos
SOURCES += main.cpp \
    codeeditor.cpp \
    editorprincipal.cpp \
    login.cpp \
    modobloqueado.cpp

# Script para copiar config.ini automáticamente
FILE_CONFIG = $$PWD/config.ini
macx|unix {
    copy_config.commands = cp $$quote($$FILE_CONFIG) $$quote($$OUT_PWD)
}
win32 {
    FILE_CONFIG_WIN = $$replace(FILE_CONFIG, /, \\)
    OUT_PWD_WIN = $$replace(OUT_PWD, /, \\)
    copy_config.commands = copy /y $$quote($$FILE_CONFIG_WIN) $$quote($$OUT_PWD_WIN)
}
QMAKE_EXTRA_TARGETS += copy_config
POST_TARGETDEPS += copy_config

HEADERS += \
    codeeditor.h \
    editorprincipal.h \
    login.h \
    modobloqueado.h \
    pantalla.h \
    validadores.h

FORMS += \
    login.ui