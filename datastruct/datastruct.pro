QT       += core gui

greaterThan(QT_MAJOR_VERSION, 4): QT += widgets

TEMPLATE = app

# You can make your code fail to compile if it uses deprecated APIs.
# In order to do so, uncomment the following line.
#DEFINES += QT_DISABLE_DEPRECATED_BEFORE=0x060000    # disables all the APIs deprecated before Qt 6.0.0
SOURCES += \
    feature_list.cpp \
    insidesearch.cpp \
    journal.cpp \
    loginwindow.cpp \
    logup.cpp \
    main.cpp \
    mainwindow.cpp \
    navigate.cpp \
    searchplace.cpp

HEADERS += \
    feature_list.h \
    insidesearch.h \
    journal.h \
    loginwindow.h \
    logup.h \
    mainwindow.h \
    navigate.h \
    searchplace.h

FORMS += \
    feature_list.ui \
    insidesearch.ui \
    journal.ui \
    loginwindow.ui \
    logup.ui \
    mainwindow.ui \
    navigate.ui \
    searchplace.ui

# Default rules for deployment.
#qnx: target.path = /tmp/$${TARGET}/bin
#else: unix:!android: target.path = /opt/$${TARGET}/bin
#!isEmpty(target.path): INSTALLS += target

DISTFILES += \
    ../../Desktop/shujvjiegou/usertest.csv \
    ../shujvjiegou/inside_path.csv \
    ../shujvjiegou/newplaces.csv \
    inside_path.csv \
    newplaces.csv \
    usertest.csv
