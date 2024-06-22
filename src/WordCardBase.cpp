/* ****************************************************************************
 * WordCardBase.cpp
 * ****************************************************************************/

#include "WordCardBase.h"

CWordCardBase :: CWordCardBase(QWidget* parent/* = nullptr*/)
    :QFrame(parent)
{
    setFrameStyle(QFrame::StyledPanel | QFrame::Sunken);
    m_audioOutput = new QAudioOutput;
    m_sound = new QMediaPlayer;
    m_sound->setAudioOutput(m_audioOutput);
}

CWordCardBase :: ~CWordCardBase()
{
}

/* [slot] play sound */
void CWordCardBase :: playSound()
{
    m_sound->play();
}
