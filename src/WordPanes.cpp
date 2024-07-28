/* ********************************************************************
 * File:    WordPanes.cpp
 * Author:  Chumakov Anton I.
 * Date:    July 8, 2024
 * ***************************************************************** */

#include "WordPanes.h"

CWordPaneBase :: CWordPaneBase(QWidget* parent)
    : QFrame(parent)
{
    mainVbox = new QVBoxLayout();
    setLayout(mainVbox);
    btnPlaySnd = new QPushButton(QIcon(":/ico_sound"), "", this);
    btnPlaySnd->setObjectName("ButtonPlaySound");
    btnPlaySnd->setFocusPolicy(Qt::FocusPolicy::NoFocus);   // no focus by Tab
    m_audioOut = new QAudioOutput(this);
    m_sound = new QMediaPlayer(this);
    m_sound->setAudioOutput(m_audioOut);

    connect(btnPlaySnd, SIGNAL(clicked()), this, SLOT(playSound()));
}

/** Set audio file */
bool CWordPaneBase :: setAudioFile(const QString& source)
{
    if (!QFile::exists(source)) {
        status = false;
        return false;
    }
    m_sound->stop();
    m_sound->setSource(QUrl::fromLocalFile(source));
    status = true;
    return true;
}

/** [slot] play sound */
void CWordPaneBase :: playSound()
{
    //qDebug() << "Error:" << m_sound->errorString();
    if (status)
        m_sound->play();
}

/* ------------------------------------------------------------------------- */
CWordPane :: CWordPane(QWidget* parent)
    : CWordPaneBase(parent)
{
    m_word = new QLabel(this);
    mainVbox->addWidget(m_word);
    mainVbox->addSpacing(16);
    m_subBox = new QHBoxLayout();
    mainVbox->addLayout(m_subBox);
    m_subBox->addWidget(btnPlaySnd);
    m_transcription = new QLabel(this);
    m_subBox->addWidget(m_transcription);
}

void CWordPane :: setValues(QString& word, QString& trans, QString& sndfile)
{
    btnPlaySnd->setDisabled(false);
    if (!setAudioFile(sndfile))
        btnPlaySnd->setDisabled(true);  // lock the play button
    m_word->setText(word);
    m_transcription->setText(QString("[%1]").arg(trans));
}

/* ------------------------------------------------------------------------- */
CWordPaneFull :: CWordPaneFull(QWidget* parent)
    : CWordPaneBase(parent)
{
    m_word = new QLabel(this);
    mainVbox->addWidget(m_word);
    // add separator
    m_example = new QLabel(this);
    mainVbox->addWidget(m_example);
    m_subBox = new QHBoxLayout();
    mainVbox->addLayout(m_subBox);
    m_subBox->addWidget(btnPlaySnd);
    m_transcription = new QLabel(this);
    m_subBox->addWidget(m_transcription);
}

void CWordPaneFull :: setValues(QString& word, QString& trans, QString& sndfile)
{
    btnPlaySnd->setDisabled(false);
    if (!setAudioFile(sndfile))
        btnPlaySnd->setDisabled(true);
    m_word->setText(word);
    m_transcription->setText(trans);
}
