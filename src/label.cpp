/* ****************************************************************************
 * label.cpp
 * ****************************************************************************/

#include "label.h"

CLabel :: CLabel(QWidget *parent)
    : QWidget(parent)
{
    QHBoxLayout* frame = new QHBoxLayout();
    setLayout(frame);
    infoLabel = new QLabel();
    infoLabel->setAlignment(Qt::AlignCenter);
    frame->addWidget(infoLabel);
}

void CLabel :: setStatus(bool status)
{
    if (status)
    {
        QString text = "<b><font color=\"#008000\">Right!</font></b>"; // TODO: read the color from the ini
        infoLabel->setText(text);
        // ...
    }
    else
    {
        QString text = "<b><font color=\"#FF0000\">Wrong!</font></b>"; // TODO: read the color from the ini
        infoLabel->setText(text);
        // ...
    }
}

void CLabel :: reset()
{
    infoLabel->setText("");
}
