QT += widgets

HEADERS += \
    login.h

SOURCES += \
    login.cpp \
    main.cpp


QMAKE_CXXFLAGS += -Wno-error=implicit-function-declaration
QMAKE_CFLAGS += -Wno-error=implicit-function-declaration