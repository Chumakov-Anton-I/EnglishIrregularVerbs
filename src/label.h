#ifndef LABEL_H
#define LABEL_H

/* ****************************************************************************
 * label.h
 * Shows status - 'RIGHT/WRONG'
 * ****************************************************************************/

#include <QtWidgets>

class CLabel : public QWidget
{
    Q_OBJECT
public:
    CLabel(QWidget *parent = nullptr);
    ~CLabel();
private:
    QHBoxLayout* frame;
    QLabel* infoLabel;
public:
    void setStatus(bool);
    void reset();
};

#endif // LABEL_H
