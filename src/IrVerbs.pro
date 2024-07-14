TEMPLATE = app

QT  += core widgets xml multimedia

CONFIG += windows c++14

SOURCES += \
    WordPanes.cpp \
    main.cpp \
    MainWindow.cpp \
    WndLearning.cpp \
    WndTest.cpp \
    word.cpp
#    ScrolledBox.cpp \
#    TextEdit.cpp \
#    WordCardBase.cpp \
#    WordCardSmall.cpp \
#    label.cpp \
#    learnwindow.cpp \
#    startwnd.cpp \

TARGET = ../../build/IrregularVerbs

HEADERS += \
    MainWindow.h \
    WordPanes.h \
    WndLearning.h \
    WndTest.h \
    word.h
#    ScrolledBox.h \
#    TextEdit.h \
#    WordCardBase.h \
#    WordCardSmall.h \
#    label.h \
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
