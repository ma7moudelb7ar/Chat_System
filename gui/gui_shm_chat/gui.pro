QT += widgets
TEMPLATE = app
TARGET = gui_shm_chat

CONFIG += c++17
CONFIG -= app_bundle

QMAKE_CXXFLAGS += -pthread

SOURCES += \
    main.cpp \
    startwindow.cpp \
    chatwindow.cpp \
    ../../common/utils.cpp \
    ../../shm_chat/ipc.cpp

HEADERS += \
    startwindow.h \
    chatwindow.h \
    ../../common/protocol.h \
    ../../common/utils.h \
    ../../shm_chat/ipc.h

INCLUDEPATH += \
    . \
    ../../common \
    ../../shm_chat

LIBS += -pthread
