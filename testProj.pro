
QT       += core gui sql network axcontainer printsupport

greaterThan(QT_MAJOR_VERSION, 4): QT += widgets


CONFIG += c++17
#LIBS += -lstdc++fs

# You can make your code fail to compile if it uses deprecated APIs.
# In order to do so, uncomment the following line.
#DEFINES += QT_DISABLE_DEPRECATED_BEFORE=0x060000    # disables all the APIs deprecated before Qt 6.0.0

SOURCES += \
    credpass.cpp \
    dialog_auth.cpp \
    highlightdelegate.cpp \
    listforms.cpp \
    logicupdate.cpp \
    main.cpp \
    mainwindow.cpp \
    parser.cpp \
    recorddialog.cpp \
    templatemanager.cpp \
    updateExecute.cpp

HEADERS += \
    credpass.h \
    dialog_auth.h \
    highlightdelegate.h \
    inja.hpp \
    json.hpp \
    listforms.h \
    logicupdate.h \
    mainwindow.h \
    recorddialog.h \
    templatemanager.h\
    inja.hpp

FORMS += \
    ../../Qt/Examples/Qt-5.15.2/sql/sqlbrowser/browserwidget.ui \
    dialog_auth.ui \
    mainwindow.ui

# Default rules for deployment.
qnx: target.path = /tmp/$${TARGET}/bin
else: unix:!android: target.path = /opt/$${TARGET}/bin
!isEmpty(target.path): INSTALLS += target

DISTFILES += \
    data
