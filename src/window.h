#ifndef WINDOW_H
#define WINDOW_H

/* ****************************************************************************
 * window.h
 * ****************************************************************************/

#include <QtWidgets>
#include <QtXml>
#include "word.h"
#include "TextEdit.h"
#include "label.h"

/*struct Report
{
    int wordsToLearn = 20;
    int score = 0;
};*/

class CWidget : public QDialog //public QWidget
{
    Q_OBJECT
public:
    CWidget(QDomNodeList& dictionary, QWidget *parent = nullptr);
    ~CWidget();

    void getReport();

public slots:
    void start();
    void check();
    void resume();
    void on_enter();

private:    // GUI part
    /* Layouts */
    QVBoxLayout *mainVbox;  // Компоновщик верхнего уровня
    QVBoxLayout *form2VBLayout;
    QVBoxLayout *form3VBLayout;
    QHBoxLayout *formsHBLayout;
    QHBoxLayout *commHBLayout;

    /* Labels */
    QLabel *WordLabel;      // Окошко с заданным словом
    QLabel *Form2Label;
    QLabel *Form3Label;
    QLabel *TranslationLabel;
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
    //void closeEvent(QCloseEvent*);
};

#endif // WINDOW_H
