QT       += core gui network

greaterThan(QT_MAJOR_VERSION, 4): QT += widgets

CONFIG += c++17

# Archivos fuente (.cpp)
SOURCES += \
    gestorclima.cpp \
    gestorimagen.cpp \
    login.cpp \
    main.cpp \
    mainwindow.cpp \
    ventanaprincipal.cpp

# Archivos de cabecera (.h)
HEADERS += \
    gestorclima.h \
    gestordatos.h \
    gestorimagen.h \
    login.h \
    mainwindow.h \
    pantalla.h \
    pantalla.h \
    ventanaprincipal.h

# Archivos de diseño QtDesigner (.ui)
FORMS += \
    login.ui \
    mainwindow.ui

# Reglas por defecto de despliegue
qnx: target.path = /tmp/$${TARGET}/bin
else: unix:!android: target.path = /opt/$${TARGET}/bin
!isEmpty(target.path): INSTALLS += target

# --- SCRIPT PARA COPIAR config.ini AUTOMÁTICAMENTE ---
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