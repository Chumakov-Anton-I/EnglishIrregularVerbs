#ifndef STATTEXT_H
#define STATTEXT_H

/* ****************************************************************************
 * StatText.h
 *
 * A pane which contains a word, its transcription and its pronunciation
 * ****************************************************************************/

#include <QtWidgets>
#include <QSoundEffect>
//#include <QMediaPlayer>
//#include <QAudioOutput>

class CStatText : public QWidget
{
    Q_OBJECT
public:
    CStatText(QWidget* parent = nullptr);
    ~CStatText();
private:
    //QFrame* mainFrame;
    QVBoxLayout* mainLayout;
    QHBoxLayout* bottomBox;
    QPushButton* btnPlaySnd;
    QTextEdit* Text;
    QLabel* Transcription;
    bool sndExists = false;
    QSoundEffect* sound = nullptr;
    //QMediaPlayer* sound;
    //QAudioOutput* audioOutput;
    int m_fontSize = 16;
public slots:
    void setText(const QString& text, const QString& transcr, const QString& fname);
    void playSound();
};

#endif // STATTEXT_H
