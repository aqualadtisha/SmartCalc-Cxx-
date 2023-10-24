QT       += core gui printsupport

greaterThan(QT_MAJOR_VERSION, 4): QT += widgets

CONFIG += c++17

# You can make your code fail to compile if it uses deprecated APIs.
# In order to do so, uncomment the following line.
#DEFINES += QT_DISABLE_DEPRECATED_BEFORE=0x060000    # disables all the APIs deprecated before Qt 6.0.0

SOURCES += \
    ../model/bank_model.cc \
    ../model/calc_model.cc \
    ../model/calc_modules.cc \
    bankwindow.cc \
    ../main.cc \
    mainwindow.cc \
    qcustomplot.cpp

HEADERS += \
    ../model/bank_model.h \
    ../controller/calc_controller.h \
    ../model/calc_model.h \
    ../model/calc_modules.h \
    bankwindow.h \
    mainwindow.h \
    qcustomplot.h

FORMS += \
    bankwindow.ui \
    mainwindow.ui

# Default rules for deployment.
qnx: target.path = /tmp/$${TARGET}/bin
else: unix:!android: target.path = /opt/$${TARGET}/bin
!isEmpty(target.path): INSTALLS += target
