#ifndef WINDOW_H
#define WINDOW_H

/* ****************************************************************************
 * File:    WndTest.h
 * Author:  Chumakov Anton I.
 * Purpose: class WndTest - a widget, that runs testing
 * Date:    June 2024
 * ****************************************************************************/

#include <QtWidgets>
#include <QtXml>
#include "word.h"
#include "TextEdit.h"
#include "label.h"
#include "WordPanes.h"
//#include "FlippedPane.h"

extern QSettings* appSettings;

class CWndTest : public QDialog
{
    Q_OBJECT
public:
    CWndTest(QDomDocument& dictionary, QWidget *parent = nullptr);
    ~CWndTest();

public slots:
    void start();
    void check();
    void resume();
    void on_enter();

private:    // GUI part
    /* Labels */
    CWordPane *WordLabel;  // the window with a current word
    //CLabel *ResultLabel;
    QStackedWidget *Form2Stack;
    QStackedWidget *Form3Stack;
    CTextEdit *Form2Edit;
    CTextEdit *Form3Edit;
    CWordPane *Form2Pane;
    CWordPane *Form3Pane;
    CTextEdit *TranslationEdit;

    /* Buttons */
    QPushButton *btnCheck;
    QPushButton *btnResume;

private:    // dictionary part
    void prepareDictionary();
    void updateStatistics(bool);
    bool readStatistics(const QDomNode&);
    bool readWord();
    CWord currentWord;   // current word
    QDomDocument m_document;
    QDomNodeList dictionary;    // dictionary
    QDomNode currentWordNode;
    int count;         // volume of dictionary
    QVector<int> order;
    int score = 0;
    int score_succ = 0;
    //QMap<QString, int> statistics;
};

#endif // WINDOW_H
