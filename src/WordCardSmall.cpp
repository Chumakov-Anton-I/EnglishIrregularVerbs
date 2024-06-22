/* ****************************************************************************
 * WordCardSmall.cpp
 * ****************************************************************************/

#include "WordCardSmall.h"

CWordCardSmall :: CWordCardSmall(QWidget* parent)
    : CWordCardBase(parent)
{
    m_Vbox = new QVBoxLayout();
    setLayout(m_Vbox);
    m_lblWord = new QLabel();
    m_Vbox->addWidget(m_lblWord);
    m_subBox = new QHBoxLayout();
    m_Vbox->addLayout(m_subBox);

    btnPlay = new QPushButton(QIcon(":/ico_sound"), "");
    m_subBox->addWidget(btnPlay);
    m_lblTrans = new QLabel();
    m_subBox->addWidget(m_lblTrans);

    //
    connect(btnPlay, SIGNAL(clicked()), SLOT(playSound()));
    btnPlay->setDisabled(true);
}

CWordCardSmall :: ~CWordCardSmall()
{
}

/* [slot] Sets values */
void CWordCardSmall :: setValues(QString& word, QString& transcript, QString& sndfname) const
{
    if (QFile::exists(sndfname)) {
        btnPlay->setDisabled(false);    // unlock the play button
        m_sound->setSource(QUrl::fromLocalFile(sndfname));
    }
    m_lblWord->setText(word);
    m_lblTrans->setText(transcript);
}
