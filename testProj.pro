
QT       += core gui sql network axcontainer

greaterThan(QT_MAJOR_VERSION, 4): QT += widgets


CONFIG += c++17


# You can make your code fail to compile if it uses deprecated APIs.
# In order to do so, uncomment the following line.
#DEFINES += QT_DISABLE_DEPRECATED_BEFORE=0x060000    # disables all the APIs deprecated before Qt 6.0.0

SOURCES += \
    dialog_auth.cpp \
    highlightdelegate.cpp \
    logicupdate.cpp \
    main.cpp \
    mainwindow.cpp \
    parser.cpp \
    updateExecute.cpp

HEADERS += \
    dialog_auth.h \
    highlightdelegate.h \
    logicupdate.h \
    mainwindow.h

FORMS += \
    ../../Qt/Examples/Qt-5.15.2/sql/sqlbrowser/browserwidget.ui \
    dialog_auth.ui \
    mainwindow.ui

# Default rules for deployment.
qnx: target.path = /tmp/$${TARGET}/bin
else: unix:!android: target.path = /opt/$${TARGET}/bin
!isEmpty(target.path): INSTALLS += target
