TEMPLATE = app

QT  += core widgets xml multimedia

CONFIG += windows c++14

SOURCES += \
    ScrolledBox.cpp \
    TextEdit.cpp \
    WordCardBase.cpp \
    WordCardSmall.cpp \
    label.cpp \
    learnwindow.cpp \
    main.cpp \
    startwnd.cpp \
    window.cpp \
    word.cpp

TARGET = ../../build/IrregularVerbs

HEADERS += \
    ScrolledBox.h \
    TextEdit.h \
    WordCardBase.h \
    WordCardSmall.h \
    label.h \
    learnwindow.h \
    startwnd.h \
    window.h \
    word.h

RESOURCES += \
    images.qrc

win32:{
    LIBS += -lUser32
    VERSION = 0.0.1
    QMAKE_TARGET_COMPANY = Chumakov Inc.
    QMAKE_TARGET_PRODUCT = Irregular Verbs Tester
    QMAKE_TARGET_DESCRIPTION = Learn and check English irregular verbs
    QMAKE_TARGET_COPYRIGHT = Chumakov Anton I.
    QMAKE_TARGET_ORIGINAL_FILENAME = IrregularVerbs.exe
    QMAKE_TARGET_INTERNALNAME = IrregularVerbs
    QMAKE_TARGET_COMMENTS = Learn English irregular verbs and test yourself!
    QMAKE_TARGET_TRADEMARKS = Chumakov Software Inc.
    RC_ICONS = app.ico
}

DISTFILES +=
