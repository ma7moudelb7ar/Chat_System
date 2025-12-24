QT += widgets network
TEMPLATE = app
TARGET = gui

SOURCES += \
    main.cpp \
    mainmenuwindow.cpp \
    serverwindow.cpp \
    netchatwindow.cpp \
    ../common/utils.cpp

HEADERS += \
    mainmenuwindow.h \
    serverwindow.h \
    netchatwindow.h \
    ../common/protocol.h \
    ../common/utils.h

INCLUDEPATH += \
    ../common
