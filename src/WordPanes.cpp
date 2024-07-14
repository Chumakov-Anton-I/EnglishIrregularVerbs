/* **************************************************************************************
 * File:    WordPanes.cpp
 * Author:  Chumakov Anton I.
 * Date:    July 8, 2024
 * *************************************************************************************/

#include "WordPanes.h"

CWordPaneBase :: CWordPaneBase(QWidget* parent)
    : QFrame(parent)
{
    mainVbox = new QVBoxLayout();
    setLayout(mainVbox);
    btnPlaySnd = new QPushButton(QIcon(":/ico_sound"), "");
    btnPlaySnd->setObjectName("ButtonPlaySound");
    m_audioOut = new QAudioOutput();
    m_sound = new QMediaPlayer();
    m_sound->setAudioOutput(m_audioOut);

    connect(btnPlaySnd, SIGNAL(clicked()), SLOT(playSound()));
}

/** Set audio file */
bool CWordPaneBase :: setAudioFile(const QString& source)
{
    if (!QFile::exists(source)) {
#ifdef _DEBUG
        qDebug() << QString("File [%1] not found.").arg(source);
#endif
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
#ifdef _DEBUG
    qDebug() << "Error:" << m_sound->errorString();
#endif
    if (status)
        m_sound->play();
}

/* ------------------------------------------------------------------------- */
CWordPane :: CWordPane(QWidget* parent)
    : CWordPaneBase(parent)
{
    m_word = new QLabel();
    mainVbox->addWidget(m_word);
    mainVbox->addSpacing(16);
    m_subBox = new QHBoxLayout();
    mainVbox->addLayout(m_subBox);
    m_subBox->addWidget(btnPlaySnd);
    m_transcription = new QLabel();
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
    m_word = new QLabel();
    mainVbox->addWidget(m_word);
    // add delimiter
    m_example = new QLabel();
    mainVbox->addWidget(m_example);
    m_subbox = new QHBoxLayout();
    mainVbox->addLayout(m_subbox);
    m_subbox->addWidget(btnPlaySnd);
    m_transcrption = new QLabel();
    m_subbox->addWidget(m_transcrption);
}

void CWordPaneFull :: setValues(QString& word, QString& trans, QString& sndfile)
{
    btnPlaySnd->setDisabled(false);
    if (!setAudioFile(sndfile))
        btnPlaySnd->setDisabled(true);
    m_word->setText(word);
    m_transcrption->setText(trans);
}
