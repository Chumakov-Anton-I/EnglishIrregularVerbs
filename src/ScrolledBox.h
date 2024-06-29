#ifndef SCROLLEDBOX_H
#define SCROLLEDBOX_H

/* ****************************************************************************
 * ScrolledBox.h
 * class CScrolledBox
 * ****************************************************************************/

#include <QtWidgets>

class CScrolledBox : public QFrame
{
    Q_OBJECT
public:
    CScrolledBox(QWidget* parent = nullptr);
    ~CScrolledBox();
private:
    QHBoxLayout* mainBox;
    QStackedLayout* m_stack;
    QPushButton* btnLeft;
    QPushButton* btnRight;
};

#endif // SCROLLEDBOX_H
