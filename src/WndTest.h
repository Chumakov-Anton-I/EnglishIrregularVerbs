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

/*struct Report
{
    int wordsToLearn = 20;
    int score = 0;
};*/

extern QSettings* appSettings;

class CWndTest : public QDialog
{
    Q_OBJECT
public:
    CWndTest(QDomNodeList& dictionary, QWidget *parent = nullptr);
    ~CWndTest();

    void getReport();

public slots:
    void start();
    void check();
    void resume();
    void on_enter();

private:    // GUI part
    /* Layouts */
    QVBoxLayout *mainVbox;  // top-level layout
    QVBoxLayout *form2VBLayout;
    QVBoxLayout *form3VBLayout;
    QHBoxLayout *formsHBLayout;
    QHBoxLayout *commHBLayout;

    /* Labels */
    CWordPane *WordLabel;  // the window with a current word
    //QLabel *Form2Label;
    //QLabel *Form3Label;
    //QLabel *TranslationLabel;
    CLabel *ResultLabel;
    QLabel *hintLabel;

    /* Form 2 */
    CTextEdit *Form2Edit;
    CTextEdit *Form3Edit;
    CTextEdit *TranslationEdit;

    /* Buttons */
    QPushButton *btnCheck;
    QPushButton *btnResume;

private:    // dictionary part
    bool readDictionary(QDomDocument);
    void prepareDictionary();
    bool readWord();
    CWord* currentWord = nullptr;   // current word
    QDomNodeList dictionary;    // dictionary
    int count;         // volume of dictionary
    QVector<int> order;
    int score = 0;
    int score_succ = 0;
    QMap<QString, int> statistics;
};

#endif // WINDOW_H
