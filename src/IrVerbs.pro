TEMPLATE = app

QT  += core widgets xml multimedia

CONFIG += windows c++14

SOURCES += \
    ReportWnd.cpp \
    main.cpp \
    MainWindow.cpp \
    WordPanes.cpp \
    label.cpp \
    TextEdit.cpp \
    WndLearning.cpp \
    WndTest.cpp \
    word.cpp \
    ScrolledBox.cpp

TARGET = ../../build/IrregularVerbs

HEADERS += \
    ReportWnd.h \
    settings_key.h \
    MainWindow.h \
    WordPanes.h \
    label.h \
    TextEdit.h \
    WndLearning.h \
    WndTest.h \
    word.h \
    ScrolledBox.h

RESOURCES += \
    images.qrc

win32:{
    LIBS += -lUser32
    VERSION = 0.2.0
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

DISTFILES += \
    ../build/styles/style.css
