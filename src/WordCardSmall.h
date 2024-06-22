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
    QVBoxLayout* m_Vbox;
    QHBoxLayout* m_subBox;
    QLabel* m_lblWord;
    QPushButton* btnPlay;
    QLabel* m_lblTrans;
public slots:
    void setValues(QString& word, QString& transcript, QString& sndfname) const;
};

#endif // WORDCARDSMALL_H
