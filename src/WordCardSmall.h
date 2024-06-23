#ifndef WORDCARDSMALL_H
#define WORDCARDSMALL_H

/* ****************************************************************************
 * WordCardSmall.h
 * ****************************************************************************/

#include "WordCardBase.h"

class CWordCardSmall : public CWordCardBase
{
    Q_OBJECT
public:
    CWordCardSmall(QWidget* parent = nullptr);
    ~CWordCardSmall();
private:    // GUI
    QVBoxLayout* m_Vbox;    // main layout, vertical
    QHBoxLayout* m_subBox;  // sublayout, horizontal
    QLabel* m_lblWord;      // the value of the current word
    QPushButton* btnPlay;   // play sound
    QLabel* m_lblTrans;     // the transcription of the current word
public slots:
    void setValues(QString& word, QString& transcript, QString& sndfname);
};

#endif // WORDCARDSMALL_H
