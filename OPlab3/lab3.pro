QT       += core gui

greaterThan(QT_MAJOR_VERSION, 4): QT += widgets

CONFIG += c++20
QMAKE_CXXFLAGS += -std=c++20

# You can make your code fail to compile if it uses deprecated APIs.
# In order to do so, uncomment the following line.
#DEFINES += QT_DISABLE_DEPRECATED_BEFORE=0x060000    # disables all the APIs deprecated before Qt 6.0.0

SOURCES += \
    entrypoint.cpp \
    graphicwindow.cpp \
    list.cpp \
    logic.cpp \
    main.cpp \
    mainwindow.cpp

HEADERS += \
    appcontext.h \
    entrypoint.h \
    error.h \
    graphicwindow.h \
    list.h \
    logic.h \
    mainwindow.h

FORMS += \
    graphicwindow.ui \
    mainwindow.ui

# Default rules for deployment.
qnx: target.path = /tmp/$${TARGET}/bin
else: unix:!android: target.path = /opt/$${TARGET}/bin
!isEmpty(target.path): INSTALLS += target
