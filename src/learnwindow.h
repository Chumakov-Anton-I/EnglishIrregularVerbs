#ifndef LEARNWINDOW_H
#define LEARNWINDOW_H

#include <QtWidgets>
#include <QtXml>
#include "word.h"
#include "StatText.h"

class CLearnWindow : public QDialog
{
    Q_OBJECT
public:
    CLearnWindow(const QDomNodeList& dictionary, QWidget *parent = nullptr);
    ~CLearnWindow();
private:    // GUI
    QVBoxLayout* mainFrame;
    QLabel* WordLabel;
    QHBoxLayout* formsHBLayout;
    //QStackedWidget* stackForm2;
    //QStackedWidget* stackForm3;
    //QStackedWidget* stackTranslation;
    CStatText* lblForm2;
    CStatText* lblForm3;
    //QLabel* lblTransl;
    QTextEdit* txtTransl;
    QPushButton* btnNext;
    QDomNodeList dictionary;
    int m_width = 100;

private: // dictionary
    void prepareDictionary();
    QVector<int> order;
    CWord* current_word;
private slots:
    void nextWord();
};

#endif // LEARNWINDOW_H