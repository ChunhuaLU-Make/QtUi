QT       += core gui #axcontainer 	#testlib �ᵼ�³��ֿ���̨���ڣ�Ҳ��Ϊ�˷��㿴������Ϣ

greaterThan(QT_MAJOR_VERSION, 4): QT += widgets

CONFIG += c++11

CONFIG += qaxcontainer



# You can make your code fail to compile if it uses deprecated APIs.
# In order to do so, uncomment the following line.
#DEFINES += QT_DISABLE_DEPRECATED_BEFORE=0x060000    # disables all the APIs deprecated before Qt 6.0.0

SOURCES += \
    DirLevAnaly.cpp \
    ExcelOperation.cpp \
    main.cpp \
    mainwindow.cpp \
    readfile.cpp \
    QComDocx.cpp \
    CallPyInterface.cpp \
    SigDistribution.cpp


HEADERS += \
    DirLevAnaly.h \
    ExcelOperation.h \
    mainwindow.h \
    readfile.h \
    QComDocx.h \
    CallPyInterface.h \
    SigDistribution.h

FORMS += \
    mainwindow.ui

# Default rules for deployment.
qnx: target.path = /tmp/$${TARGET}/bin
else: unix:!android: target.path = /opt/$${TARGET}/bin
!isEmpty(target.path): INSTALLS += target

INCLUDEPATH += $$PWD/include/
INCLUDEPATH += $$PWD/Lib/

Release:LIBS += -L$$PWD/./ -lpython311
Debug:LIBS += -L$$PWD/./ -lpython311_d

RESOURCES += \
    Res.qrc

DISTFILES += \
    WordToExcel.py
