/* ****************************************************************************
 * StatText.cpp
 * ****************************************************************************/

#include "StatText.h"

CStatText :: CStatText(QWidget* parent)
    : QWidget(parent)
{
    mainFrame = new QHBoxLayout();
    setLayout(mainFrame);

    Text = new QLabel();
    mainFrame->addWidget(Text);

    Text->setAlignment(Qt::AlignCenter);
    Text->setFrameStyle(QFrame::Shape::WinPanel | QFrame::Shadow::Sunken);
    Text->setStyleSheet("QLabel { background-color: #FFFFFF; }");
    Text->setFont(QFont("Times New Roman", 14));
}

CStatText :: ~CStatText()
{
}

void CStatText :: setText(const QString& text)
{
    Text->setText(text);
}
