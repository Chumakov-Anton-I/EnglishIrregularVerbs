#ifndef WORDPANES_H
#define WORDPANES_H

/* ********************************************************************
 * File:    WordPanes.h
 * Author:  Chumakov Anton I.
 * Purpose: classes CWordPane
 * Date:    July 8, 2024
 * ***************************************************************** */

#include <QtWidgets>
#include <QtMultimedia>

/** -- A Word Card class ------------------------------------ */
class CWordPane : public QFrame
{
    Q_OBJECT
public:
    CWordPane(bool showExample = false, QWidget* parent = nullptr);
public slots:
    void playSound();
    void setValues(QString&, QString&, QString&);
    void setExample(const QString& example);
private:
    bool m_showExample;
    QAudioOutput* m_audioOut;
    QMediaPlayer* m_sound;
    QPushButton* btnPlaySnd;
    QLabel* m_word;
    QLabel* m_transcription;
    QLabel* m_example;  // Maybe 'QTextEdit'?
    bool status;
    bool setAudioFile(const QString& sourse);
};

#endif // WORDPANES_H
