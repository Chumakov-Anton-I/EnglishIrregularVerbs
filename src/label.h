#ifndef LABEL_H
#define LABEL_H

/* ****************************************************************************
 * label.h
 * Shows status - 'RIGHT/WRONG'
 * !!!!! Probably deprecated
 * ****************************************************************************/

#include <QtWidgets>

class CLabel : public QWidget
{
    Q_OBJECT
public:
    CLabel(QWidget *parent = nullptr);
    void setStatus(bool);
    void reset();
private:
    QLabel* infoLabel;
};

#endif // LABEL_H
