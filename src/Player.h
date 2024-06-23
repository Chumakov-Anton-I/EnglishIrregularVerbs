#ifndef PLAYER_H
#define PLAYER_H

/* ****************************************************************************
 * Player.h
 * class CPlayer
 * ****************************************************************************/

//#include <QtWidgets>
#include <QString>
#include <QtMultimedia>

class CPlayer
{
    Q_OBJECT
public:
    CPlayer();
    ~CPlayer();
    bool init(const QString& fname);
private:
    QAudioOutput* m_aOutput;
    QMediaPlayer* m_player;
    bool status;
public slots:
    void play();
};

#endif // PLAYER_H
