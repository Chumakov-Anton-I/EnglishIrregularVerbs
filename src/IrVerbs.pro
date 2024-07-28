TEMPLATE = app

QT  += core widgets xml multimedia

CONFIG += windows c++14

SOURCES += \
    WordPanes.cpp \
    main.cpp \
    MainWindow.cpp \
    label.cpp \
    TextEdit.cpp \
    WndLearning.cpp \
    WndTest.cpp \
    word.cpp \
    ScrolledBox.cpp
#    WordCardBase.cpp \
#    WordCardSmall.cpp \
#    learnwindow.cpp \
#    startwnd.cpp \

TARGET = ../../build/IrregularVerbs

HEADERS += \
    MainWindow.h \
    WordPanes.h \
    label.h \
    TextEdit.h \
    WndLearning.h \
    WndTest.h \
    settings_key.h \
    word.h \
    ScrolledBox.h
#    WordCardBase.h \
#    WordCardSmall.h \
#    learnwindow.h \
#    startwnd.h \

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
