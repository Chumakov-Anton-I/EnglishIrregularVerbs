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
    m_Vbox->addSpacing(32);
    m_subBox = new QHBoxLayout();
    m_Vbox->addLayout(m_subBox);

    btnPlay = new QPushButton(QIcon(":/ico_sound"), "");
    btnPlay->setFixedSize(32, 32);  // TODO
    m_subBox->addWidget(btnPlay);
    m_lblTrans = new QLabel();
    //m_lblTrans->setFrameStyle(QFrame::Shape::Panel | QFrame::Shadow::Raised);
    m_subBox->addWidget(m_lblTrans);

    // signals --> slots
    connect(btnPlay, SIGNAL(clicked()), SLOT(playSound()));
}

CWordCardSmall :: ~CWordCardSmall()
{
}

/* [slot] Sets values */
void CWordCardSmall :: setValues(QString& word, QString& transcript, QString& sndfname)
{
    btnPlay->setDisabled(false);
    if (!setAudioFile(sndfname))
        btnPlay->setDisabled(true);    // lock the play button
    m_lblWord->setText(QString("<big>%1</big>").arg(word));
    m_lblTrans->setText(QString("[%1]").arg(transcript));
}
