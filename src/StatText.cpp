/* ****************************************************************************
 * StatText.cpp
 * ****************************************************************************/

#include "StatText.h"

CStatText :: CStatText(QWidget* parent)
    : QWidget(parent)
{
    setFont(QFont("Times New Roman", m_fontSize));
    //mainFrame = new QFrame();

    mainLayout = new QVBoxLayout();
    //mainFrame->setLayout(mainLayout);
    setLayout(mainLayout);

    Text = new QTextEdit();
    Text->setReadOnly(true);
    mainLayout->addWidget(Text);

    Text->setAlignment(Qt::AlignCenter);
    //Text->setStyleSheet("QLabel { background-color: #FFFFFF; }");
    //Text->setFont(QFont("Times New Roman", 14));
    bottomBox = new QHBoxLayout();
        btnPlaySnd = new QPushButton("[ Play |> ]");    // TODO: add picture
        bottomBox->addWidget(btnPlaySnd);
        bottomBox->addSpacing(12);
        Transcription = new QLabel();
        Transcription->setFrameStyle(QFrame::Shape::Panel | QFrame::Shadow::Sunken);
        bottomBox->addWidget(Transcription);
    mainLayout->addLayout(bottomBox);

    connect(btnPlaySnd, SIGNAL(clicked()), SLOT(playSound()));
}

CStatText :: ~CStatText()
{
}

/* [slot] Sets text */
void CStatText :: setText(const QString& text, const QString& transcr, const QString& fname)
{
    Text->setText(text);
    Transcription->setText(transcr);
    //if (sound == nullptr) {
    delete sound;
    sound = nullptr;
    if (QFile::exists(fname)) {
        sndExists = true;
        btnPlaySnd->setEnabled(true);
        //qDebug() << fname;
        //audioOutput = new QAudioOutput;
        //sound->setAudioOutput(audioOutput);
        sound = new QSoundEffect; //new QMediaPlayer;
        sound->setSource(QUrl::fromLocalFile(fname));
        sound->setLoopCount(1);
        sound->setVolume(99.9f);
    }
    else    // Disable play button if a soundfile doesn't exist
        btnPlaySnd->setEnabled(false);
}

/* [slot] Plays sound if it exists */
void CStatText :: playSound()
{
    if (sndExists)  // TODO: maybe it doesn't have mean
        sound->play();
}
