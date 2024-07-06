/* ****************************************************************************
 * WordCardBase.cpp
 * ****************************************************************************/

#include "WordCardBase.h"

CWordCardBase :: CWordCardBase(QWidget* parent/* = nullptr*/)
    :QFrame(parent)
{
    //setFont(QFont("Times New Roman", 16));  // TODO: get settings from the ini
    //setFrameStyle(QFrame::StyledPanel | QFrame::Sunken);
    m_audioOut = new QAudioOutput;
    m_sound = new QMediaPlayer();
    m_sound->setAudioOutput(m_audioOut);
}

CWordCardBase :: ~CWordCardBase()
{
}

/* [slot] */
bool CWordCardBase :: setAudioFile(QString& source)
{
    if (!QFile::exists(source)) {
#ifdef _DEBUG
        qDebug() << QString("File [%1] not found.").arg(source);
#endif
        status = false;
        return false;   // Return the fail if an audiofile doesn't exist
    }
    m_sound->stop();
    m_sound->setSource(QUrl::fromLocalFile(source));
    status = true;
    return true;
}

/* [slot] play sound */
void CWordCardBase :: playSound()
{
#ifdef _DEBUG
    qDebug() << "Error:" << m_sound->errorString();
    //qDebug() << "" << m_sound->
#endif
    if (status)
        m_sound->play();
}
