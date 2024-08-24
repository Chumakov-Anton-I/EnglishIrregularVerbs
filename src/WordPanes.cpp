/* ********************************************************************
 * File:    WordPanes.cpp
 * Author:  Chumakov Anton I.
 * Date:    July 8, 2024
 * ***************************************************************** */

#include "WordPanes.h"

CWordPane :: CWordPane(bool showExample, QWidget* parent)
    : QFrame(parent), m_showExample(showExample)
{
    QVBoxLayout* mainVbox = new QVBoxLayout();
    setLayout(mainVbox);
    m_word = new QLabel(this);
    m_word->setObjectName("Word");
    mainVbox->addWidget(m_word);
    m_example = new QTextEdit(this);
    m_example->setObjectName("Example");
    if (showExample) {
        QFrame* separator = new QFrame(this);
        separator->setFrameStyle(QFrame::HLine | QFrame::Plain);
        mainVbox->addWidget(separator);
        m_example->setReadOnly(true);
        //m_example->
        mainVbox->addWidget(m_example);
        mainVbox->addSpacing(8);
        mainVbox->addStretch(1);
    }
    else {
        m_example->hide();
        mainVbox->addSpacing(20);
        mainVbox->addStretch(1);
    }
    QHBoxLayout* subBox = new QHBoxLayout();
    mainVbox->addLayout(subBox);
    btnPlaySnd = new QPushButton(QIcon(":/ico_sound"), "", this);
    btnPlaySnd->setObjectName("ButtonPlaySound");
    btnPlaySnd->setFocusPolicy(Qt::FocusPolicy::NoFocus);   // no focus by 'Tab'
    btnPlaySnd->setSizePolicy(QSizePolicy::Fixed, QSizePolicy::Fixed);
    subBox->addWidget(btnPlaySnd);
    m_audioOut = new QAudioOutput(this);
    m_transcription = new QLabel(this);
    m_transcription->setObjectName("Transcription");
    subBox->addWidget(m_transcription);

    m_sound = new QMediaPlayer(this);
    m_sound->setAudioOutput(m_audioOut);

    connect(btnPlaySnd, SIGNAL(clicked()), this, SLOT(playSound()));
}

/** Set audio file */
bool CWordPane :: setAudioFile(const QString& source)
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
void CWordPane :: playSound()
{
    if (status)
        m_sound->play();
}

/** Set values of panes */
void CWordPane :: setValues(QString& word, QString& trans, QString& sndfile)
{
    btnPlaySnd->setDisabled(false);
    if (!setAudioFile(sndfile))
        btnPlaySnd->setDisabled(true);  // lock the play button
    m_word->setText(word);
    m_transcription->setText(QString("[%1]").arg(trans));
}

/** Set examples */
void CWordPane :: setExample(const QString& example)
{
    m_example->setText(example);
}
