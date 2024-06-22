#ifndef WORDCARDBASE_H
#define WORDCARDBASE_H

/* ****************************************************************************
 * WordCardBase.h
 * class CWordCardBase: it's a base class
 * ****************************************************************************/

#include <QtWidgets>
#include <QtMultimedia>

class CWordCardBase : public QFrame
{
    Q_OBJECT
public:
    CWordCardBase(QWidget* parent = nullptr);
    ~CWordCardBase();
protected:
    QAudioOutput* m_audioOutput;
    QMediaPlayer* m_sound;
public slots:
    void playSound();
};

#endif // WORDCARDBASE_H
