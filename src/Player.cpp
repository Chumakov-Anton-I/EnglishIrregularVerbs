/* ****************************************************************************
 * Player.cpp
 * ****************************************************************************/

#include "Player.h"
#include <QFile>

CPlayer :: CPlayer()
{
    m_aOutput = new QAudioOutput;
    m_player = new QMediaPlayer;
    m_player->setAudioOutput(m_aOutput);
}

CPlayer :: ~CPlayer()
{
    delete m_player;
    delete m_aOutput;
    m_player = nullptr;
    m_aOutput = nullptr;
}

bool CPlayer :: init(const QString& fname)
{
    if (!QFile::exists(fname)) {
        status = false;
        return false;
    }
    m_player->setSource(QUrl::fromLocalFile(fname));
    status = true;
    return true;
}

/* [slot] Plays sound */
void CPlayer :: play()
{
    qDebug() << m_player->error();
    qDebug() << m_player->errorString();
    if (status)
        m_player->play();
}
