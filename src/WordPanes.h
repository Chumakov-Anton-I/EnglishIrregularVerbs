#ifndef WORDPANES_H
#define WORDPANES_H

/* ****************************************************************************
 * File:    WordPanes.h
 * Author:  Chumakov Anton I.
 * Purpose: classes CWordPaneBase, CWordPane, CWordPaneFull
 * Date:    July 8, 2024
 * ***************************************************************************/

#include <QtWidgets>
#include <QtMultimedia>

/** -- A base class ------------------------------------ */
class CWordPaneBase : public QFrame
{
    Q_OBJECT
public:
    CWordPaneBase(QWidget* parent = nullptr);
public slots:
    void playSound();
private:
    QAudioOutput* m_audioOut;
    QMediaPlayer* m_sound;
protected:
    QVBoxLayout* mainVbox;
    QPushButton* btnPlaySnd;
    bool status;
    bool setAudioFile(const QString& sourse);
};

/** -- A simple card --------------------------------------------- */
class CWordPane : public CWordPaneBase
{
    Q_OBJECT
public:
    CWordPane(QWidget* parent = nullptr);
    void setValues(QString&, QString&, QString&);
private:
    QLabel* m_word;
    QLabel* m_transcription;
    QHBoxLayout* m_subBox;
};

/** -- A full card ----------------------------------------------- */
class CWordPaneFull : public CWordPaneBase
{
    Q_OBJECT
public:
    CWordPaneFull(QWidget* parent = nullptr);
    void setValues(QString&, QString&, QString&);
    void setExample(const QString&);
private:
    QLabel* m_word;
    QLabel* m_example;  // Maybe 'QTextEdit'?
    QLabel* m_transcrption;
    QHBoxLayout* m_subbox;
};

#endif // WORDPANES_H
