#ifndef WORDCARDBASE_H
#define WORDCARDBASE_H

/* ****************************************************************************
 * WordCardBase.h
 * class CWordCardBase: it's a base class
 * ****************************************************************************/

#include <QtWidgets>
#include <QtMultimedia>
//#include "Player.h"

class CWordCardBase : public QFrame
{
    Q_OBJECT
public:
    CWordCardBase(QWidget* parent = nullptr);
    ~CWordCardBase();
private:
    bool status;
protected:
    QAudioOutput* m_audioOut;
    QMediaPlayer* m_sound;
    bool setAudioFile(QString&);
public slots:
    void playSound();
};

#endif // WORDCARDBASE_H
